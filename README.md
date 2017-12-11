= Convex Hull of Intersections

  Gabor Koszegi  -  Dec 7-14 2017

  [Problem statement](doc/problem_statement.pdf)

== Dependencies
  - C++14 compatible compiler
  - cmake >= 3.1 and ctest
  - for script/show.py python 2.7 with matplotlib

== Compilation
```
mkdir build
cd build
cmake ..
make
```

== Use cases
  - The main binary can be found at `build/ConvexHullOfIntersections`, takes input from stdin, writes output to stdout
    and some diagnostic info to stderr.
  - Comparing the expected results on the sample input:
    Run `script/compare.sh` to plot the inputs, expected outputs (in red) and the actual outputs (in black).
  - Executing the unit tests:
    Run `make test` to show only a Passed/Failed status.
    Run `build/unit_test` to get a detailed log of executed test cases and assertions.

== Project directories
  - `doc/`: Problem description and sample inputs.
  - `bin/`: Source of the main binary.
  - `include/`: Include files used by the binary and the unit tests.
  - `lib/`: Sources common to the binary and the unit tests.
  - `script/`: Scripts for running the binary and comparing the results with the expected output.
  - `test/`: Sources of the unit tests. No frameworks needed, `test/unit_test.{h,cpp}` contains all that they depend on.

== Known issues (`git grep IGNORE_TEST_CASE`)
  - Intersecting a circle with a line does not always give the expected results.
