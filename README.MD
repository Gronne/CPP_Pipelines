# PLS 
PLS is a c++17 pipelines library.

## Setup 
1. Run `./RunMe.sh` located in the repository root folder. May require root access to install google test suite.
* OBS! Errors may occour if other programs is open when the commaned is run

## Compilation
1. Run `make` in the repository root folder. This will both compile the Library, Example program, and Tests.

## Run Example app
1. Example app must be run with paths to .txt files as argument, e.g. `./Example/PLS_Example.out Example/Books/Dracula.txt` from repository root.
2. File "MapReducedBooks.txt" with mapped should be located in repository root, once the application is done running.

## Run Tests
1. Tests for the files in `./Pipelines` can be run with the command `./Tests/runTests.out`