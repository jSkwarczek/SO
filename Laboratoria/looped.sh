#!/bin/bash

if [[ $# -ne 1 ]]; then
    echo "ERROR: Invalid number of arguments!"
    exit 1
fi

cd "$1" || exit 1

links=$(find . -type l)

looped=()

for link in $links; do

    visited=()
    length=0
    path=$(echo $link | cut -d'/' -f 2)

    if [[ "${looped[@]}" =~ "$path" ]]; then
        continue
    fi

    while [[ -L "$(readlink "$path")" ]]; do
        if [[ "${visited[@]}" =~ "$(readlink "$path")" ]]; then
            looped+=("${visited[@]}")
            echo "Pętla: ${visited[@]} ${visited[0]}"
            echo -e "Długość: $length\n"
            break
        else
            path=$(readlink "$path")
            length=$((length + 1))
            visited+=("$path")
        fi
    done
done
