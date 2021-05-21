# Field Plotter
---

## Table of contents

* [About Project](#general-info)
* [Dependencies](#technologies)
* [Setup](#setup)

## About Project
---
Field Plotter is a learning tool for AP and IB Physics made as my computer science IA. It plots a customizable interactive 3D plot of the electric field around any user-specified static point charges. The project is divided into two sub-modules: a statically linked library, `libfieldplotter`, and a frontend that uses the library. `libfieldplotter` is platform independent, potentially useful outside the scope of the program and `frontend` will depend on whatever GUI library is used (e.g. Qt, GTK+,...). So far, `frontend` is nothing but a GLFW window for debugging purposes.
	
## Technologies
---
This project is created with:
* GLEW: 2.2.0
* GLFW: 3.3.2 (just the testing frontend)
* Qt5: TBA (Windows version)
* GTK+: TBA (Linux version)
* CUDA: TBA


## Setup
---
Currently the project is undergoing a very large refactoring as the code has decayed over time. The build system is being switched to meson.

### Gallery
---
![Screenshot](https://i.imgur.com/ALwgeFy.png)
![Screenshot2](https://i.imgur.com/vSQkmAr.png)
