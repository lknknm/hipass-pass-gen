### How to build Hipass
Hipass is available to build on Linux Ubuntu or using Windows Subsystem for Linux (WSL). The following quickstart guide will help you build the program from source.
#### Download the Source
```
gh repo clone lknknm/hipass-pass-gen
cd hipass-pass-gen
code .
```
#### Compile the code using Makefile
Hipass uses a Makefile to compile the code. It may be necessary to install the latest GCC compiler. The following commands can be executed from the root directory.
```
make           # Build Hipass
make all       # Build Hipass with all object files
make clean     # Clean ./build directory
make test      # Build and run test
make install   # Install Hipass and add it to PATH
make uninstall # Uninstall Hipass
```
By default the Makefile will output object files and binary into the `~/build` folder. You can then run the program from there:
```
cd ~/build
./hipass
```
If you install Hipass with `sudo make install`, just prompt it from anywhere:
```
hipass --passphrase '%'
```
To update Hipass, just pull the code from the repository in your hipass folder and run `sudo make install` again:
```
git pull origin main
sudo make install
```

Additionally, if you are on Linux, you may need to install xclip to get the password copied into the clipboard, if you haven't yet.
```
sudo apt-get -y install xclip
```