#!/bin/bash 

FILES=$(find . -executable -type f \( -iname "*" ! -iname "*.sh" \) )
for file in $FILES
do
	echo -----RUN----- $file
	${file}
	if [$? -ne 0]
	then
		exit $?
	fi
done

