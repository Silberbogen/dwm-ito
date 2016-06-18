#!/bin/bash
#eval $(gnome-keyring-daemon -s --components=pkcs11,secrets,ssh,gpg) &
syndaemon -t -k -i 2 -d &
synclient TapButton1=1 &
conky -c conkydwm-ito | while read -r; do xsetroot -name "$REPLY"; done &
nitrogen --restore &
xfce4-volumed &
xfce4-power-manager &
xss-lock -- slock &
nm-applet &
unclutter &

