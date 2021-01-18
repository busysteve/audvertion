tmp_dir=$(mktemp -d)
mkfifo "$tmp_dir/f1" "$tmp_dir/f2"
command1 <"$tmp_dir/f1" & pid1=$!
command2 <"$tmp_dir/f2" & pid2=$!
tee "$tmp_dir/f1" "$tmp_dir/f2" | command3
rm -rf "$tmp_dir"
wait $pid1 $pid2


