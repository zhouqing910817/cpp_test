#!/bin/bash
user=alex
pass=alex
ip=$1
cmd=$2
/usr/bin/expect << EOF
set timeout 10
spawn ssh-copy-id $user@$ip
expect {
       "*password" {send "$pass\n"; exp_continue;}
       "*vail*" {send "${pass}1\n"; exp_continue;}
}
EOF

/usr/bin/expect << EOF
set timeout 10
spawn ssh $user@$ip "$cmd"
expect {
       "*password" {send "$pass\n"; exp_continue}
}
EOF
