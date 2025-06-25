# Pathfinding Tool
A CLI tool using greedy algorithmic approach for creating a path-planning tool to assist with urban navigation.

All streets are assumed to be two-way streets. The city is represented as a weighted undirected graph. Each edge is associated with two integers: the driving and walking time. Each node has an indication of whether there is parking available there or not.

If you can drive through an edge, you can walk through it as well. Also, we consider that there are always free parking spots.

The [data](code/data/) folder contains the files used for creating the city representation graph.

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
```
git clone git@github.com:casemiromjm/DA-pathfinder.git
cd DA-pathfinder
mkdir build && cd build
```

If you have `ninja` installed, you can use it to build the project:
```
cmake ../code
ninja
./pathfinder
```

Otherwise, you can use `make`:
```
cmake -G "Unix Makefiles" ../code
make
./pathfinder
```

## Features
- Independent Route Planning

Find the fastest route *(Route A)*. Also, find the best alternative independent route *(Route B)*. There are no shared locations/roads between the two routes, and *Route B* must take the same time or longer than *Route A*.

- Restricted Route Planning

Find the fastest route considering restrictions such as:
    <ul style="list-style-type: circle;">
    <li>Exclude some nodes (locations)</li>
    <li>Exclude some edges (streets)</li>
    <li>Exclude some nodes and edges simultaneously</li>
    <li>Include a specific node</li>
    </ul>

- Environmentally-Friendly Route Planning

Finds the best path that allows the users to drive to a certain point, park the car and then walk to the destination.

- Approximate Environmentally-Friendly Route Planning

If no route is found, it relaxes the maximum walking time constraint, but it keeps in mind that the user should not walk for an unreasonable amount of time.

## Input / Output
### Input
For inputs, the user can use the CLI or a file called `input.txt` in the `code/input_output/` folder. The input format can be:

Independent Route Planning:
```
Mode:driving
Source:<id>
Destination:<id>
```

Restricted Route Planning:
```
Mode:driving
Source:<node_id>
Destination:<node_id>
AvoidNodes:<node_id>,<node_id>,...,<node_id>
AvoidSegments:<node_id>,<node_id>,...,<node_id>
Include:<node_id>
```
If a certain restriction is not used, it should be left blank.

Environmentally-Friendly Route Planning:
```
Mode:driving-walking
Source:<node_id>
Destination:<node_id>
MaxWalkingTime:<int>
AvoidNodes:<node_id>,<node_id>,...,<node_id>
AvoidSegments:<node_id>,<node_id>,...,<node_id>
```
If a certain restriction, namely the last two, is not used, it should be left blank.

Approximate Environmentally-Friendly Route Planning:

The same as the previous.

### Output

The outputs will occur in the same place as the input. In the file case, it will be the `output.txt`. The output format will be:

`<total_time>` is represented as an integer number of minutes.

Independent Route Planning:
```
Source:<node_id>
Destination:<node_id>
BestDrivingRoute:<node_id>,<node_id>,<node_id>,...,<node_id>(<total_time>)
AlternativeDrivingRoute:<node_id>,<node_id>,<node_id>,...,<node_id>(<total_time>)
```
If there is an impossible route (Best or Alternative), the output is `...DrivingRoute:none`

Restricted Route Planning:
```
Source:<node_id>
Destination:<node_id>
RestrictedDrivingRoute:<node_id>,<node_id>,<node_id>,...,<node_id>(<total_time>)
```

Environmentally-Friendly Route Planning:
When it finds a route, the output is:
```
Source:<node_id>
Destination:<node_id>
DrivingRoute:<node_id>,<node_id>,<node_id>,...,<node_id>(<total_time_driving>)
ParkingNode:<node_id>
WalkingRoute:<node_id>,<node_id>,<node_id>,...,<node_id>(<total_time_walking>)
TotalTime:<total_time>
```

In case of an impossible route, the output is:
```
Source:<node_id>
Destination:<node_id>
DrivingRoute:none
ParkingNode:none
WalkingRoute:none
TotalTime:
Message:<error>
```

Approximate Environmentally-Friendly Route Planning:

When the initial constraints are relaxed and a route is found, the file `alternative_routes.txt` is created and the output is:
```
Source:<node_id>
Destination:<node_id>
DrivingRoute1:<node_id>,<node_id>,<node_id>,...,<node_id>(<total_time_driving>)
ParkingNode1:<node_id>
WalkingRoute1:<node_id>,<node_id>,<node_id>,...,<node_id>(<total_time_walking>)
TotalTime1:<total_time>
DrivingRoute2:<node_id>,<node_id>,<node_id>,...,<node_id>(<total_time_driving>)
ParkingNode2:<node_id>
WalkingRoute2:<node_id>,<node_id>,<node_id>,...,<node_id>(<total_time_walking>)
TotalTime2:<total_time>
```
