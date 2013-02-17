#!/bin/bash

# read X default urxvt config
if [ -f $HOME/.Xresources ]; then
	xrdb $HOME/.Xresources
fi

# use neo leopard layout
#setxkbmap de neo -option

xmodmap $HOME/.xmodmaprc

# add own font dir
if [ -d $HOME/.fonts ]; then
	mkfontdir $HOME/.fonts
	xset fp+ $HOME/.fonts
fi

# fuck java
wmname LG3D
export _JAVA_AWT_WM_NONREPARENTING=1

# run urxvt daemon
urxvtd -q -f

# run dwm
if [ -x $HOME/bin/startdwm ]; then
	$HOME/bin/startdwm & wmpid=$!
fi

wait $wmpid

# reset font path in case the dm won't do it
xset fp default

# unfuck java
unset _JAVA_AWT_WM_NONREPARENTING
wmname ""
