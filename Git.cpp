//
// Created by johncrossley on 19/10/17.
//

#include <boost/algorithm/string.hpp>
#include "Git.h"

#define BUFFER 1024

std::string parsePath(std::string &pathTemplate);

const std::string exec(const Settings settings, const std::string cmd) {
//    std::cout << "exec: " << cmd << std::endl;

    std::array<char, BUFFER> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(("cd " + settings.root + ";" + cmd).c_str(), "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), BUFFER, pipe.get()) != nullptr)
            result += buffer.data();
    }

    boost::trim(result);

    return result;
}

const std::vector<std::string> getAuthorNames(const Settings settings) {
    const std::string command = "git --no-pager log --pretty=format:\"%an\" " + settings.args + " | sort -u";
    const std::string s = exec(settings, command);
    std::vector<std::string> authors = {};
    boost::split(authors, s, boost::is_any_of("\n"));

    return authors;
}

std::vector<PathDelta> getPathDeltas(const Settings settings, std::string hash) {
    std::vector<PathDelta> pathDeltas = {};

    std::string command = "git --no-pager diff -M -C --numstat " + hash + "^..." + hash;
    std::string result = exec(settings, command);

    //first commit so everything is an add and there is no parent
    if (result.empty()) {
        command = "git --no-pager log --oneline --numstat " + hash;
        result = exec(settings, command);
        result = result.substr(result.find('\n'));//remove header line
    }

    std::vector<std::string> files = {};
    boost::split(files, result, boost::is_any_of("\n"));

    for (std::string file : files) {
        if (file.length() == 0) {
            continue;
        }

        boost::replace_all(file, " => ", "=>");//spaces will mess up the split later on (cannot seem to change this format from git-log

        std::vector<std::string> parts = {};
        boost::split(parts, file, boost::is_any_of("\t "), boost::token_compress_on);

        const std::string path = parsePath(parts[2]);

        if (parts[0].compare("-") != 0 && parts[1].compare("-") != 0) {
            const long add = std::stol(parts[0]);
            const long remove = std::stol(parts[1]);
            pathDeltas.push_back({add, remove, path});

        } else {
            //need to determine add / modify / remove from - (and other symbols git will use)
            pathDeltas.push_back({1, 0, path});

        }
    }

    return pathDeltas;
}

/**
 * The path could be of form: /x/y/{a=>b} to signify a rename/move in git
 * @param pathTemplate
 */
std::string parsePath(std::string &pathTemplate) {
    if (pathTemplate.find("=>") == -1) {
        return pathTemplate;
    }

    std::string::size_type s = pathTemplate.find("{");
    std::string::size_type e = pathTemplate.find("}");
    std::string::size_type change = pathTemplate.find("=>");

    return pathTemplate.substr(0, s) + pathTemplate.substr(change + 2, e - change - 2) + pathTemplate.substr(e + 1, pathTemplate.length());
}

const std::vector<Commit> getCommitMetaData(const Settings settings, std::string authorName) {
    const std::string command = "git --no-pager log --no-merges --pretty=format:\"%H|%ct|%P\" --author=\"" + authorName + "\" " + settings.args;
    const std::string result = exec(settings, command);

    std::vector<Commit> commits = {};
    if (result.length() == 0) {
        return commits;
    }

    std::vector<std::string> commitRecords = {};
    boost::split(commitRecords, result, boost::is_any_of("\n"));

    //for each commit
    for(auto const& commitRecord : commitRecords) {
        std::vector<std::string> parts = {};
        boost::split(parts, commitRecord, boost::is_any_of("|"));

        const std::string hash = parts[0];
        const long time = atol(parts[1].c_str());

        std::vector<std::string> parents = {};
        if (parts.size() == 3) {
            boost::split(parents, parts[2], boost::is_any_of(","));
        }

        //get file details for commit
        std::vector<PathDelta> pathDeltas = getPathDeltas(settings, hash);
        commits.push_back({ hash, time, parents, pathDeltas });
    }

    return commits;
}