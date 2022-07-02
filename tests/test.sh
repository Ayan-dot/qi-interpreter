#!/usr/bin/bash


RED="\033[0;31m"
BLUE="\033[0;34m"
NC="\033[0m"
TEST_FOLDER_NAME="tests"
QI="../../build/qi"

cd "$TEST_FOLDER_NAME"
FOLDER_NAMES=$(ls -1 -d */)
failed_tests=0

for folder_name in $FOLDER_NAMES
do
    cd "$folder_name" || exit 1
    test_number=1
    passed_test_count=0
    echo -e "$BLUE[info]$NC running tests for $folder_name"

    while [[ -f "$test_number-in" ]] && [[ -f "$test_number-out" ]] && [[ -f "code.qi" ]]
    do
        $QI "code.qi" < "$test_number-in" > "$test_number-test" || ""
        if ! cmp -s "$test_number-out" "$test_number-test"; then
            echo -e "$RED[error]$NC $folder_name: test $test_number failed"
            echo "expected contents ($folder_name$test_number-out):"
            cat "$test_number-out" || exit 0
            echo "actual contents ($folder_name$test_number-test):"
            cat "$test_number-test" || exit 0
            passed_test_count=$(( $passed_test_count - 1 ))
            failed_tests=$(( $failed_tests + 1 ))
        fi
        test_number=$((test_number + 1))
    done

    total_test_count=$((test_number - 1))
    passed_test_count=$(( $passed_test_count + $total_test_count ))
    echo -e "$BLUE[info]$NC $folder_name: $passed_test_count/$total_test_count tests passed"

    cd ".."
done

cd ".."
echo -e "$BLUE[info]$NC ran all tests"
if [[ $failed_tests == 0 ]]; then
    exit 0
else
    exit 1
fi
