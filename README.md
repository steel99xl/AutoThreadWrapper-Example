# SillyDownloader
SD (SillyDownlaoder) main goal is to be an example of the ```AutoThreadWrapper```
in a real world use

A simple UI will let you specify links to download from and the name of the
file

The only argument options are ```SD [LINK] , [FILE_NAME]```
the partern can be repeated indeffinetly


# Requierments
C++ 17 or newer
libcurl 

# Build
```clang++ -std=c++17 -lcurl main.cpp -o sd```
