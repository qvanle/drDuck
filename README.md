# Dr Duck
- CS162 projects.
- This is a solo project for the course CS162 - Introduction to Computer Science II.
- Visualize data structures.
- In this project, I will do a data visualization application.
## FEATURES 
#### Static array / dynamic array / singly, doubly, circular linked list / stack / queue
- Init from file
- Randomized data
- Insert / delete / search / update / push / pops
- Highlight code
- Custom
#### Run step by step
#### Speed up and slow down
#### Sound 
#### Graphics
#### Open with file 
- Data is storing in folder saving/
## REQUIRED
- SDL2
- SDL\_image
- SDL\_ttf
- https://github.com/nlohmann/json
- CMAKE 3.12+
- makefile
- C++17
## INSTALL 
- At first you need to install C++17, makefile, CMake:
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
## Usage
### 1. After call make, a window will pop up
- If you don't like the sound you can turn off it (the button is on the top-left of screen).
- Click "start" button to continue.
- Tutorial and donate are still in developing.
![Starting screen](docs/images/starting_screen.png)
### 2. You have 3 type of data structures 
1. Array.
2. Linked list.
3. In and out order (stack and queue).
![choose data structures](docs/images/choose_data_structures.png)
#### Array 
1. Static array.
2. Dynamic array.
![choose array](docs/images/choose_array.png)
#### Linked list 
1. Singly linked list.
2. Doubly linked list.
3. Circular linked list.
![choose linked list](docs/images/choose_linked_list.png)
#### I/O order 
1. Stack.
2. Queue.
![choose in and out order](docs/images/choose_InO_order.png)
### 3. Open file 
- After press button "open file" there will a box pop up require to enter file name.
- This file must be store in folder saving, if there don't exist that file, the window unable to do anything.
- To create new file, you have to save it with file extension "json" 
- Samples are in saving/
![open file](docs/images/open_file_input.png)
### 4. Working screen 
#### After you have choose data structures or open file, this screen will be displayed.
![working screen](docs/images/working_screen.png)
#### Move the cursor to the right, operator bar will be appeared.
![operator bar](docs/images/operator_bar.png)
#### Move the cursor to the bottom, play bar will be appeared.
1. First button will slow down animation
2. Second button (still in developing)
3. Third button will Pause/Continue animation 
4. Fourth button will go to next step (when the animation is pause) 
5. Last button will speed up the animation
![play bar](docs/images/play_bar.png)
### 5. Opeartor bar
#### New operator 
- Maximum size of static and dynamic array is 12, otherwise it's 10.
- If the input greater than maximum size, it will ignore the remainder.
![new opeartor](docs/images/new_operator.png)
#### Insert operator 
- If the size is maximum, it will do nothing.
- In stack and queue mode, this will be call push. 
![insert operator](docs/images/insert_operator.png)
![inserting](docs/images/inserting.png)
#### Delete operator 
- If the size is equal 0, it will do nothing.
- In stack and queue mode, this will be call pop.
![delete operator](docs/images/delete_operator.png)
![deleting](docs/images/deleting.png)
#### Update operator 
![update operator](docs/images/update_operator.png)
![updating](docs/images/updating.png)
#### Search operator
![search operator](docs/images/search_operator.png) 
![searching](docs/images/searching.png)
## Demonstration
- https://youtu.be/aZ55WbN_IRI
## Files/folders structures
#### Asset/
- Fonts is stored in folder fonts.
- Graphics is stored in folder graphics.
- Sound is stored in folder sound.
- Attribute folder is use to stored property of buttons, screens, input box, script, Data structures (size, position in screen, font used, graphics used, ...)
#### include/
- All file *.hpp is stored here.
#### src/ 
- All file *.cpp is stored here.
#### saving/
- All files that use for "open file" features is stored here.
#### docs
- Grading scheme is stored here.
- report is stored here.
- Open docs/html/index.html to run website version of document.
#### CMakeLists.txt
- CMake file 
#### makefile
- makefile that use to call CMAKE (this is for my text editor)
#### README.md 
## Documentation
- github repository: https://github.com/qvanle/drDuck
- Report: docs/report.pdf 
- Documentation: website version, open file docs/html/index.html
