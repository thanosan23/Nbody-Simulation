# Nbody Simulation

This is an nbody simulation written in C++ and Python.

The physics engine is written in C++, and the visualization code is written in Python.

## How to use
Edit `configuration.toml` with desired parameters for the simulation.
```
chmod u+wx ./run
./run <enter name of file to export nbody data>
```

## Requirements
* g++
* python3

## Templates
Examples of configuration templates you can use are found in `templates/`

## Notes
* When adding an object onto Earth's orbit, when setting the distance from Earth, add the altitude of the object and the Earth's radius together.
* When calculating for velocity use: `sqrt(G*m/r)`

## Nbody File Format
Nbody data is formatted into its own file format.

The first line is the amount of celestial bodies in the simulation.
The second line is the amount of timesteps in the simulation.
The third line is if labels are toggled on or off.
The next `n` lines, where `n` is the amount of celestial bodies, is the names of each of the bodies.
The next lines of data are the position values of the celestial bodies. 
