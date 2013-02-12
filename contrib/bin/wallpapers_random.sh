#!/bin/sh

while true; do
	find $HOME/bilder/wallpaper/current -type l -print0 | shuf -n1 -z | xargs -0 feh --bg-fill
	sleep 15m
done
