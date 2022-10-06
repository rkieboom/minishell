source src/defines.sh

function minishell_test_0(){
	echo "pwd > $1"
	echo "echo \$? >> $1"
}

function minishell_test_1(){
	echo "cd ../../../../../.. > $1"
	echo "cd ../../../../../.."
	echo "echo \$? >> $1"
	echo "pwd >> $1"
}

function minishell_test_2(){
	echo "cd ~"
	echo "echo \$? > $1"
	echo "pwd >> $1"
}

function minishell_test_3(){
	echo "cd ~/Desktop"
	echo "echo \$? >> $1"
	echo "pwd >> $1"
}

function minishell_test_4(){
	echo "cd"
	echo "echo \$? >> $1"
	echo "pwd >> $1"
}

function minishell_test_5(){
	export HOMEEPIC=EPIC
	echo "export HOME=$TESTER_HOME"
	echo "cd"
	echo "echo \$? > $1"
	echo "pwd >> $1"
}

function minishell_test_6(){
	echo "cd"
	echo "cd .. cool swag"
	echo "echo \$? > $1"
	echo "pwd >> $1"
}

function minishell_test_7(){
	echo "cd"
	echo "cd .."
	echo "cd"
	echo "cd - > $1"
	echo "echo \$? >> $1"
}

function minishell_test_8(){
	echo "echo > $1"
	echo "echo \$? >> $1"
}

function minishell_test_9(){
	echo "echo $PATH > $1"
	echo "echo \$? >> $1"
}

function minishell_test_10(){
	echo "echo ~ > $1"
	echo "echo \$? >> $1"
}

function minishell_test_11(){
	echo "echo -n -n -nnnn -nnnnm > $1"
	echo "echo \$? >> $1"
}

function minishell_test_12(){
	echo "echo -n -nnn hello -n > $1"
	echo "echo \$? >> $1"
}

function minishell_test_13(){
	echo "env > $1"
	echo "echo \$? >> $1"
}

function minishell_test_14(){
	echo "cd /tmp"
	echo "export ls=\"ls -l\""
	echo "\$ls > $1"
	echo "echo \$? >> $1"
}

function minishell_test_15(){
	echo "export ls=\"ls -l\""
	echo "echo \$ls > $1"
	echo "echo \$? >> $1"
}

function minishell_test_16(){
	echo "export var=a"
	echo "export \$var=test"
	echo "echo \$var \$a > $1"
	echo "echo \$? >> $1"
}

function minishell_test_17(){
	echo "export test1"
	echo "env | grep test1 > $1"
	echo "echo \$? >> $1"
}

function minishell_test_18(){
	echo "export test2=test"
	echo "env | grep test2 > $1"
	echo "echo \$? >> $1"
}

function minishell_test_19(){
	echo "export test3=\$HOME"
	echo "env | grep test3 > $1"
	echo "echo \$? >> $1"
}

function minishell_test_20(){
	echo "echo ~ > $1"
	echo "echo \$? >> $1"
}

function minishell_test_21(){
	echo "echo \"bip | bip ; coyotte > <\" > $1"
	echo "echo \$? >> $1"
}

function minishell_test_22(){
	echo "echo $USER$wouw$USER$USERtest$USER > $1"
	echo "echo \$? >> $1"
}

function minishell_test_23(){
	echo "echo \"\"abc\"\" > $1"
	echo "echo \$? >> $1"
}

function minishell_test_24(){
	echo "export ls=\"ls -l\""
	echo "echo \"\$ls\" > $1"
	echo "echo \$? >> $1"
}

function minishell_test_25(){
	echo "ls | exit > $1"
	echo "echo \$? >> $1"
}

function minishell_test_26(){
	echo "> test | echo hoi > $1"
	echo "echo \$? >> $1"
}

function minishell_test_27(){
	echo "export var=\"    truc  \""
	echo "echo \$var | cat -e > $1"
	echo "echo \$? >> $1"
}

function minishell_test_28(){
	echo "echo \"$test""Makefile\" > $1"
	echo "echo \$? >> $1"
}

function minishell_test_29(){
	echo "echo \"$test\"Makefile > $1"
	echo "echo \$? >> $1"
}

function minishell_test_30(){
	echo "echo \"$test\" Makefile > $1"
	echo "echo \$? >> $1"
}

function minishell_test_31(){
	echo "export \$random > $1"
	echo "echo \$? >> $1"
}

function minishell_test_32(){
	echo "export TEST=\"c -c\""
	echo "echo 'test xD' | w\$TEST > $1"
	echo "echo \$? >> $1"
}

function minishell_test_33(){
	echo "export TEST=\"l s \""
	echo "echo l\$TEST\"s\" >> $1"
	echo "export TEST=\"\""
	echo "echo l\$TEST\"s\" >> $1"
	echo "export TEST=\"     \""
	echo "echo l\$TEST\"s\" >> $1"
	echo "export TEST=\" l s\""
	echo "echo l\$TEST\"s\" >> $1"
	echo "export TEST=\" l s \""
	echo "echo l\$TEST\"s\" >> $1"
	echo "export TEST=\" HALLO? XDDD  'we  zijn     hier' misschien, athans...   \""
	echo "echo \$TEST >> $1"
}

function minishell_test_34(){
	echo "echo '-n ' -nnn hello -n > $1"
	echo "echo \$? >> $1"
}

function minishell_test_35(){
	echo "ls -l / | cat | wc -l > $1"
	echo "echo \$? >> $1"
}

function minishell_test_36(){
	echo "unset HOME"
	echo "cd .. > $1"
	echo "echo \$? >> $1"
}

function minishell_test_37(){
	echo "cd"
	echo "/bin/ls > $1"
	echo "echo \$? >> $1"
}
