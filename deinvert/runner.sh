paplay --rate=44100 -r --raw --latency-msec=10 --format=float32le  | ./biquad -f 500 -q 0.5 -r 44100 -g 0.0 -t notch | paplay --rate=44100 -p --raw --latency-msec=10 --format=float32le
