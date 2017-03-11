#!/bin/bash

# Install git-hook that creates Commit-ID in commit message.

GITDIR=$(git rev-parse --git-dir)
FOR_REMOTE=${FOR_REMOTE-"origin"}

URL=$(git remote -v | \
	grep ${FOR_REMOTE} | \
	grep '(push)' | \
	awk '{print $2}' | \
	sed -Ee 's/([[:alnum:]])\/.*$/\1/')

PORT=$(sed -Ee 's/.*://' <<< "$URL")
SERVER=$(sed -Ee 's/:[[:digit:]]+$//' <<< "$URL" | \
	sed -Ee 's/(ssh:\/\/|http:\/\/|https:\/\/|git:\/\/)//')

function DOTHIS() {
	echo "${@}"
	${@}
}

DOTHIS scp -p -P $PORT ${SERVER}:hooks/commit-msg ${GITDIR}/hooks/


