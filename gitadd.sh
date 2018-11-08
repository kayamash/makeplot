#!/bin/bash
file1='makeplot.cpp'
file2='run.sh'
file3='bsub.sh'
file4='gitadd.sh'

branch='dev_kayamash'
add='git add '
commit='git commit -m '
message='bug fix '
push='git push origin '

eval $add$file1
eval $add$file2
eval $add$file3
eval $add$file4
git commit -m "${message}"
eval $push$branch
