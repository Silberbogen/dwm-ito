#!/bin/bash
#eval $(gnome-keyring-daemon -s --components=pkcs11,secrets,ssh,gpg) &
#synclient VertEdgeScrol=1 &
syndaemon -t -k -i 2 -d &
synclient TapButton1=1 &
#synclient TapButton2=2 &
#synclient TapButton3=3 &
#synclient touchpadoff=1 &
#setxkbmap -layout de nodeadkeys &
conky -c conkydwm-ito | while read -r; do xsetroot -name "$REPLY"; done &
nitrogen --restore &
xfce4-volumed &
xfce4-power-manager &
xscreensaver -no-splash &
nm-applet &
unclutter &

