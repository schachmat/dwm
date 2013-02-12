#!/bin/sh

# set statusbar text
if [ -x $HOME/bin/dwm-status.sh ]; then
	$HOME/bin/dwm-status.sh & statuspid=$!
fi

# set wallpaper
if [ -x $HOME/bin/wallpapers_random.sh ]; then
	$HOME/bin/wallpapers_random.sh & wallpaperpid=$!
fi

if [ -x $HOME/code/dwm/dwm ]; then
	while true; do
		$HOME/code/dwm/dwm 2> $HOME/.dwmerr
	done
else
	echo "$HOME/code/dwm/dwm executable not found" > $HOME/.dwmerr
fi

kill $statuspid
kill $wallpaperpid
