#!/bin/bash
run="root -l -b -q makeplot.cpp++"
bsub="bsub -q 30m -o ~/log/out.log -e ~/log/err.log "
clean="rm makeplot_*"
eval $bsub$run
eval $clean
