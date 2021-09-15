# Field Plotter
---

## About Project
---

Field Plotter is a passion C++ project, its main focus being providing 2D and 3D views of a static system of N-charges, displaying the vectors, field lines and equipotential surfaces to the electric field. It originally started as a school assignment, but the project decayed due to deadlines.

It is mostly an exercise in managing a scaling codebase, but it would be nice if the project evolved past its original goal and found use as an inspiration for software design and gallons of material for code ~~review~~ criticism.

## Building
---
To build, simply set up with meson

``` sh
meson build .
```
then compile with ninja
``` sh
ninja -C build
```
The output directory contains two executables, one being a debug build of the program and the other a testing executable which runs all the tests; the latter can be invoked with
``` sh
meson test -C build
```

## Status
---
This project had to meet deadlines so it ended up suffering from heavy code smells. It is currently being overhauled in favor of switching to the meson build system and establishing a solid foundation to application-level processes (input and window events) as well as a better abstraction of the rendering API. Below is a gallery of what it ended up looking like at some point.

### Gallery
---

This is what the old project produced in the experimental build thereof:

![Screenshot](https://i.imgur.com/ALwgeFy.png)
![Screenshot2](https://i.imgur.com/vSQkmAr.png)
