#!/bin/bash
avg=0
diff=0
result=0
gen=0
number=1
sum=0

set -e
set -o pipefail
rm -f file 2 > /dev/null
rm -f file2 > /dev/null
touch file
touch file2
while true
do
	./generator --big-superposition > file
	if [[ `diff file file2` ]]
		then
		result="$( ./lem-in < file | grep L | wc -l )"
		gen=$( tail -2 file | grep '#' | cut -d":" -f2 )
		diff=$(( result - gen ))
		echo "diff = $diff"
		sum=$(( sum + diff ))
		printf "for $number of rounds, average =  "
		echo "scale=1; $sum / $number " | bc
		number=$(( number + 1 ))
		#sleep 0.5
	fi
	cat file > file2
done
