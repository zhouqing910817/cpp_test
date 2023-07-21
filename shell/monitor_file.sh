#!/bin/bash

cd $(dirname $0)
cur_dir=`pwd`
ZKOS_ROOT_PATH=/opt/zkos/platform/
#WATCH_DIR=$cur_dir  # 监听的目录路径
WATCH_DIR=/home/zeekr/jump_point  # 监听的目录路径

# 定义函数，用于读取文件内容并进行处理
function process_file {
    local file="$1"
    local filename=$2
    echo "rm -f $file"
    rm -rf $file
}

# 监听目录中的文件变化
inotifywait -m "$WATCH_DIR" -e create |
while read path action file; do
    if [[ "$action" == "CREATE" ]]; then
	# 检查文件是否已完成写入
        while fuser "$path$file" >/dev/null 2>&1; do
	         echo "等待文件写入完成[$path$file] ..."
            sleep 1
        done
	echo "$path$file 写入完成"
	{
            process_file "$path$file" $file 
	}&
    fi
done

