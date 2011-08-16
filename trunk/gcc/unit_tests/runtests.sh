#!/bin/bash 

FILES=$(find . -executable -type f \( -iname "*" ! -iname "*.sh" \) )
for file in $FILES
do
	echo -----RUN----- $file
	${file}
	if [ $? -ne 0 ]
	then
    echo TEST FAILED!   
		exit 1
	fi
done

