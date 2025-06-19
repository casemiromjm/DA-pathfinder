# Pathfinding Tool
A CLI tool using greedy algorithmic approach for creating a path-planning tool to assist with urban navigation.

All streets are assumed to be two-way streets. The city is represented as a weighted undirected graph. Each edge is associated with two integers: the driving and walking time. Each node has an indication of whether there is parking available there or not.

If you can drive through an edge, you can walk through it as well. Also, we consider that there are always free parking spots.

The [data/](code/data/) folder contains the files used for creating the city representation graph.

[Locations.csv](code/data/Locations.csv) contains a header with 3 columns: *Location*, *Id*, *Code*, *Parking*.
- *Location* is the name of the location
- *Id* is the unique identifier of the location
- *Code* is the code that be a key in another table
- *Parking* is a boolean (C like bool) value indicating if there is parking available at the location.
    - `0` means no parking
    - `1` means parking is available 

[Distances.csv](code/data/Distances.csv) contains information about the travelling time (or distance) between two locations. The file contains a header with 4 columns: *Location1*, *Location2*, *Driving*, *Walking*.
- *Location1* and *Location2* are the *Code* of the locations. Goes from 1 to 2.
- *Driving* is the time, in minutes, it takes to drive from *Location1* to *Location2*.
- *Walking* is the time, in minutes, it takes to walk from *Location1* to *Location2*.

Whenever you cannot drive on a certain street, there will be an `X` character.

After parsing the information, we create one (or more) graph based on the  *`Graph.h`* file used in DA TP classes.

## How to run
TODO

## Features
- Independent Route Planning
- Restricted Route Planning
- Environmentally-Friendly Route Planning
- Approximate Solution

## Notes
The last feature: *"Find an approximate solution"* relies on relaxing the maximum walking time constraint, but it keeps in mind that the user should not walk for an unreasonable amount of time.
