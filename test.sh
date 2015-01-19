#!/bin/bash
. ./functions.sh

usage
# test function
function myfunc () {

    local myresult='some value'
    echo "$myresult"
}

result=$(myfunc)	# or result=`myfunc`
echo $result
