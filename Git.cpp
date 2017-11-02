//
// Created by johncrossley on 19/10/17.
//

#include <boost/algorithm/string.hpp>
#include "Git.h"

#define BUFFER 1024
#define BINARY "-"

const std::string exec(const std::string root, const std::string cmd) {
//    std::cout << "exec: " << cmd << std::endl;

    std::array<char, BUFFER> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(("cd " + root + ";" + cmd).c_str(), "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), BUFFER, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}

const std::vector<std::string> getAuthorNames(const std::string root, const std::string args) {
    const std::string command = "git log --pretty=format:\"%an\" " + args + " | sort -u";
    const std::string s = exec(root, command);
    std::vector<std::string> authors = {};
    boost::split(authors, s, boost::is_any_of("\n"));
    return authors;
}

std::vector<PathDelta> getPathDeltas(std::string root, std::string hash) {
    std::vector<PathDelta> pathDeltas = {};

    const std::string command = "git diff --numstat " + hash;
    const std::string result = exec(root, command);

    std::vector<std::string> files = {};
    boost::split(files, result, boost::is_any_of("\n"));

    for (std::string file : files) {
        if (file.length() == 0) {
            continue;
        }

        std::vector<std::string> parts = {};
        boost::split(parts, file, boost::is_any_of("\t "), boost::token_compress_on);

        const unsigned long add = parts[0].compare(BINARY) == 0 ? -1 : std::stoul(parts[0]);
        const unsigned long remove = parts[1].compare(BINARY) == 0 ? -1 : std::stoul(parts[1]);

        pathDeltas.push_back({add, remove, parts[2]});
    }

    return pathDeltas;
}

const std::vector<Commit> getCommitMetaData(std::string root, std::string args, std::string authorName) {
    const std::string command = "git log --pretty=format:\"%H|%ct|%P\" --author=\"" + authorName + "\" " + args;
    const std::string result = exec(root, command);

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
        std::vector<PathDelta> pathDeltas = getPathDeltas(root, hash);
        commits.push_back({ hash, time, parents, pathDeltas });
    }

    return commits;
}