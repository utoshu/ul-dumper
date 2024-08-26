# ul-dumper
ul-dumper is a program which dumps the hex of a file or the memory of a file

## build
build main.cpp with g++, main.cpp is located inside the src folder
```
g++ -o uldumper src/main.cpp
```

## usage

memory dump
```
uldumper {file} --mem
```

hex dump
```
uldumper {file} --hex
```