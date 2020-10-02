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
To build the project simply run
```sh
$ cmake . .
```
in the root directory of this repo.

### Usage
---
The prototype frontend currently displays a hard-coded electric field around two point charges that can be adjusted in the `main.cpp` source file within `fieldplotter`. It won't be like this for too long as these parameters will later be changeable by the user.
![Screenshot](https://i.imgur.com/ALwgeFy.png)
![Screenshot2](https://i.imgur.com/vSQkmAr.png)