# 进程守护脚本

```shell
#!/bin/sh
while true; do
    server=`ps aux | grep 进程关键字 | grep -v grep`
    if [ ! "$server" ]; then
        # 启动服务的命令
        sleep 10
    fi
    sleep 5
done
```

