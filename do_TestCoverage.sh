#!/bin/bash
cd cmake-build-debug
ctest
cd -
lcov --capture --no-external --directory ../DataMapper/ --output-file coverage.info
genhtml coverage.info --output-directory out
