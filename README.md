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