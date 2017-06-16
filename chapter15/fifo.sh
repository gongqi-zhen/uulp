#!/bin/sh
	while true ; do
		rm -f /tmp/HOGE
		mkfifo /tmp/HOGE
		date > /tmp/HOGE
		echo "hello"
	done
