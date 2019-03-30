#!/bin/bash
cd cmake-build-debug
ctest
cd -
lcov --capture --no-external --directory ../OrderManager-v1/ --output-file coverage.info
genhtml coverage.info --output-directory out
firefox out/index.html &