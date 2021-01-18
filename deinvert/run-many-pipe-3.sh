#!/bin/bash

function trap_handle_ctrl_c ()
{
	echo ""
	echo ""
	echo "Caught Ctrl-c"	
	echo "killing sub-processes"
	
	kill $pid1
	kill $pid2
	kill $pid3
	rm -rf $tmp_dir
	
	echo "Done."
	
	exit 0
}

trap "trap_handle_ctrl_c" 2

tmp_dir=$(mktemp -d)
mkfifo "$tmp_dir/in1" "$tmp_dir/in2" "$tmp_dir/out1" "$tmp_dir/out2" 
paplay --rate=22050 -r --raw --latency-msec=1 | tee "$tmp_dir/in1" "$tmp_dir/in2" > /dev/null & pid1=$!
cat $tmp_dir/in1 | ./src/deinvert -f 2300 -s 1000 -r 22050 | ./biquad -l 4 -f 600 -q 1.0 -r 22050 -g 1.0 -t lowpass -F s16 > "$tmp_dir/out1" & pid2=$!
#cat $tmp_dir/in2 | ./src/deinvert -f 2300 -s 1000 -r 22050 | ./biquad -l 4 -f 600 -q 1.0 -r 22050 -g 1.0 -t highpass -F s16 > "$tmp_dir/out2" & pid3=$!
cat $tmp_dir/in2 | ./src/deinvert -f 2300 -s 1000 -r 22050 | ./biquad -l 4 -f 600 -q 1.0 -r 22050 -g 1.0 -t highpass -F s16 > /dev/null & pid3=$!
./splicer -F s16 -f $tmp_dir/out1 | ./src/deinvert -f 2300 -s 1000 -r 22050 | paplay --rate=22050 -p --raw --latency-msec=1
rm -rf $tmp_dir

