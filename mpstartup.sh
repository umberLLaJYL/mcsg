#!/bin/bash

# default configuration
Bootdelay=0
Server=default
ServerPort0=4001
ServerPort1=4001
NetworkEth0=ens33
NetworkEth0IP=192.168.1.147
NetworkEth0Gateway=192.168.1.1
NetworkEth0Netmask=255.255.255.0
NetworkEth1=disable
Can=disable

ConfDir=/mnt/hgfs/MCSG/mpinetsvr.conf

if [ ! -f "$ConfDir" ]; then
    echo "no configuration file"
    exit 1
fi
# start mpser
var=`grep "^[\$]Bootdelay" "$ConfDir" | grep -o "[^ =]*$"`
if [ -n "$var" ]; then
    Bootdelay = $var
    sleep $Bootdelay
fi
./bin/mpser &
# initialize network with configuration file
if [ "$1" = "-o" ]; then
    grep "^[\$]NetworkEth0" "$ConfDir" | while read -r line; do
        if [[ "$line" =~ ^[\$]NetworkEth0( ) ]]; then
            var=`echo $line | grep -o "[^ =]*$"`
            if [ -n "$var" ]; then
                NetworkEth0="$var"
                echo $NetworkEth0
            fi
        elif [[ "$line" =~ ^[\$]NetworkEth0IP ]]; then
            var=`echo $line | grep -o "[^ =]*$"`
            if [ -n "$var" ]; then
                NetworkEth0IP="$var"
                echo $NetworkEth0IP
                ifconfig $NetworkEth0 $NetworkEth0IP
            fi
        elif [[ "$line" =~ ^[\$]NetworkEth0Gateway ]]; then
            var=`echo $line | grep -o "[^ =]*$"`
            if [ -n "$var" ]; then
                NetworkEth0Gateway="$var"
                echo $NetworkEth0Gateway
                route add default gw $NetworkEth0Gateway
            fi
        elif [[ "$line" =~ ^[\$]NetworkEth0Netmask ]]; then
            var=`echo $line | grep -o "[^ =]*$"`
            if [ -n "$var" ]; then
                NetworkEth0Netmask="$var"
                echo $NetworkEth0Netmask
                ifconfig $NetworkEth0 netmask $NetworkEth0Netmask
            fi
        fi
    done
fi
# initialize parameter of server
grep "^[\$Server]" "$ConfDir" | while read -r line; do
    if [[ "$line" =~ ^[\$]Server( ) ]]; then
        var=`echo $line | grep -o "[^ =]*$"`
        if [ -n "$var" ]; then
            Server="$var"
            echo $Server
        fi
    elif [[ "$line" =~ ^[\$]ServerPort0 ]]; then
        var=`echo $line | grep -o "[^ =]*$"`
        if [ -n "$var" ]; then
            ServerPort0="$var"
            echo $ServerPort0
        fi
    elif [[ "$line" =~ ^[\$]ServerPort1 ]]; then
        var=`echo $line | grep -o "[^ =]*$"`
        if [ -n "$var" ]; then
            ServerPort1="$var"
            echo $ServerPort1
        fi
    fi
done
./mpargs "--$Server=$ServerPort0 $ServerPort1" &
