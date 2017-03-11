# UI part of all beautify_project tool
# This is not even a script, stupid and can't exist alone. It is purely
# meant for being included.

BEAUTYFY_PROJECT_SH=$(basename $(readlink -f $0))
TMPDIR="/tmp/${BEAUTYFY_PROJECT_SH}/${USER}"
TS=$(date +%s.%N)
TMPFILE="${TMPDIR}/beautify_project-${TS}"
BEAUTYFY_PROJECT_DOTFILE=.beautify_project
if [ -t 0 ]; then
    PIPED_INPUT=no
else
    PIPED_INPUT=yes
fi

if ! [ -d "${TMPDIR}" ]; then
    mkdir -p "${TMPDIR}"
fi

# Get user environment settings from dot-file if exists
if [ -f ${HOME}/${BEAUTYFY_PROJECT_DOTFILE} ]; then
    eval $(
        cat "${HOME}/${BEAUTYFY_PROJECT_DOTFILE}" | \
        grep -vE '^#' | \
        grep -vE '^[[:space:]]*$'
    )
fi
if [ -f $(pwd)/${BEAUTYFY_PROJECT_DOTFILE} ]; then
    eval $(
        cat "$(pwd)/${BEAUTYFY_PROJECT_DOTFILE}" | \
        grep -vE '^#' | \
        grep -vE '^[[:space:]]*$'
    )
fi

#Hard-coded defaults if not set via DOT-file(s) or environment
#Step 1
DOT_BEAUTIFY_EXCLUDE_FILES=${BEAUTIFY_EXCLUDE_FILES-""}
DOT_BEAUTIFY_NOCLEANUP_DIRS=${BEAUTIFY_NOCLEANUP_DIRS-"tmp mnt"}
DOT_BEAUTIFY_DEBUG=${BEAUTIFY_DEBUG-"no"}
unset BEAUTIFY_EXCLUDE_FILES
unset BEAUTIFY_NOCLEANUP_DIRS
unset BEAUTIFY_DEBUG

function print_beautify_project_help() {
			cat <<EOF
NAME
        $BEAUTYFY_PROJECT_SH - Run indent on projects managed under git

SYNOPSIS
        $BEAUTYFY_PROJECT_SH [options]

DESCRIPTION
        $BEAUTYFY_PROJECT_SH

EXAMPLES
        $BEAUTYFY_PROJECT_SH

OPTIONS
    Defaults within []

    Options for $BEAUTYFY_PROJECT_SH are used to refine what is run trough
    indent and how indents mandatory back-up files.

    General options
        -h          This help
        -p          Debug print-outs show what is being done on fs while
                    exeuting. \$BEAUTIFY_DEBUG: [$DOT_BEAUTIFY_DEBUG]
        -f          Exclude file from files to be beautified by adding it to a
                    white-space delimiter list of files. Option can be given
                    several times. \$BEAUTIFY_EXCLUDE_FILES:
                    [$DOT_BEAUTIFY_EXCLUDE_FILES]
        -F          As -f but removes any default or previously added files
        -d          Exclude directory from list to be clensed from indent
                    back-up files (*.*~) by adding it to a
                    white-space delimiter list of directories. Option can be
                    given several times. \$BEAUTIFY_NOCLEANUP_DIRS:
                    [$DOT_BEAUTIFY_NOCLEANUP_DIRS]
        -D          As -d but removes any default or previously added
                    directories

OPERATION

    $BEAUTYFY_PROJECT_SH runs mostly as is without options. Just cd into any
    directory and run the script without options. Options are mainly used to
    exclude things. For convenience you are encouraged to use the control-file,
    store it the root-directory of your git-project and revision manage that
    file.

ENVIRONMENT VARIABLES

    The following environment variables can be set instead of corresponding
    option to affect the default value for that option. I.e. if both option
    and variable are set, option overrides variable.

        BEAUTIFY_EXCLUDE_FILES
        BEAUTIFY_NOCLEANUP_DIRS
        BEAUTIFY_DEBUG

FILES

    $BEAUTYFY_PROJECT_DOTFILE

        Sets default options corresponding environment variables. Presidency
        for options (higher is stronger or weakest first):

        1. Environment variable set in $BEAUTYFY_PROJECT_DOTFILE in \$HOME directory
        2. Environment variable set in $BEAUTYFY_PROJECT_DOTFILE in current directory
        3. Environment variable set in environment (exported shell variable)
        4. Corresponding option given on command line

AUTHOR
        Written by Michael Ambrus, 7 Jul 2016

EOF
}


while getopts f:F:d:D:ph OPTION; do
	case $OPTION in
	h)
		if [ -t 1 ]; then
			print_beautify_project_help $0 | less -R
		else
			print_beautify_project_help $0
		fi
		exit 0
		;;
	f)
		BEAUTIFY_EXCLUDE_FILES="${BEAUTIFY_EXCLUDE_FILES} ${OPTARG}"
		;;
	F)
		BEAUTIFY_EXCLUDE_FILES="${OPTARG}"
		;;
	d)
		BEAUTIFY_NOCLEANUP_DIRS="${BEAUTIFY_NOCLEANUP_DIRS} ${OPTARG}"
		;;
	D)
		BEAUTIFY_NOCLEANUP_DIRS="${OPTARG}"
		;;
	p)
		BEAUTIFY_DEBUG="yes"
		;;
	?)
		echo "Syntax error: options" 1>&2
		echo "For help, type: $BEAUTYFY_PROJECT_SH -h" 1>&2
		exit 2
		;;

	esac
done
shift $(($OPTIND - 1))

if [ $# -ne 0 ]; then
	echo "Syntax error: $BEAUTYFY_PROJECT_SH takes no argument" 1>&2
	echo "For help, type: $BEAUTYFY_PROJECT_SH -h" 1>&2
	exit 2
fi


#Final variable deduction
#Step 2
BEAUTIFY_EXCLUDE_FILES=${BEAUTIFY_EXCLUDE_FILES-$DOT_BEAUTIFY_EXCLUDE_FILES}
BEAUTIFY_NOCLEANUP_DIRS=${BEAUTIFY_NOCLEANUP_DIRS-$DOT_BEAUTIFY_NOCLEANUP_DIRS}
BEAUTIFY_DEBUG=${BEAUTIFY_DEBUG-$DOT_BEAUTIFY_DEBUG}
