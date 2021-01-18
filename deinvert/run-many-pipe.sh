tmp_dir=$(mktemp -d)
mkfifo "$tmp_dir/f1" "$tmp_dir/f2"
./biquad -l 4 -f 500 -q 1.0 -r 22050 -g 0.0 -t lowpass -F s16 <"$tmp_dir/f1" & pid1=$!
./biquad -l 4 -f 500 -q 1.0 -r 22050 -g 0.5 -t highpass -F s16 <"$tmp_dir/f2" & pid2=$!
paplay --rate=44100 -r --raw --latency-msec=10 | tee "$tmp_dir/f1" "$tmp_dir/f2" > /dev/null
./splicer -F s16 -f $tmp_dir/f1 -f $tmp_dir/f2 | paplay --rate=22050 -p --raw --latency-msec=10
rm -rf "$tmp_dir"
wait $pid1 $pid2


