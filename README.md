# Gettin CM to run
To get this mess to run requires some prep


## Required packages:
1. libxkcp https://github.com/XKCP/XKCP 

run command make 
```bash
make <target\>/libXKCP.so
make <target\>/libXKCP.a
```
The make file creates the .so and .a files in the bin/ folder. Copy both and rename to libkeccak.a & libkeccak.so to /usr/lib/ and to the same for the headers to the /usr/include folder. 
```bash
pwd
~/Documents/XKCP 
cp bin/<target>/libXKCP.a usr/lib/libkeccak.a
cp bin/<target>/libXKCP.so usr/lib/libkeccak.so
cp bin/<target>/libXKCP.a.headers usr/include/libkeccak.a.headers
cp bin/<target>/libXKCP.so.headers usr/include/libkeccak.so.headers
```

2. openssl 
```bash
sudo apt install libssl-dev
```
CM code package should now build. 
To test change directory to the cm-256 and run
```
cd cm-256/
make
```


## Install cmapi
The CM API (cmapi) python package can me installed 
```
make install
```
and removed with
```
make clean
```

to run local test without installing:
```
make
```