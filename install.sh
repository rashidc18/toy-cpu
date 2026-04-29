#!/usr/bin/env sh

TOYCPU=toycpu
TOYCPU_STRING="Toy CPU"
DSL=asmdsl.rb

echo "** Installing Ruby DSL."
cp $DSL /usr/lib64/ruby/$DSL

echo "** Building $TOYCPU_STRING."
make

echo "** Installing $TOYCPU_STRING."
mv $TOYCPU /usr/local/bin/$TOYCPU
