#!/bin/bash 

# echo "arguments: $@"
EXEC=$1
KPL=$2

if [ -z "$EXEC" ]
then
    echo "Usage: ./script.sh <executable> <kpl>"
    exit 1
fi

while inotifywait \
    -e modify \
    -e create \
    -e delete \
    -e move \
    -e attrib \
    -r \
    -q \
    -e close_write **/{*.{c,kpl},**/*.kpl};\
    do now=$(date) && \
    clear && \
    echo "Run: $now" && \
    echo "=====" && \
    $EXEC $KPL && \
    echo "=====" && \
    echo "Run: $now";\
done
