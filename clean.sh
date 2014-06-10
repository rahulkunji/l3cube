find .head > /dev/null 2>&1
if [ $? -eq 0 ]
then
rm .head
fi
find file_monitor > /dev/null 2>&1 
if [ $? -eq 0 ]
then
rm file_monitor.txt
fi
touch file_monitor.txt


