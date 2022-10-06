source src/defines.sh

function bash_test_0(){
	pwd
	echo $?
}

function bash_test_1(){
	cd ../../../../../..
	echo $?
	pwd
}

function bash_test_2(){
	cd ~
	echo $?
	pwd
}

function bash_test_3(){
	cd ~/Desktop
	echo $?
	pwd
}

function bash_test_4(){
	cd
	echo $?
	pwd
}

function bash_test_5(){
	export HOMEEPIC=EPIC
	export HOME=$TESTER_HOME
	cd
	echo $?
	pwd
}

function bash_test_6(){
	cd
	cd .. cool swag
	echo $?
	pwd
}

function bash_test_7(){
	cd -
	echo $?
}

function bash_test_8(){
	echo
	echo $?
}

function bash_test_9(){
	echo $PATH
	echo $?
}

function bash_test_10(){
	echo ~
	echo $?
}

function bash_test_11(){
	echo -n -n -nnnn -nnnnm
	echo $?
}

function bash_test_12(){
	echo -n -nnn hello -n
	echo $?
}

function bash_test_13(){
	env
	echo $?
}

function bash_test_14(){
	cd /tmp
	export ls="ls -l"
	$ls
	echo $?
}

function bash_test_15(){
	echo $ls
	echo $?
}

function bash_test_16(){
	export var=a
	export $var=test
	echo $var $a
	echo $?
}

function bash_test_17(){
	export test1
	env | grep test1
	echo $?
	unset test1
}

function bash_test_18(){
	export test2=test
	env | grep test2
	echo $?
	unset test2
}

function bash_test_19(){
	export test3=$HOME
	env | grep test3
	echo $?
	unset test3
}

function bash_test_20(){
	echo ~
	echo $?
}

function bash_test_21(){
	echo "bip | bip ; coyotte > <"
	echo $?
}

function bash_test_22(){
	echo "$USER$wouw$USER$USERtest$USER"
	echo $?
}

function bash_test_23(){
	echo ""abc""
	echo $?
}

function bash_test_24(){
	export ls="ls -l"
	echo "$ls"
	echo $?
	unset ls
}

function bash_test_25(){
	ls | exit
	echo $?
}

function bash_test_26(){
	> test | echo hoi
	echo $?
}

function bash_test_27(){
	export var="     truc  "
	echo $var | cat -e
	echo $?
}

function bash_test_28(){
	echo "$test""Makefile"
	echo $?
}

function bash_test_29(){
	echo "$test"Makefile
	echo $?
}

function bash_test_30(){
	echo "$test" Makefile
	echo $?
}

function bash_test_31(){
	export $random
	echo $?
}

function bash_test_32(){
	export TEST="c -c"
	echo 'test xD' | w$TEST
	echo $?
}

function bash_test_33(){
	export TEST="l s "
	echo l$TEST"s"
	export TEST=""
	echo l$TEST"s"
	export TEST="     "
	echo l$TEST"s"
	export TEST=" l s"
	echo l$TEST"s"
	export TEST=" l s "
	echo l$TEST"s"
	export TEST=" HALLO? XDDD  'we  zijn     hier' misschien, athans...   "
	echo $TEST
}

function bash_test_34(){
	echo '-n ' -nnn hello -n
	echo $?
}

function bash_test_35(){
	ls -l / | cat | wc -l
	echo $?
}

function bash_test_36(){
	unset HOME
	cd ..
	echo $?
	export HOME=$TESTER_HOME
}

function bash_test_37(){
	cd
	/bin/ls
	echo $?
}
