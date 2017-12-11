#!/bin/bash
cd ${0%/*}/.. # go to top level project directory
BIN=`find . -name ConvexHullOfIntersections`
[ -z "$BIN" ] && echo "Compiled binary not found" && exit 1
script/show.py doc/input.1.txt doc/output.1.txt <("$BIN" < doc/input.1.txt)
