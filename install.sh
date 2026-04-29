#!/usr/bin/env sh

TOYCPU=toycpu

make
sudo mv $TOYCPU /usr/local/bin/$TOYCPU
