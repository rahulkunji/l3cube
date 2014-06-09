#/bin/bash
cd ~/
ls -R  | sort | uniq --count -d | tail -n +2 > temp1.txt 
while read count file_name
do
	echo -e "\n$file_name occured $count times\n" 
	var=($(find -name $file_name))
	len=${#var[@]}
	echo -e "\nDuplicates are:\n"
	printf -- "%s\n" "${var[@]}"
	echo -e "\n"
	flag=0
	for (( i=0 ; i<$len ; i++ ))
	do
		for(( j=$i+1;j<$len;j++ ))
		do
			x=${var[$i]}
			y=${var[$j]}
			DIFF=$(diff $x $y)
			if [ "$DIFF" = "" ]
			then
			flag=1
			echo -e "\n FILES $x and $y have same content\n"
	fi
		done
	done
	if [ $flag -eq 0 ]
	then
	echo -e "\nContentwise -there exist no duplicates\n"
	fi
	let "len=len-1"
	num=0
	while [ $num -ne -1 ]
	do
	echo "Enter file number to be deleted:(0 to $len) -1 to delete no more files"
	read num </dev/tty
	if [ $num -eq -1 ]
	then
	continue
	fi
	file_to_be_del=`echo ${var[$num]}`
	echo "the file you have chosen for deletion is:" 
	echo "$file_to_be_del"
	rm $file_to_be_del
	done
done <"temp1.txt"
