function minishell_test_error_0(){
	echo "unset HOME"
	echo "cd"
	echo "echo \$? >> $1"
}

function minishell_test_error_1(){
	echo "cd Eyooooo"
	echo "echo \$? >> $1"
}

function minishell_test_error_2(){
	echo "mkdir a"
	echo "mkdir a/b"
	echo "cd a/b"
	echo "rm -r ../../a"
	echo "cd .."
	echo "echo \$? >> $1"
}

function minishell_test_error_3(){
	echo "echo $NonExistingVar > $1"
	echo "echo \$? >> $1"
}

function minishell_test_error_4(){
	echo "env Weeiirrddd"
	echo "echo \$? >> $1"
}

function minishell_test_error_5(){
	echo "cd Weyooo"
	echo "echo \$? >> $1"
}

function minishell_test_error_6(){
	echo "random_cmd"
	echo "echo \$? >> $1"
}

function minishell_test_error_7(){
	echo "cat bla"
	echo "echo \$? >> $1"
}

function minishell_test_error_8(){
	echo "./utils/non_exe_file.sh"
	echo "echo \$? >> $1"
}

function minishell_test_error_9(){
	echo "$"
	echo "echo \$? >> $1"
}

function minishell_test_error_10(){
	echo "$LESS$VAR"
	echo "echo \$? >> $1"
}

function minishell_test_error_11(){
	echo ".."
	echo "echo \$? >> $1"
}

function minishell_test_error_12(){
	echo "cat ultrashell.sh | grep pr | head -n 5 | cd hoi0"
	echo "echo \$? >> $1"
}

function minishell_test_error_13(){
	echo "cat ultrashell.sh | grep pr | head -n 5 | hoi"
	echo "echo \$? >> $1"
}

function minishell_test_error_14(){
	echo "cat -e > test1 < test2"
	echo "echo \$? >> $1"
}

function minishell_test_error_15(){
	echo "cd"
	echo "/bin/ls qwerty"
	echo "echo \$? >> $1"
}

function minishell_test_error_16(){
	echo 'echo " #!/bin/bash" > /tmp/ultrashell_test.out'
	echo 'chmod +x /tmp/ultrashell_test.out'
	echo '/tmp/ultrashell_test.out'
	echo "echo \$? > $1"
	echo 'rm /tmp/ultrashell_test.out'
}

function minishell_test_error_17(){
	echo "unset a=6 > $1"
	echo "echo \$? >> $1"
}
