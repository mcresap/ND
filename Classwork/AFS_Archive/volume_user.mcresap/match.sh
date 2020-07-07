#!/bin/sh

# Functions

usage() {
cat <<EOF
Usage: $(basename $0) [-n NUMBER -p PATTERN -s]

    -n NUMBER   Number of items to output (default is 10).
    -p PATTERN  Pattern to match.
    -s      Output items in sorted order.

Extracts up to the first NUMBER items from STDIN that match specified PATTERN.
EOF
    exit $1
}

# Parse command-line options

NUMBER=10
PATTERN=""
SORT=0

while [ $# -gt 0 ]; do
    case $1 in
        -n) NUMBER=$2 shift ;;
        -p) PATTERM=$2 shift ;;
        -s) SORT=1 ;;
        *) usage shift ;;
    esac
    shift
done

if [ $PATTERN ]; then
    sed -En $PATTERN 
fi

# Main execution

if [ $SORT==1 ]; then
    cut -d -$NUMBER | sort
else
    cut -d -$NUMBER
fi

