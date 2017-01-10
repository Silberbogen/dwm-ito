#!/bin/bash
eval $(gnome-keyring-daemon -s --components=pkcs11,secrets,ssh,gpg) &
syndaemon -t -k -i 2 -d &
synclient TapButton1=1 &
conky -c ~/.dwm-ito/conkydwm-ito | while read -r; do xsetroot -name "$REPLY"; done &
nitrogen --restore &
xfce4-volumed &
xfce4-power-manager &
# Enable one of the two following screensave-methods
# xss-lock -- slock &
# xscreensaver -no-splash &
nm-applet &
unclutter &

