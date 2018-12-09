#!/bin/bash

if [ `cat list.h | md5sum | cut -f1 -d' '` = "cee68fce96c71f19ecef5db1f4006782" ]; then
	exit 0
else
	echo "list.h has been modified. Please re-download it from assignments"
	exit 1
fi

