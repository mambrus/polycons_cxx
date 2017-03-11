#!/bin/bash

# Removes git-hook commit-msg wherever it hides

GITDIR=$(git rev-parse --git-dir)

function DOTHIS() {
	echo "${@}"
	${@}
}

DOTHIS rm -f ${GITDIR}/hooks/commit-msg


