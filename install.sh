#!/usr/bin/env sh

TOYCPU=toycpu
TOYCPU_STRING="Toy CPU"
DSL=asmdsl.rb
RUBY_PATH=/usr/lib64/ruby/

message() {
  echo "**** $1. ****"
}

install_message() {
  message "Installing $1"
}

building_message() {
  message "Building $1"
}

success_message() {
  message "Success"
}

install_message "Ruby DSL"
cp $DSL $RUBY_PATH$DSL
set -e
success_message

building_message $TOYCPU_STRING
make
set -e
success_message

install_message $TOYCPU_STRING
mv $TOYCPU /usr/local/bin/$TOYCPU
set -e
success_message
