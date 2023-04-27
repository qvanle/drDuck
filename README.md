# Dr Duck
- CS162 projects
- Visualize data structures

## FEATURES 
#### Static array / dynamic array / singly, doubly, circular linked list / stack / queue
- Init from file
- Randomized data
- Insert / delete / search / update / push / pops
- Highlight code
- Custom
#### Run step by step
#### Speed up and slow down
#### Sound / GUI / multithread
## REQUIRED
- SDL2
- SDL\_image
- SDL\_ttf
- https://github.com/nlohmann/json
- CMAKE 3.12+
- makefile
- C++17
## INSTALL 
- At first you need to C++17, makefile, CMake:
```
sudo apt update 
sudo apt install build-essential
sudo apt install make 
sudo apt install cmake 
```
- Install SDL2 and external libraries
```
sudo apt install libsdl2-dev
sudo apt install libsdl2-ttf-dev
sudo apt install libsdl2-image-dev
git clone https://github.com/nlohmann/json.git 
cd json
mkdir build
cd build
cmake ..
make
sudo make install
```

- After installed, download the repository and call make.
```
git clone https://github.com/qvanle/drDuck
cd drDuck 
make 
```
