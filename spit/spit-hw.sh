#!/bin/bash

echo == CPU power

cat /proc/cpuinfo | grep "name" | sort | uniq -c
cat /sys/devices/system/cpu/cpufreq/*/scaling_governor | sort | uniq -c

echo == drive scheduler

sort /sys/block/sd*/queue/scheduler | uniq -c


lshw -c network -businfo | sed 's/pci\@0000://g' >/tmp/nicinfo 2>/dev/null
lshw -c video -businfo | sed 's/pci\@0000://g' >/tmp/gpuinfo 2>/dev/null

IPs=$(ip addr list | grep "state UP" | awk '{print $2}' | tr -d ':')

echo ====
ip addr list | grep "state UP"

for f in $IPs
do

echo === $f ===

grep -w $f /tmp/nicinfo
pci=$(grep -w $f /tmp/nicinfo | awk '{print $1;}')

lspci -s $pci -vv | egrep -i '(numa|GT/s)'
(devlink dev info pci/0000:$pci | grep fw\.) 2>/dev/null
(ethtool $f | grep Speed) 2>/dev/null

done


for f in $(grep display /tmp/gpuinfo | awk '{print $1}')
do

    echo ==== $f ====

    lspci -s $f -vv | egrep -i '(control|numa|GT/s)'
done
