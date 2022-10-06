#!/usr/bin/env bash
source src/defines.sh
source src/functions_bash.sh
source src/functions_bash_error.sh
source src/functions_minishell.sh
source src/functions_minishell_error.sh

TESTER_DIR=$PWD
YOUR_RESULTS=$PWD/results/YOUR_RESULTS
BASH_RESULTS=$PWD/results/BASH_RESULTS
DIFF_RESULTS=$PWD/results/DIFF

NUM_TESTS=37
NUM_ERROR_TESTS=17

printf "Your results\n"
echo $YOUR_RESULTS
echo $BASH_RESULTS
printf "\n"

i=0

# Export to give path of tester dir
export SHELL_DIR="$YOUR_RESULTS"
# Normal minishell test
until [ $i -gt $NUM_TESTS ]
do
	minishell_test_$i "$SHELL_DIR/test_$i.out" | $RUN
	let "i++"
done

i=0
#Change some rights of a file
chmod 000 utils/non_exe_file.sh

# Error minishell test
until [ $i -gt $NUM_ERROR_TESTS ]
do
	minishell_test_error_$i "$SHELL_DIR/test_error_$i.out" | $RUN 2> $YOUR_RESULTS/test_error_$i.out
	let "i++"
done

#Change it back to normal rights for Git
chmod 555 utils/non_exe_file.sh

i=0

# Bash
until [ $i -gt $NUM_TESTS ]
do
	bash_test_$i &> $BASH_RESULTS/test_$i.out
	let "i++"
done

i=0

until [ $i -gt $NUM_ERROR_TESTS ]
do
	bash_test_error_$i &> $BASH_RESULTS/test_error_$i.out
	let "i++"
done

i=0

# Check diff of test files
until [ $i -gt $NUM_TESTS ]
do
	diff $BASH_RESULTS/test_$i.out $YOUR_RESULTS/test_$i.out > $DIFF_RESULTS/result_$i.diff
	let "i++"
done

i=0

until [ $i -gt $NUM_ERROR_TESTS ]
do
	diff $BASH_RESULTS/test_error_$i.out $YOUR_RESULTS/test_error_$i.out > $DIFF_RESULTS/result_error_$i.diff
	let "i++"
done

clear

for filename in $DIFF_RESULTS/*; do
	if [ -s $filename ]; then
		echo "diff in $(basename $filename)";
	else
		rm $filename;
	fi
done;

printf "NOTE: Test_19 can have a different exit code!\n"
printf "NOTE: Test_33 has a different outcome when the user
		does it him/herself\n"
printf "NOTE: Test_error_14 can have a different exit code!
		Because of open()\n"
printf "NOTE: Test_37 can have a different exit code!\n"

printf $P
printf "\n***\n"
printf "Check results/DIFF for results\n"
printf "***\n\n"
printf $R

cd $TESTER_DIR