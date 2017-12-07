#include <iostream>
#include <array>
#include "Author.h"
#include "Git.h"
#include "Delta.h"
#include "ChangeProvider.h"
#include "Format.h"

#include <boost/algorithm/string.hpp>
#include <map>

static const std::string CMD_HELP = "--help";
static const std::string CMD_ROOT = "--git-root=";
static const std::string CMD_AUTHOR_COMMITS = "--git-author-commits=";
static const std::string CMS_AUTHOR_SUMMARY = "--git-author-summary=";
static const std::string CMD_REPO_SUMMARY = "--git-repo-summary=";
static const std::string CMD_RANK = "--git-rank=";
static const std::string CMD_RANK_EXTENSION = "--git-rank-extension=";

static const std::string OPT_FILES = "files";
static const std::string OPT_EXTENSIONS = "extensions";
static const std::string OPT_ALL = "all";

static const std::string OPT_DELTA = "delta";
static const std::string OPT_CHANGE = "change";

static const std::string EMPTY = "[ empty ]";

void init(Settings &settings, const int argc, const char* argv[]);

void authorCommitStats(const Settings settings, const std::map<std::string, Author> authors);

void fileCommitStats(const Settings settings, const std::map<std::string, Author> authors);

std::vector<Author> getVectorOfOrderedAuthors(std::map<std::string, Author> authors);

std::vector<Delta> orderDeltas(std::map<std::string, Delta> &files);

void addPathDelta(std::map<std::string, Delta> &allFiles, const PathDelta &pathDelta);

void addExtensionDelta(std::map<std::string, Delta> &allExtensionTypes, const PathDelta &pathDelta);

void printDeltas(std::string label, std::string prefix, std::map<std::string, Delta> map);

std::string toString(FileMode fileMode);

void printHelp(const char* argv[]) {
    std::string fileOptions = "[ " + OPT_FILES + " | " + OPT_EXTENSIONS + " | " + OPT_ALL + " ]";
    std::string changeOptions = "[ " + OPT_DELTA + " | " + OPT_CHANGE + " ]";

    std::cout << "Usage: " << argv[0] << " \\" << std::endl <<
        "\t" << CMD_ROOT << "path" << " \\" << std::endl <<
        "\t" << CMD_AUTHOR_COMMITS << fileOptions << " \\" << std::endl <<
        "\t" << CMS_AUTHOR_SUMMARY << fileOptions << " \\" << std::endl <<
        "\t" << CMD_REPO_SUMMARY << fileOptions << " \\" << std::endl <<
        "\t" << CMD_RANK << changeOptions << " \\" << std::endl <<
        "\t" << CMD_RANK_EXTENSION << "'.ext'" << " \\" << std::endl <<
        "\t" << CMD_HELP << std::endl << std::endl;

    std::cout << "More detail:" << std::endl <<
        padCommand(CMD_ROOT) << "path_to_git_repo" << std::endl <<
        padCommand(CMD_AUTHOR_COMMITS) << "show authors stats broken down per commit" << std::endl <<
        padCommand(CMS_AUTHOR_SUMMARY) << "show authors summary stats (across all commits)" << std::endl <<
        padCommand(CMD_REPO_SUMMARY) << "show repo stats (across all authors)" << std::endl <<
        padCommand(CMD_RANK) << "sort authors by delta (add - remove) or change (add + remove) with optional extension" << std::endl <<
        padCommand(CMD_RANK_EXTENSION) << "extension to sort authors by.  I.e. '.java' or '.cpp'" << std::endl <<
        padCommand(CMD_HELP) << "this help message " << std::endl;
}

/**
 * Usage: ./CaptainsLog \
 *	--git-root=path \
 *	--git-author-commits=[ files | extensions | all ] \
 *	--git-author-summary=[ files | extensions | all ] \
 *	--git-repo-summary=[ files | extensions | all ] \
 *	--git-rank=[ delta | change ] \
 *	--git-rank-extension='.ext' \
 *	--help
 *
 * More detail:
 * --git-root=              path_to_git_repo
 * --git-author-commits=    show authors stats broken down per commit
 * --git-author-summary=    show authors summary stats (across all commits)
 * --git-repo-summary=      show repo stats (across all authors)
 * --git-rank=              sort authors by delta (add - remove) or change (add + remove) with optional extension
 * --git-rank-extension=    extension to sort authors by.  I.e. '.java' or '.cpp'
 * --help                   this help message
 *
 * @param argc
 * @param argv
 * @return
 */
