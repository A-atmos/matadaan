#!/usr/bin/env bash

echo "Checking the Required Packages";
cmake CMakeLists.txt;
echo "Creating a MakeFile";
cmake .;
echo "Compiling the code";
make;
echo "Running the project!";
./Matadaan
