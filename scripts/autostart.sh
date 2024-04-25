#!/bin/bash

LIDSTATUS=$(cat /proc/acpi/button/lid/LID/state | awk '{print $2}')
[[ $LIDSTATUS -eq "closed" ]] && xrandr --output eDP-1 --off #&& xrandr --output DP-3-3 --auto --primary

feh --bg-scale /home/carobb/Pictures/bridge-wallpaper.jpg &

[[ ! -z "$(pgrep -f picom)" ]] && pkill picom
picom &

[[ ! -z "$(pgrep -f dwmblocks)" ]] && pkill dwmblocks
dwmblocks &
