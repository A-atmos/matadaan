# Matadaan: A Decentralized Voting System

> A PoC of Blockchain Technology

***Due to the epoll and socket programming used in this project, it can only be run on Linux systems.***

## Initialization:


`matadaan` is a decentralized voting system build from scratch using C++. It uses the concepts of OOP in C++, BlockChain Technology and the general concept of Voting System.

*Preferred IDE: **CLion*** 

**Use CMakeLists.txt or [build.sh](./build.sh) to build the Project.**
### Build:
Check if the required packages are available in the system
```
cmake CMakeLists.txt
```
Create a Makefile
```
cmake .
```
Compiles and creates a `Matadaan` named executable file
```
make
```
`./Matadaan`: to run the executable file
```
./Matadaan
```

## External Libraries Used:
- [openssl](https://github.com/openssl/openssl) for hashing
- [qt](http://www.qt.io/) for GUI
- [json.hpp](https://github.com/nlohmann/json) for processing json data for the REST API
