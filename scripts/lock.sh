#!/bin/sh

BLANK='#00000000'
CLEAR='#ffffff22'
DEFAULT='#cccccccc'
TEXT='#aaaaaaee'
WRONG='#880000bb'
KEY='#66B766bb'
BKSPC='#D63232bb'
VERIFYING='#eeeeeebb'

i3lock \
  --insidever-color=$CLEAR     \
  --ringver-color=$VERIFYING   \
  --insidewrong-color=$CLEAR   \
  --ringwrong-color=$WRONG     \
  --inside-color=$BLANK        \
  --ring-color=$DEFAULT        \
  --line-color=$BLANK          \
  --separator-color=$DEFAULT   \
  --verif-color=$TEXT          \
  --wrong-color=$TEXT          \
  --time-color=$TEXT           \
  --date-color=$TEXT           \
  --layout-color=$TEXT         \
  --keyhl-color=$KEY           \
  --bshl-color=$BKSPC          \
  --blur 5                     \
  --clock                      \
  --indicator                  \
  --time-str="%H:%M:%S"        \
  --date-str="%A, %Y-%m-%d"    \
  --radius 150 &

sleep 600 && sudo systemctl suspend
