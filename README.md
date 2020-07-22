# Conways Game Of Life
[Conways Game Of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) written in C++ with a Qt5 based GUI.

![alt text](https://github.com/jleipus/Game-Of-Life/blob/master/screencap.png?raw=true)

###### How to run:
1) Download [release](https://github.com/jleipus/Game-Of-Life/blob/master/release) folder
2) Run [GameOfLife.exe](https://github.com/jleipus/Game-Of-Life/blob/master/release/GameOfLife.exe) from release folder  
or open [.pro](https://github.com/jleipus/Game-Of-Life/blob/master/src/GameOfLife.pro) file in QtCreator, build and run game from there.

###### Unit test:
All unit tests are written in the [tests.cpp](https://github.com/jleipus/Game-Of-Life/blob/master/src/tests/tests.cpp) file. To run the the tests, either run the [executable file](https://github.com/jleipus/Game-Of-Life/blob/master/src/tests/runTests.exe), or, if changes to the code have been made, open the [src/tests](https://github.com/jleipus/Game-Of-Life/blob/master/src/tests) folder in your console, type "g++ tests.cpp catch.hpp ../gamefield.cpp ../ruleset.cpp -o runTests" and then run the executable.

###### Versions:

v0: Basic C++ console application with predetermined starting value. Speed is set to 10 ticks/s.

v1: Size and speed are specified through console arguments.

v2: Added graphical interface using Qt5. Size is fixed at 50x50, speed starts at 10 t/s but can be adjusted. Clicking on speed pauses game.

v3: Clicking on a cell changes its state. Added cycle counter.

v4: Size is now adjustable, field size and drawn view ar independent, many internal functionality changes, addded basic units test for public functions.

v5: Unit tests now use the catch2 framework, added multithreading for GUI functions.
