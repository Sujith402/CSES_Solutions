#!/bin/bash
# to run: make_folder.sh folder file_name 

cp A.cpp "$1"
success=$?
cd "$1"

#only if copy is successful otherwise it deletes A.cpp that's normally used
if [ $success == 0 ]
then 
	mv -i A.cpp "$2.cpp"
fi