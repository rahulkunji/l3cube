#/bin/bash
timestamp_commit=`date`
if [ $1 = "commit" ]
then
line_count=`wc -l $2 | cut -f1 -d' '`
if [ $line_count -gt 10 ]
then
echo "total lines allowed<=10. Invalid file"
exit -1
fi
max_width=`wc -L $2 | cut -f1 -d' '`
if [ $max_width -gt 10 ]
then
echo "line length exceeds 10-- invalid file"
exit -1
fi
ls -a | grep -i ".head" 
if [ $? -ne 0 ]
then
touch .head
echo "Head file created.. first commit"
echo "name  $2" > ".head"
echo "time $timestamp_commit" >> .head
echo "version1 $line_count" >> .head
echo "$2 1" >> "file_monitor.txt"
echo "-------------------------" >> .head
cat $2 >> .head
echo "-------------------------" >> .head
else #commit one has already been done
echo "time $timestamp_commit" >> .head
x=`grep "$2" "file_monitor.txt"`
grep -v "$2" "file_monitor.txt" >file_monitor_1.txt
arr=($x)
y=`echo "${arr[1]}"`
let "y=y+1"
#echo "version$y $line_count"
echo "version$y $line_count" >> .head
echo "$2 $y" >> file_monitor_1.txt
cat file_monitor_1.txt > file_monitor.txt
rm file_monitor_1.txt
echo "-------------------------" >> .head
cat $2 >> .head
echo "-------------------------" >> .head
fi
elif [ $1 = "version" ]
then
upper_count=`grep -nr "version$3" ".head" | cut -f1 -d:` #cut field1 seperated by :" `
lower_count=`grep "version$3" ".head" | cut -f2 -d' '`
#echo $upper_count #debugging code
#echo $lower_count
let "total_count=upper_count+lower_count+2"
let "lower_count=lower_count+2"
cat .head | head -n $total_count | tail -n $lower_count
elif [ $1 = "help" ]
then
echo "./svc.sh is a script for simple version control of a file"
echo "./svc.sh commit <filename> will commit changes to a file"
echo "./svc.sh version <filename> <n> will display nth version of file"
else
echo "invalid command try ./svc.sh for documentation"
fi



