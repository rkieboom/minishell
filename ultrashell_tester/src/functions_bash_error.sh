source src/defines.sh

function bash_test_error_0(){
	unset HOME
	cd
	echo $?
}

function bash_test_error_1(){
	cd Eyooooo
	echo $?
}

function bash_test_error_2(){
	mkdir a
	mkdir a/b
	cd a/b
	rm -r ../../a
	cd ..
	echo $?
}

function bash_test_error_3(){
	echo $NonExistingVar
	echo $?
}

function bash_test_error_4(){
	env Weeiirrddd
	echo $?
}

function bash_test_error_5(){
	cd Weyooo
	echo $?
}

function bash_test_error_6(){
	random_cmd
	echo $?
}

function bash_test_error_7(){
	cat bla
	echo $?
}

function bash_test_error_8(){
	./utils/non_exe_file.sh
	echo $?
}

function bash_test_error_9(){
	$
	echo $?
}

function bash_test_error_10(){
	$LESS$VAR
	echo $?
}

function bash_test_error_11(){
	..
	echo $?
}

function bash_test_error_12(){
	cat ultrashell.sh | grep pr | head -n 5 | cd hoi
	echo $?
}

function bash_test_error_13(){
	cat ultrashell.sh | grep pr | head -n 5 | hoi
	echo $?
}

function bash_test_error_14(){
	cat -e > test1 < test2
	echo $?
}

function bash_test_error_15(){
	/bin/ls qwerty
	echo $?
}

function bash_test_error_16(){
	printf "#\005!\006/bin/bash" > /tmp/ultrashell_test.out
	chmod +x /tmp/ultrashell_test.out
	/tmp/ultrashell_test.out
	echo $?
	rm /tmp/ultrashell_test.out
}

function bash_test_error_17(){
	unset a=6
	echo $?
}
