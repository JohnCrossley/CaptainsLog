#include <iostream>
#include <array>
#include "Author.h"
#include "Git.h"
#include "Delta.h"

#include <boost/algorithm/string.hpp>
#include <map>

void init(std::string &root, std::string &args, const int argc, const char* argv[]);

void authorCommitStats(const std::map<std::string, Author> authors);

void fileCommitStats(const std::map<std::string, Author> authors);

std::vector<Delta> getVectorOfOrderedExtensionTypes(std::map<std::string, Delta> &extensionTypes);

std::vector<Delta> getVectorOfOrderedFiles(std::map<std::string, Delta> &files);

/**
 * Example: --gitroot=/home/johncrossley/src/UnrealEngine --gitargs="--since=\"2 weeks ago\""
 * @param argc
 * @param argv
 * @return
 */
int main(const int argc, const char* argv[]) {
    std::string root;
    std::string args;

    init(root, args, argc, argv);

    std::cout << "git root: " << root << std::endl;
    std::cout << "git args: " << args << std::endl;

    const std::vector<std::string> authorNames = getAuthorNames(root, args);

    std::cout << "Counted: " << authorNames.size() << " authorNames." << std::endl;

    std::map<std::string, Author> authors = {};
    for (auto const &authorName : authorNames) {
        std::vector<Commit> commits = getCommitMetaData(root, args, authorName);
        authors.insert({authorName, {authorName, commits}});
    }
    
    authorCommitStats(authors);
    fileCommitStats(authors);

    std::cout << std::endl << "Done" << std::endl;

    return 0;
}

/**
 * TODO
 * option to check merges against merger or person who coded the line in the branch
 * --merge=[ pull | branch ]
 *
 *
 */
void init(std::string &root, std::string &args, const int argc, const char* argv[]) {
    std::vector<std::string> parts;

    for(int i = 0; i < argc; i++) {
        parts = {};

        if (boost::starts_with(argv[i], "--gitroot=")) {
            boost::split(parts, argv[i], boost::is_any_of("="));
            root = parts[1];

        } else if (boost::starts_with(argv[i], "--gitargs=")) {
            args = argv[i];
            args = args.substr(args.find("=") + 1, args.length());

        }
    }
}

void authorCommitStats(const std::map<std::string, Author> authors) {
    std::cout << std::endl << "Author stats: -------------------------------------------------------------------" << std::endl << std::endl;

    //print out results
    for (auto const& author : authors) {
        std::cout << "Author: " << author.second << std::endl;

        //commit stats
        std::map<std::string,Delta> files = {};
        std::map<std::string,Delta> extensionTypes = {};

        std::cout << "Commit deltas:" << std::endl;
        for (auto const &commit : author.second.getCommits()) {
            for (auto const &pathDelta : commit.getPathDeltas()) {
                //paths
                if (files.find(pathDelta.getPath()) == files.end()) {
                    files.insert({pathDelta.getPath(), {pathDelta.getPath()}});
                }
                Delta &fileDelta = files.find(pathDelta.getPath())->second;
                fileDelta.addAmount(commit.getTotalAdd());
                fileDelta.removeAmount(commit.getTotalRemove());

                //extension
                if (extensionTypes.find(pathDelta.getExtensionType()) == extensionTypes.end()) {
                    extensionTypes.insert({pathDelta.getExtensionType(), {pathDelta.getExtensionType()}});
                }
                Delta &extensionDelta = extensionTypes.find(pathDelta.getExtensionType())->second;
                extensionDelta.addAmount(commit.getTotalAdd());
                extensionDelta.removeAmount(commit.getTotalRemove());
            }

            std::cout << "\t" << commit << std::endl;
        }

        std::cout << "File deltas:" << std::endl;
        std::vector<Delta> orderedFiles = getVectorOfOrderedFiles(files);
        for(auto const &file : orderedFiles) {
            std::cout << "\t" << file << std::endl;
        }

        std::cout << "Extension deltas:" << std::endl;
        std::vector<Delta> orderedExtensionTypes = getVectorOfOrderedExtensionTypes(extensionTypes);
        for(auto const &extensionType : orderedExtensionTypes) {
            std::cout << "\t" << extensionType << std::endl;
        }

        std::cout << std::endl << std::endl;
    }
}

void fileCommitStats(const std::map<std::string, Author> authors) {
    std::cout << std::endl << "File stats: ---------------------------------------------------------------------" << std::endl << std::endl;

    //commit stats
    std::map<std::string,Delta> files = {};
    std::map<std::string,Delta> extensionTypes = {};

    for (auto const& author : authors) {
        for (auto const &commit : author.second.getCommits()) {
            for (auto const &pathDelta : commit.getPathDeltas()) {
                //paths
                if (files.find(pathDelta.getPath()) == files.end()) {
                    files.insert({pathDelta.getPath(), {pathDelta.getPath()}});
                }
                Delta &fileDelta = files.find(pathDelta.getPath())->second;
                fileDelta.addAmount(commit.getTotalAdd());
                fileDelta.removeAmount(commit.getTotalRemove());

                //extension
                if (extensionTypes.find(pathDelta.getExtensionType()) == extensionTypes.end()) {
                    extensionTypes.insert({pathDelta.getExtensionType(), {pathDelta.getExtensionType()}});
                }
                Delta &extensionDelta = extensionTypes.find(pathDelta.getExtensionType())->second;
                extensionDelta.addAmount(commit.getTotalAdd());
                extensionDelta.removeAmount(commit.getTotalRemove());
            }
        }
    }

    std::cout << "File deltas:" << std::endl;
    std::vector<Delta> orderedFiles = getVectorOfOrderedFiles(files);
    for(auto const &file : orderedFiles) {
        std::cout << "\t" << file << std::endl;
    }

    std::cout << "Extension deltas:" << std::endl;
    std::vector<Delta> orderedExtensionTypes = getVectorOfOrderedExtensionTypes(extensionTypes);
    for(auto const &extensionType : orderedExtensionTypes) {
        std::cout << "\t" << extensionType << std::endl;
    }

    std::cout << std::endl << std::endl;
}

std::vector<Delta> getVectorOfOrderedFiles(std::map<std::string, Delta> &files) {
    std::vector<Delta> orderedFiles = {};
    transform(files.begin(), files.end(), back_inserter(orderedFiles), [](const std::map<std::string, Delta>::value_type& val){return val.second;} );
    sort(orderedFiles.begin(), orderedFiles.end(), [](Delta a, Delta b) {
            return (b.getAdd() + b.getRemove()) < (a.getAdd() + a.getRemove());
        });
    return orderedFiles;
}

std::vector<Delta> getVectorOfOrderedExtensionTypes(std::map<std::string, Delta> &extensionTypes) {
    std::vector<Delta> orderedExtensionTypes = {};
    transform(extensionTypes.begin(), extensionTypes.end(), back_inserter(orderedExtensionTypes), [](const std::map<std::string, Delta>::value_type& val){return val.second;} );
    sort(orderedExtensionTypes.begin(), orderedExtensionTypes.end(), [](Delta a, Delta b) {
            return (b.getAdd() + b.getRemove()) < (a.getAdd() + a.getRemove());
        });
    return orderedExtensionTypes;
}
