# fdumper
fdumper (funny dumper) is a program which dumps the hex of a file or  the memory of a file

## build
build main.cpp with g++, main.cpp is located inside the src folder
```
g++ -o fdumper src/main.cpp
```

## usage

memory dump
```
fdumper {file} --mem
```

hex dump
```
fdumper {file} --hex
```