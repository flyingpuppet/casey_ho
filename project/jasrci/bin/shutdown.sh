#!/bin/sh

count=`ps -ef |grep './jasrci' | grep -v grep | wc -l`
if [ $count -gt 0 ];then
ps -ef | grep './jasrci.sh' | grep -v grep | awk '{print $2}' | xargs kill -s 9
ps -ef | grep './jasrci' | grep -v grep | awk '{print $2}' | xargs kill -s 9
fi
