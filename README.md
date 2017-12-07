# CaptainsLog
Git repository stats

Run this program over your git repository to pull out author level (commit and summary) and repo level stats.
All broken down by file and extension.

./CaptainsLog --help
Usage: /home/johncrossley/src/CaptainsLog/cmake-build-debug/CaptainsLog \
	--git-root=path \
	--git-author-commits=[ files | extensions | all ] \
	--git-author-summary=[ files | extensions | all ] \
	--git-repo-summary=[ files | extensions | all ] \
	--git-rank=[ delta | change ] \
	--git-rank-extension='.ext' \
	--help

More detail:
--git-root=              path_to_git_repo
--git-author-commits=    show authors stats broken down per commit
--git-author-summary=    show authors summary stats (across all commits)
--git-repo-summary=      show repo stats (across all authors)
--git-rank=              sort authors by delta (add - remove) or change (add + remove) with optional extension
--git-rank-extension=    extension to sort authors by.  I.e. '.java' or '.cpp'
--help                   this help message


Example output for this repository:

Command run: ./CaptainsLog/cmake-build-debug/CaptainsLog --git-root=/home/johncrossley/src/CaptainsLog \
    --git-author-commits=all \
    --git-author-summary=all \
    --git-repo-summary=all \
    --since=\"5 weeks ago\"


root: /home/johncrossley/src/CaptainsLog
args: --since="5 weeks ago"
author commit mode:  all
author summary mode: all
repo summary mode:   all
change rank system:  Delta (all ext)
Counted: 1 authorNames.

Author stats: -------------------------------------------------------------------

Ranked #1 (of 1)
John Crossley -> 5 commits [02/11/2017 - 28/11/2017]                                                                 74+                  22-                   52+ Delta (all ext)

Commit deltas:
	28/11/2017 57158fae7605336321e53e7c69598e9179d39eb0                                                                  26+                   12-
		File deltas:
			main.cpp                                                                                                             24+                    9-
			Author.h                                                                                                              2+                    3-
		Extension deltas:
			.cpp                                                                                                                 24+                    9-
			.h                                                                                                                    2+                    3-
	28/11/2017 30765d047fca36d2f1b24d891b3be596f1a445d5                                                                  14+                    7-
		File deltas:
			Git.cpp                                                                                                              13+                    6-
			Format.cpp                                                                                                            1+                    1-
		Extension deltas:
			.cpp                                                                                                                 14+                    7-
	28/11/2017 ac5f6c7fd24da8950af1bdbb9e3c29816af80c8b                                                                  28+                    1-
		File deltas:
			Author.cpp                                                                                                           22+                    1-
			Author.h                                                                                                              6+                    0-
		Extension deltas:
			.cpp                                                                                                                 22+                    1-
			.h                                                                                                                    6+                    0-
	28/11/2017 9dd217c394555bcadc3c534ccc24918ca871a9f4                                                                   3+                    0-
		File deltas:
			.gitignore                                                                                                            3+                    0-
		Extension deltas:
			.gitignore                                                                                                            3+                    0-
	02/11/2017 fb0ec2e8d3d491e5782ea1d57e046f28c6d5b26f                                                                   3+                    2-
		File deltas:
			Git.cpp                                                                                                               3+                    2-
		Extension deltas:
			.cpp                                                                                                                  3+                    2-
File deltas:
	main.cpp                                                                                                             24+                    9-
	Git.cpp                                                                                                              16+                    8-
	Author.cpp                                                                                                           22+                    1-
	Author.h                                                                                                              8+                    3-
	.gitignore                                                                                                            3+                    0-
	Format.cpp                                                                                                            1+                    1-
Extension deltas:
	.cpp                                                                                                                 63+                   19-
	.h                                                                                                                    8+                    3-
	.gitignore                                                                                                            3+                    0-



File stats: ---------------------------------------------------------------------

File deltas:
	main.cpp                                                                                                             24+                    9-
	Git.cpp                                                                                                              16+                    8-
	Author.cpp                                                                                                           22+                    1-
	Author.h                                                                                                              8+                    3-
	.gitignore                                                                                                            3+                    0-
	Format.cpp                                                                                                            1+                    1-
Extension deltas:
	.cpp                                                                                                                 63+                   19-
	.h                                                                                                                    8+                    3-
	.gitignore                                                                                                            3+                    0-



Done

Process finished with exit code 0
