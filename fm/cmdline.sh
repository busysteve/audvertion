paplay --channels=1 --rate=44100 -r --raw --latency-msec=1 | ./afm -a 0.10 -r 44100 -c 10000 -m 4000 -b 1.0 | '/home/smathews/GNU-Radio-Projects/Scope/gnuradio-companion-runner'
