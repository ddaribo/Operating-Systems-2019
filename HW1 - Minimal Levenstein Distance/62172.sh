#!/bin/bash

sed -i -r 's/./\L&/g' text.txt
sed -i -r 's/\s/\n/g' text.txt
sed -i -r 's/'\[\[:punct:\]\]'//g' text.txt
sort -u text.txt -o text.txt
grep -v -Fwf dic.txt text.txt | tee text.txt 1> /dev/null
for i in $(cat text.txt); do echo "$i:" $(tre-agrep -99 -B -w -s $i dic.txt); done | cut -d ' ' -f 1,2 