int main(const int argc, const char* argv[]) {
    Settings settings = {};

    init(settings, argc, argv);
    ChangeProvider changeProvider = {};
    ChangeCalculator *changeCalculator = changeProvider.get(settings.rankType, settings.extensionToRank);

    std::cout << "root: " << settings.root << std::endl;
    std::cout << "args: " << settings.args << std::endl;
    std::cout << "author commit mode:  " << toString(settings.authorCommitMode) << std::endl;
    std::cout << "author summary mode: " << toString(settings.authorSummaryMode) << std::endl;
    std::cout << "repo summary mode:   " << toString(settings.repoSummaryMode) << std::endl;
    std::cout << "change rank system:  " << changeCalculator->describe() << std::endl;

    const std::vector<std::string> authorNames = getAuthorNames(settings);

    std::cout << "Counted: " << authorNames.size() << " authorNames." << std::endl;

    std::map<std::string, Author> authors = {};
    for (auto const &authorName : authorNames) {
        std::vector<Commit> commits = getCommitMetaData(settings, authorName);
        authors.insert({authorName, {authorName, commits, changeCalculator}});
    }

    authorCommitStats(settings, authors);
    fileCommitStats(settings, authors);

    delete changeCalculator;

    std::cout << std::endl << "Done" << std::endl;

    return 0;
}

FileMode parseMode(std::string option) {
    if (option.compare(OPT_FILES) == 0) {
        return FileMode::FM_FILE;
    } else if (option.compare(OPT_EXTENSIONS) == 0) {
        return FileMode::FM_EXTENSION;
    } else if (option.compare(OPT_ALL) == 0) {
        return FileMode::FM_ALL;
    } else {
        return FileMode::FM_OFF;
    }
}

RankType parseRankType(std::string option) {
    if (option.compare(OPT_CHANGE) == 0) {
        return RankType::RT_CHANGE;
    } else {
        return RankType::RT_DELTA;
    }
}

std::string toString(FileMode fileMode) {
    std::string value;

    switch (fileMode) {
        case FM_OFF:
            value = "off";
            break;
        case FM_FILE:
            value = "file";
            break;
        case FM_EXTENSION:
            value = "extension";
            break;
        case FM_ALL:
            value = "all";
            break;
        default:
            value = "unknown";
            break;
    }

    return value;
}

void init(Settings &settings, const int argc, const char* argv[]) {
    std::vector<std::string> parts;
    std::string args = {};

    for(int i = 1; i < argc; i++) {
        parts = {};

        if (boost::starts_with(argv[i], CMD_HELP)) {
            printHelp(argv);
            exit(0);

        } else if (boost::starts_with(argv[i], CMD_ROOT)) {
            boost::split(parts, argv[i], boost::is_any_of("="));
            settings.root = parts[1];

        } else if (boost::starts_with(argv[i], CMD_AUTHOR_COMMITS)) {
            boost::split(parts, argv[i], boost::is_any_of("="));
            settings.authorCommitMode = parseMode(parts[1]);

        } else if (boost::starts_with(argv[i], CMS_AUTHOR_SUMMARY)) {
            boost::split(parts, argv[i], boost::is_any_of("="));
            settings.authorSummaryMode = parseMode(parts[1]);

        } else if (boost::starts_with(argv[i], CMD_REPO_SUMMARY)) {
            boost::split(parts, argv[i], boost::is_any_of("="));
            settings.repoSummaryMode = parseMode(parts[1]);

        } else if (boost::starts_with(argv[i], CMD_RANK)) {
            boost::split(parts, argv[i], boost::is_any_of("="));
            settings.rankType = parseRankType(parts[1]);

        } else if (boost::starts_with(argv[i], CMD_RANK_EXTENSION)) {
            boost::split(parts, argv[i], boost::is_any_of("="));
            settings.extensionToRank = parts[1];

        } else {
            std::string s = argv[i];
            args += s + " ";

        }
    }

    settings.args = args;
}

