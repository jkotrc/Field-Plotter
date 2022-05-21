
# Table of Contents

1.  [Field Plotter](#orgba9b308)
    1.  [About](#org1e7fd0f)
    2.  [Building](#org81dfac5)



<a id="orgba9b308"></a>

# Field Plotter


<a id="org1e7fd0f"></a>

## About

This project has a rocky road of development behind it, starting as a high school project with quickly
hacked together design and messy code. Since then it has developed into a passion project for learning
OpenGL programming and software design principles as a whole.

The program will be a simple graphing calculator with a floating ImGUI-powered interface. It will
have a 2D and 3D view and allow the user to add electrical charges to the scene to visualize
the force field either as field lines or as a vector field.

![Screenshot](https://i.imgur.com/ALwgeFy.png)

![Screenshot2](https://i.imgur.com/vSQkmAr.png)


<a id="org81dfac5"></a>

## Building

    meson build .; ninja -C build

Requires installing subprojects:

    meson wrap install glew
    meson wrap install gtest

