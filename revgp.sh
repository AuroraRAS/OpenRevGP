#!/bin/bash

# Initialize variables
tty=""
btdev=""
slot=""
group=""
config=""
detection=""
detection_clean=""
detection_clean_all=""
get=""
put=""

# Parse command line arguments
while [[ $# -gt 0 ]]
do
    key="$1"
    case $key in
        -d|--dev)
        if [[ $2 == tty* ]]
        then
            tty="$2"
        else
            btdev="$2"
        fi
        shift
        shift
        ;;
        -s|--slot)
        slot="$2"
        shift
        shift
        ;;
        -sg|--slot-group)
        group="$2"
        shift
        shift
        ;;
        -sc|--slot-config)
        config="$2"
        shift
        shift
        ;;
        -dg|--detection-get)
        detection="$2"
        shift
        shift
        ;;
        -dc|--detection-clean)
        detection_clean="true"
        shift
        ;;
        -dca|--detection-clean-all)
        detection_clean_all="true"
        shift
        ;;
        -g|--get)
        get="$2"
        shift
        shift
        ;;
        -p|--put)
        put="$2"
        shift
        shift
        ;;
        *)
        echo "Unknown option: $1"
        exit 1
        ;;
    esac
done

serialport="/dev/$tty"
if [ "$btdev" != "" ];then
    serialportName='rfcomm0'
    serialport="/dev/$serialportName"
    [ -c "$serialport" ] || (sudo rfcomm -r bind $serialportName "$btdev" && sleep 0.1)
fi
stty -F $serialport 0:0:18b2:0:0:0:0:0:0:0:1:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0

chat -t 10 -f chatscripts/init.chat < $serialport > $serialport && sleep 0.1 || exit

if [ "$group" != "" ]; then
    group=$group chat -E -t 10 -f chatscripts/group.chat < $serialport > $serialport && sleep 0.1 || exit
fi

if [ "$slot" != "" ]; then
    slot=$slot chat -E -t 10 -f chatscripts/slot.chat < $serialport > $serialport && sleep 0.1 || exit
fi

if [ "$detection" != "" ];then
    chat -t 10 -f chatscripts/detec.chat < $serialport > $serialport && sleep 0.1 && \
        rx -X $detection < $serialport > $serialport && sleep 0.1
fi

if [ $detection_clean_all ];then
    chat -E -t 10 -f chatscripts/detec_clear_all.chat < $serialport > $serialport && sleep 0.1 || exit
elif [ $detection_clean ];then
    chat -E -t 10 -f chatscripts/detec_clear_activated.chat < $serialport > $serialport && sleep 0.1 || exit
fi

if [ "$get" != "" ]; then
    chat -t 10 -f chatscripts/get.chat < $serialport > $serialport && sleep 0.1 && \
        rx -X $get < $serialport > $serialport
fi

if [ "$put" != "" ]; then
    chat -t 10 -f chatscripts/put.chat < $serialport > $serialport && sleep 0.1 && \
        rx -X $put < $serialport > $serialport
fi

