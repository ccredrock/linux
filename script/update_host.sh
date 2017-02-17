#!/bin/sh
#0 08 * * * /bin/sh /home/redrock/script/update_host.sh > /dev/null 2>&1

HOST=/etc/hosts
HOST_BAK=/etc/hosts.bak
FC_FLAG='#fc_host'

function reset_host()
{
    # txt link
    LINK="http://blog.yadgen.com/wp-content/uploads/2013/01/$TXT"

    # clean
    sed -i '/.*'$FC_FLAG'$/d' $HOST

    # reset
    curl $LINK |sed 's/$/ '$FC_FLAG'/g'>> $HOST

    # log
    echo "update "$TXT" on "`date` >> /home/redrock/script/update_host.log
}

if [ ! $1 = '' ]; then
    TXT=$1
    reset_host
elif [ ! -f $HOST_BAK ]; then
    TXT=`curl http://blog.yadgen.com/?page_id=585 \
        |grep hosts_ \
        |sed 's/.*>hosts/hosts/g' \
        |sed 's/<.*//g' |head -n 1`
    reset_host
fi

