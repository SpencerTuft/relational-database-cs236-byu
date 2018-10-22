#!/bin/bash

BLUE=$'\e[0;34m'
RED=$'\e[0;31m'
GREEN=$'\e[0;32m'
NORMAL=$'\e[0m'

declare EXE_PATH="./cmake-build-debug/datalog-parser-cs236-byu"
declare IN_PATH="./test/in"
declare OUT_PATH="./test/out"
declare EXPECTED_PATH="./test/expected"

declare -a fileNames=("30" "33" "35" "36" "37" "41" "42" "43" "44" "61" "62")

printf "%s\n" "${BLUE}Starting unit tests${NORMAL}"
for name in "${fileNames[@]}"
do
    ${EXE_PATH} "${IN_PATH}/${name}.txt" | tee "${OUT_PATH}/${name}.txt"
    if !(cmp -s -- "${OUT_PATH}/${name}.txt" "${EXPECTED_PATH}/${name}.txt")
    then
        printf "%s" "${RED}FAILED${NORMAL} "
        tkdiff ${OUT_PATH}/${name}.txt ${EXPECTED_PATH}/${name}.txt
    else
        printf "%s" "${GREEN}PASSED${NORMAL} "
    fi

    printf "%s\n" "test for file ${name}.txt"
done
printf "%s\n" "${BLUE}Unit testing complete${NORMAL}"


######## Using the code below to populate test case files ########

#printf "%s\n" "${BLUE}Creating test files${NORMAL}"
#for name in "${fileNames[@]}"
#do
#    touch "${IN_PATH}/${name}.txt"
#    touch "${OUT_PATH}/${name}.txt"
#    touch "${EXPECTED_PATH}/${name}.txt"
#done
#printf "%s\n" "${BLUE}Done${NORMAL}"

##################################################################