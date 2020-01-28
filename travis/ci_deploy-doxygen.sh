#!/usr/bin/env bash

# This script builds the doxygen documentation and automatically commits
<<<<<<< HEAD
# It uses an encrypted GH_TOKEN setting in Travis to check out the latest version, 
=======
# It uses an encrypted GH_TOKEN setting in Travis to check out the latest version,
>>>>>>> 26891742c0188b55a674d96671491b6334dea9c5
# build the doc, commit the changes, and then push.

set -ev # -e: Exit with nonzero exit code if anything fails
        # -v: verbose mode; print every command in travis output

if [ "${TRAVIS_BRANCH}" != "${BUILD_BRANCH}" ]; then
    echo "Will not build doxygen documentation for branch ${TRAVIS_BRANCH}"
    exit 1
fi

<<<<<<< HEAD
=======
if [ "${TRAVIS_PULL_REQUEST}" != "false" ]; then
    echo "Will not build doxygen documentation for pull requests. Skipping it."
    exit 0
fi

>>>>>>> 26891742c0188b55a674d96671491b6334dea9c5
SHA=$(git rev-parse --verify HEAD)

DOXYGEN_REPOSITORY="https://${GH_TOKEN}@github.com/rism-ch/verovio-doxygen"
DOXYGEN_DIRECTORY="doxygen"

# Clone the doxygen repo.
echo "Cloning ${DOXYGEN_REPOSITORY}"
git clone ${DOXYGEN_REPOSITORY} ${DOXYGEN_DIRECTORY}


CURRENT_PATH=$(pwd)
OUTPUT_DIRECTORY="${CURRENT_PATH}/${DOXYGEN_DIRECTORY}"

cd ./doc
(cat verovio.conf ; echo "OUTPUT_DIRECTORY = ${OUTPUT_DIRECTORY}") | doxygen -

# Return to the root
cd ..

<<<<<<< HEAD
# 
=======
#
>>>>>>> 26891742c0188b55a674d96671491b6334dea9c5
cd ${DOXYGEN_DIRECTORY}

echo "Configuring git push"
git config user.name "Documentation deployment"
git config user.email "${COMMIT_AUTHOR_EMAIL}"


git add -A

echo "Running git status"
git status

echo "Running git commit"
git commit -m "Auto-commit of documentation build for rism-ch/verovio-doxygen@${SHA}"

echo "Syncing from origin..."
git pull

echo "Pushing commits"
# Now that we're all set up, we can push.
<<<<<<< HEAD
# git push ${DOXYGEN_REPOSITORY} master
=======
git push ${DOXYGEN_REPOSITORY} master
>>>>>>> 26891742c0188b55a674d96671491b6334dea9c5
