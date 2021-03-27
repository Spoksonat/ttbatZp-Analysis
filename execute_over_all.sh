#!/bin/bash

#source setup.sh 
make 

while read -r p; do
    cat /dev/null > input.txt
    printf "$p" | awk '{print $1}' >> input.txt
    ./MadAnalysis5job input.txt
    name=$(echo "$p" | awk '{print $2}')
    mv output.root "${name}".root
    #echo "${bar}"
done <inputs_todos.txt

root -q merge_histos.cxx
