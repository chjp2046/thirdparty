#!/bin/bash
# Copyright (c) 2011, Tencent Inc.
# All rights reserved.

# Author: rabbitliu <rabbitliu@tencent.com>
#    Xiaokang Liu <hsiaokangliu@tencent.com>
# Usage: monitor zookeeper server mem/cpu/net/disk


start_java_stat()
{
    zookeeper_pid=$(ps x | grep QuorumPeerMain | grep -v "grep" | awk '{print $1}')
    if [ -n "$zookeeper_pid" ]; then
        jstat -gcutil $zookeeper_pid 1s  >> jstat.log &
    else
        echo "no pid found. jstat quit."
    fi
}

zk_cpu_used=0
get_cpu_usage()
{
    zookeeper_pid=$(ps x | grep QuorumPeerMain | grep -v "grep" | awk '{print $1}')
    if [ -n "$zookeeper_pid" ]; then
        zk_cpu_used=`top -bn 1 -p $zookeeper_pid | grep -w java | awk '{print $9}'`
    else
        zk_cpu_used=0
    fi
}

page_fault=0
mem_used=0
swap_used=0
total_mem_used=0
get_mem_usage()
{
    zookeeper_pid=$(ps x | grep QuorumPeerMain | grep -v "grep" | awk '{print $1}')
    if [ -n "$zookeeper_pid" ]; then
        mem_used=`top -bn 1 -p $zookeeper_pid | grep -w java | awk '{print $6}'`
        page_fault=`cat /proc/$zookeeper_pid/stat | awk '{print $12}'`
    else
        mem_used=0
        page_fault=0
    fi
    swap_used="`free -m | grep Swap | awk '{print $3}'` Mb"
    mem_total=`cat /proc/meminfo | grep -w "MemTotal"| awk '{print $2}'`
    mem_free=`cat /proc/meminfo | grep -w "MemFree"| awk '{print $2}'`
    total_mem_used=`expr "scale=1; ($mem_total - $mem_free)/1024000" | bc`
}

await=0
avgrq_sz=0
get_disk_overload()
{
    diskio=$(df -h | grep -w "/data" | awk '{print $1}' | awk -F / '{print $3}')
    await=$(iostat -x | grep $diskio | awk '{printf"%d", $12*100}')
    avgrq_sz=$(iostat -x | grep $diskio | awk '{printf"%d", $10*100}')
}

net_rx=0
net_tx=0
total_cpu_used=0
interval=2
get_cpu_net_overload()
{
    cpu_log_1=$(cat /proc/stat | grep 'cpu ' | awk '{print $2" "$3" "$4" "$5" "$6" "$7" "$8}')
    sys_idle_1=$(echo $cpu_log_1 | awk '{print $4}')
    total_1=$(echo $cpu_log_1 | awk '{print $1+$2+$3+$4+$5+$6+$7}')

    eth='eth1'
    RXpre=$(cat /proc/net/dev | grep $eth | tr : " " | awk '{print $2}')
    TXpre=$(cat /proc/net/dev | grep $eth | tr : " " | awk '{print $10}')

    sleep $interval

    cpu_log_2=$(cat /proc/stat | grep 'cpu ' | awk '{print $2" "$3" "$4" "$5" "$6" "$7" "$8}')
    sys_idle_2=$(echo $cpu_log_2 | awk '{print $4}')
    total_2=$(echo $cpu_log_2 | awk '{print $1+$2+$3+$4+$5+$6+$7}')

    sys_idle=`expr $sys_idle_2 - $sys_idle_1`
    total=`expr $total_2 - $total_1`

    idle_rate=`expr $sys_idle/$total*100 | bc -l`
    idle_rate=`expr "scale=0; $idle_rate/1" | bc`
    total_cpu_used=`expr 100 - $idle_rate | bc -l`

    RXnext=$(cat /proc/net/dev | grep $eth | tr : " " | awk '{print $2}')
    TXnext=$(cat /proc/net/dev | grep $eth | tr : " " | awk '{print $10}')

    net_rx=$((${RXnext}-${RXpre}))
    net_tx=$((${TXnext}-${TXpre}))

    net_rx=`expr "scale=0; $net_rx/1024000/$interval" | bc`
    net_tx=`expr "scale=0; $net_tx/1024000/$interval" | bc`
}

from="hsiaokangliu"
to="hsiaokangliu"
title="[zookeeper warnings]"
body="unknown reason"

old_expired_session=0
new_expired_session=0
last_send_message_time=`date +%s`
session_checker()
{
    zookeeper_log="../logs/zookeeper.log"
    if [ -f $zookeeper_log ]; then
        new_expired_session=`grep "session expired" $zookeeper_log | wc -l`
        if [ $new_expired_session -gt $old_expired_session ]; then
            number=`expr $new_expired_session - $old_expired_session`
            body="$(date) session checker reports $number sessions expired."
            current_time=`date +%s`
            send_interval=`expr $current_time - $last_send_message_time`
            if [ $send_interval -ge 300 ]; then
                ./sendrtxproxy "$from" "$to" "$title" "$body"
                ./sendrtxproxy "$from" "$to" "$title" "$body" 1
                last_send_message_time=$current_time
            fi
            echo $body
        fi
        old_expired_session=$new_expired_session
    fi
}

while true; do
    echo "##########################"
    echo "Monitor time: `date +"%Y-%-m-%d %H:%M:%S"`"
    get_cpu_net_overload
    echo "total cpu used: $total_cpu_used%"
    echo "net TX: $net_rx Mb/s"
    echo "net RX: $net_tx Mb/s"

    get_cpu_usage
    echo "zookeeper cpu used: $zk_cpu_used%"
    get_mem_usage
    echo "mem used: $mem_used"
    echo "total mem used: $total_mem_used GB"
    echo "swap used: $swap_used"
    echo "page fault: $page_fault"

    get_disk_overload
    echo "disk await: $await"
    echo "disk avgrq_sz: $avgrq_sz"

#    session_checker
done
