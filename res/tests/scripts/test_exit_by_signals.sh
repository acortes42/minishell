#!/bin/bash
res/tests/scripts/sleep.sh 12345 &
res/tests/scripts/stop.sh $1 $!
wait $!
exit $?