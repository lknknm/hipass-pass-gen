### How to build Hipass
Hipass is available to build on Linux Ubuntu or using Windows Subsystem for Linux (WSL). The following quickstart guide will help you build the program from source.
#### Download the Source
```
sudo wget https://github.com/lknknm/hipass-pass-gen/archive/refs/heads/main.zip
unzip hipass-pass-gen-main.zip
rm hipass-pass-gen-main.zip
cd hipass-pass-gen-main
```
#### Compile the code using Makefile
Hipass uses a Makefile to compile the code. The following commands can be executed from the root directory.
```
make          # Build Hipass
make all      # Build Hipass with all object files
make clean    # Clean ./build directory
make test     # Build and run test
```
By default the Makefile will output object files and binary into the `~/build` folder. You can then run the program from there:
```
cd ~/build
./hipass
```
Additionally, if you are on Linux, you may need to install xclip to get the password copied into the clipboard, if you haven't yet.
```
sudo apt-get -y install xclip
```