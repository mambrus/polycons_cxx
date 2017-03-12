#! /bin/bash
#
# Copyright (C) Michael Ambrus,
#               Sigma Connectivity AB, 2016
# All rights, including trade secret rights, reserved.
#
# Run indent using the projects code-convention rules
#

function test_prerequisites_installed() {
	if [ "X$(which indent)" == "X" ]; then
		exec 3>&1 2>&1
		cat <<EOF
Please install indent. On Ubuntu 14.04.3 LTS this can be done as
follows:

sudo apt-get install indent


EOF
		exec 3>&-
		exit 1
	fi
}

SCRIPT_DIR=$(dirname $(readlink -f $0))
source ${SCRIPT_DIR}/beautify_project_ui.sh
TOP=$(git rev-parse --show-toplevel)

# --------- Write code here --------------------------
test_prerequisites_installed

pushd "${TOP}" >/dev/null

# Ignore git submodule replies.
function no_submod() {
	cat -- | grep -Eve '\((new commits|modified content|untracked content).*\)[[:space:]]*$'
}

function doit() {
	local HIDE_STDERR=$2

	if [ $BEAUTIFY_DEBUG == 'yes' ]; then
		echo ">>> Executing: ${1}"
	fi
	if [ "X${HIDE_STDERR}" == 'Xyes' ]; then
		( eval "${1}" ) 2>/dev/null
	else
		eval "${1}"
	fi
}

# Sanity and precaution tests
if ! [ -f .indent.pro ]; then
	exec 3>&1 2>&1
	echo "Indent control file [.indent.pro] missing from git root" \
		"directory: ${TOP}"
	echo "Refusing to run."
	exec 3>&-
	popd >/dev/null
	exit 1
fi
if ! [ -a .git ]; then
	exec 3>&1 2>&1
	echo "Git root-directory [${TOP}] is not a git repository."
	echo "Fatal script error. Please bug-rapport!"
	echo "Refusing to continue."
	exec 3>&-
	popd >/dev/null
	exit 1
fi
if [ "X$(git status | \
	grep -Ee '^[[:space:]]modified:' | no_submod )" != "X" ]; then

	exec 3>&1 2>&1
	echo "You have modified files. Please commit or stash first:"
	git status | \
		grep -Ee '^[[:space:]]modified:' | no_submod
	exec 3>&-
	popd >/dev/null
	exit 1
fi

# The actual beautify run
if [ "X$BEAUTIFY_EXCLUDE_FILES" != "X" ]; then
	#Trim leading and trailing whitespace and expand spaces between with " -e "
	_EXCLUDE_FILES=$(xargs <<< $BEAUTIFY_EXCLUDE_FILES | sed -Ee 's/[[:space:]]+/ -e /g')

	doit "git ls-files '*.cpp' '*.h' | grep -ve $_EXCLUDE_FILES | xargs -I'{}' indent '{}'"
else
	doit "git ls-files '*.cpp' '*.h' | xargs -I'{}' indent '{}'"
fi

#Clean-up backups as they are not needed (git keeps track for us)
if [ "X$BEAUTIFY_NOCLEANUP_DIRS" != "X" ]; then
	_EXCLUDE_DIRS=$(echo "$BEAUTIFY_NOCLEANUP_DIRS" | sed -Ee 's/([^[:space:]]+)/*\/\1\/*/g')
	_EXCLUDE_DIRS=$(xargs <<< $_EXCLUDE_DIRS | sed -Ee 's/[[:space:]]+/ ! -path /g')
	doit "find .  \( -iname '*.*~' ! -path $_EXCLUDE_DIRS \) | xargs -I'{}' rm '{}'" yes
else
	doit "find . -iname '*.*~' | xargs -I'{}' rm '{}'"
fi

#Output which files have been changed
if [ "X$(git status | \
	grep -Ee '^[[:space:]]modified:' | no_submod )" != "X" ]; then

	echo "Changed files, please inspect before committing:"
	git status | \
		grep -Ee '^[[:space:]]modified:' | no_submod
fi

popd >/dev/null
