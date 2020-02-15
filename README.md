# LED-Controller
A program for controlling your custom LED-strips with your computer easily.

Pretty useful to test your LEDs, and to fool around of course.

## Prerequisites
* An [Arduino](https://www.arduino.cc)
* [CMake](https://cmake.org), a pretty neat build-tool
* The [GNU Compiler Collection](https://gcc.gnu.org)
* A computer, connected with the Arduino via USB
* Some basic knowledge of electronics

## Setup
* Clone the repository via `git clone https://github.com/DalexKraus/LED-Controller.git`\
  Alternatively, you can also download the [ZIP-version](https://github.com/DalexKraus/LED-Controller/archive/master.zip).

* Descend into the created directory and execute the command `cmake .`, which will then create a **Makefile** for you.

* After generating the Makefile, the last step is to run `make` to compile the source files into an executable binary.

* Finally, you can run the program using `./ledctrl`

## Notes
The program has been compiled and tested on
**x86_64 Debian GNU/Linux 10 (buster)** using **g++ 8.3.0**

**Support for Windows is currently not supported, but will be added in the near future!**
