#!/bin/bash
cat /dev/urandom | head -n1 | hexdump -v -e '/1 "%02d "' | awk -F ' ' '{print $1}'