void authorCommitStats(const Settings settings, const std::map<std::string, Author> authors) {
    if (settings.authorCommitMode == FM_OFF && settings.authorSummaryMode == FM_OFF) {
        return;
    }

    std::cout << std::endl << "Author stats: -------------------------------------------------------------------" << std::endl << std::endl;

    //sort by most active to least
    const std::vector<Author> orderedAuthors = getVectorOfOrderedAuthors(authors);

    //print out results
    for (int i = 0; i < orderedAuthors.size(); i++) {
        auto const& author = orderedAuthors.at(i);

        std::cout << "Ranked #" << (i + 1) << " (of " << orderedAuthors.size() << ")" << std::endl;
        std::cout << author << std::endl;

        //commit stats across all commits
        std::map<std::string,Delta> allFiles = {};
        std::map<std::string,Delta> allExtensionTypes = {};

        if (settings.authorCommitMode != FM_OFF) {
            std::cout << "Commit deltas:" << std::endl;

            if (author.getCommits().empty()) {
                std::cout << "\t" << EMPTY << std::endl;
            }
        }

        for (auto const &commit : author.getCommits()) {
            //commit stats across single commits
            std::map<std::string,Delta> commitFiles = {};
            std::map<std::string,Delta> commitExtensionTypes = {};

            for (auto const &pathDelta : commit.getPathDeltas()) {
                addPathDelta(allFiles, pathDelta);
                addPathDelta(commitFiles, pathDelta);

                addExtensionDelta(allExtensionTypes, pathDelta);
                addExtensionDelta(commitExtensionTypes, pathDelta);
            }

            if (settings.authorCommitMode != FM_OFF) {
                std::cout << "\t" << commit << std::endl;

                if (settings.authorCommitMode == FM_FILE || settings.authorCommitMode == FM_ALL) {
                    printDeltas("\t\tFile deltas:", "\t\t\t", commitFiles);
                }

                if (settings.authorCommitMode == FM_EXTENSION || settings.authorCommitMode == FM_ALL) {
                    printDeltas("\t\tExtension deltas:", "\t\t\t", commitExtensionTypes);
                }
            }
        }

        if (settings.authorSummaryMode == FM_FILE || settings.authorSummaryMode == FM_ALL) {
            printDeltas("File deltas:", "\t", allFiles);
        }
        if (settings.authorSummaryMode == FM_EXTENSION || settings.authorSummaryMode == FM_ALL) {
            printDeltas("Extension deltas:", "\t", allExtensionTypes);
        }

        std::cout << std::endl << std::endl;
    }
}

void printDeltas(std::string label, std::string prefix, std::map<std::string, Delta> map) {
    std::cout << label << std::endl;
    std::vector<Delta> orderedFiles = orderDeltas(map);

    if (orderedFiles.empty()) {
        std::cout << prefix << EMPTY << std::endl;
    }

    for(auto const &file : orderedFiles) {
        std::cout << prefix << file << std::endl;
    }
}

void addExtensionDelta(std::map<std::string, Delta> &allExtensionTypes, const PathDelta &pathDelta) {
    if (allExtensionTypes.find(pathDelta.getExtensionType()) == allExtensionTypes.end()) {
        allExtensionTypes.insert({pathDelta.getExtensionType(), {pathDelta.getExtensionType()}});
    }
    Delta &extensionDelta = allExtensionTypes.find(pathDelta.getExtensionType())->second;
    extensionDelta.addAmount(pathDelta.getAdd());
    extensionDelta.removeAmount(pathDelta.getRemove());
}

void addPathDelta(std::map<std::string, Delta> &allFiles, const PathDelta &pathDelta) {
    if (allFiles.find(pathDelta.getPath()) == allFiles.end()) {
        allFiles.insert({pathDelta.getPath(), {pathDelta.getPath()}});
    }
    Delta &fileDelta = allFiles.find(pathDelta.getPath())->second;
    fileDelta.addAmount(pathDelta.getAdd());
    fileDelta.removeAmount(pathDelta.getRemove());
}

void fileCommitStats(const Settings settings, const std::map<std::string, Author> authors) {
    if (settings.repoSummaryMode == FM_OFF) {
        return;
    }

    std::cout << std::endl << "File stats: ---------------------------------------------------------------------" << std::endl << std::endl;

    std::map<std::string,Delta> allFiles = {};
    std::map<std::string,Delta> allExtensionTypes = {};
    for (auto const& author : authors) {
        for (auto const &commit : author.second.getCommits()) {
            for (auto const &pathDelta : commit.getPathDeltas()) {
                addPathDelta(allFiles, pathDelta);
                addExtensionDelta(allExtensionTypes, pathDelta);
            }
        }
    }

    if (settings.repoSummaryMode == FM_FILE || settings.repoSummaryMode == FM_ALL) {
        printDeltas("File deltas:", "\t", allFiles);
    }

    if (settings.repoSummaryMode == FM_EXTENSION || settings.repoSummaryMode == FM_ALL) {
        printDeltas("Extension deltas:", "\t", allExtensionTypes);
    }

    std::cout << std::endl << std::endl;
}

std::vector<Author> getVectorOfOrderedAuthors(std::map<std::string, Author> authors) {
    std::vector<Author> orderedAuthors = {};
    transform(authors.begin(), authors.end(), back_inserter(orderedAuthors), [](const std::map<std::string, Author>::value_type& val){return val.second;} );
    sort(orderedAuthors.begin(), orderedAuthors.end(), [](Author a, Author b) {
        return b.getTotal() < a.getTotal();
    });
    return orderedAuthors;
}

std::vector<Delta> orderDeltas(std::map<std::string, Delta> &files) {
    std::vector<Delta> orderedFiles = {};
    transform(files.begin(), files.end(), back_inserter(orderedFiles), [](const std::map<std::string, Delta>::value_type& val){return val.second;} );
    sort(orderedFiles.begin(), orderedFiles.end(), [](Delta a, Delta b) {
        return (b.getAdd() + b.getRemove()) < (a.getAdd() + a.getRemove());
    });
    return orderedFiles;
}
