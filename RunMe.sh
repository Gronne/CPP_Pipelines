#!/bin/bash
#Install developer environment

SOURCEDIR=$(pwd)

sudo apt-get install libgtest-dev
sudo apt-get install cmake

cd ~
cd /usr/src/gtest

sudo cmake CMakeLists.txt
sudo make

sudo cp *.a /usr/lib 

cd ~
cd $SOURCEDIR

cmake CMakeLists.txt 
make 