#!/bin/sh
while true; do
    server=`ps aux | grep test_code | grep -v grep`
    if [ ! "$server" ]; then
        ./test_code &
    fi
    sleep 5
done
