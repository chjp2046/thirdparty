#/bin/bash

crontab -l 2>/dev/null | sed '1,3d' > zk.crontab

command="*/10 * * * * cd $(pwd); ./zkCleanup.sh -n 5 >> ../logs/clean_history.log 2>&1"
exist=`cat zk.crontab | grep zkCleanup | wc -l`

if [ $exist -lt 1 ]; then
    echo "$command" >> zk.crontab
fi
crontab zk.crontab

rm -f zk.crontab
