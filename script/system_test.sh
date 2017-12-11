#!/bin/bash -e

echo "System test of ConvexHullOfIntersections" >&2

[ $# -lt 2 ] && echo "Usage: $0 <SRC_DIR> <BIN_DIR>" && exit 1

SRC_DIR=$1
BIN_DIR=$2

"$BIN_DIR/ConvexHullOfIntersections" < "$SRC_DIR/doc/input.1.txt"
