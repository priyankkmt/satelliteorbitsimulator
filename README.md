# Satellite orbit simulator

## Overview
This project is a satellite orbit simulation implemented in C++ using OpenGL. The simulation models a planet with a satellite in orbit around it. The satellite's position and velocity are calculated based on user-defined parameters, and the simulation provides a visual representation of the path of the satellite.

## Introduction
The satellite orbit simulation project aims to provide a simple and visually appealing representation of a satellite in orbit around a planet. The simulation is implemented using C++ and OpenGL, making it platform-independent.

## Dependencies
The project has the following dependencies:

- OpenGL: The simulation utilizes OpenGL for rendering the 3D graphics.
- C++ Standard Library: Standard C++ libraries are used for general functionalities.
- Visual Studio: The project is developed and tested using the Visual Studio IDE.
- QT Framework: The simulation relies on the QT framework for handling user interface elements.
- Sphere Class: The project uses a Sphere class for representing the planet and satellite.
- Geometry DLL: A dynamic link library (DLL) containing Point3D and Sphere classes that handles sphere rendering in the simulation.

## Input
Velocity ( Km/s ) 

Altitude ( 100 Km ) ( if 10 is input then it will be multiplied by 100 and it will become 1000 Km )

Size     ( m )   

## Output
Visual animation of satellites path
