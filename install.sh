#!/bin/bash
mkdir -p build
cd build
qmake ../audiobook.pro -r CONFIG+=release PREFIX=/usr 
make
sudo make install
