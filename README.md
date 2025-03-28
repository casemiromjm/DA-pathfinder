# DA project 1
Project using greedy algorithmic approach creating a path-planning tool to assist with urban navigation.

All streets are assumed to be two-way streets. The city is represented as a weighted undirected graph. Each edge is associated with two integers: the driving and walking time. Each node indicates if there is a parking available there or not.

If you can drive through an edge, you can walk through it as well. There are always free parking spots.

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

Whenever you cannot drive on a certain street, there will be an `X` character. It has to be treated by the code.

After parsing the information, we need to create one (or more) appropriate data strutcture(s). It has to be based on the *`Graph.h`* file used in TP. Any changes to the file must be justified in the presentation.

## TODO
### Task 1 - Initial Functionalities
- [X] *T1.1* - **CLI menu (+ batch mode)** that exposes all functionalities. When displaying the results, show all relevant details, including the full sequence path
points from origin to destination. The program should handle exceptional cases/errors properly *(1 point)*
- [X] *T1.2* - **Read and parse Input Data** (accessible through menu). This functionality enable the user to request information such as the start and end points of your trip, the
alternative independent route, the locations and/or segments to exclude, and the environmentally-friendly
routing parameters. The **batch mode** must rely on input via `input.txt` and output via `output.txt` *(1 point)*
- [X] **Inputs/Outputs via CLI** same as the batch mode, but get inputs (and give outputs) via terminal.
- [ ] *T1.3* - Generate ***Doxygen* documentation**. It should also indicate the *time complexity* for each of the most relevant algorithms. *(2 points)*

### Task 2 - Route Planning Functionalities (driving only)
Assumptions:
- Origin and destination can be adjacent or not.
- Origin and destination can have parking spots or not.
- Consider only the driving time.

Tasks:

- [X] *T2.1* - **Independent Route Planning**. Find the fastest route *(Route A)*. Also, find the best alternative independent route *(Route B)*. *(3 points)*

    This means that *Route A* and *Route B* should **NOT** share intermediate nodes/edges and *Route B* **MUST TAKE** the same time or longer than *Route A*.

    - `input.txt`
    ```
    Mode:driving
    Source:<node_id>
    Destination:<node_id>
    ```

    - `output.txt`
    ```
    Source:<node_id>
    Destination:<node_id>
    BestDrivingRoute:<node_id>,<node_id>,<node_id>,...,<node_id>(<total_time>)
    AlternativeDrivingRoute:<node_id>,<node_id>,<node_id>,...,<node_id>(<total_time>)
    ```

    `<total_time>` is represented as an integer number of minutes

    If there is an impossible route (A or B), the output should be `...DrivingRoute:none`


- [X] *T2.2* - **Restricted Route Planning**. Find the fastest route considering restrictions. *(5 points)*

    Restrictions could be:
    - Exclude some nodes (locations)
    - Exclude some edges (streets)
    - Exclude some nodes and edges simultaneously
    - Include a specific node

    - `input.txt`
    ```
    Mode:driving
    Source:<node_id>
    Destination:<node_id>
    AvoidNodes:<node_id>,<node_id>,...,<node_id>
    AvoidSegments:<node_id>,<node_id>,...,<node_id>
    Include:<node_id>
    ```
    If a certain restriction is not used, it should be left blank, e.g. `AvoidNodes:`.

    - `output.txt`
    ```
    Source:<node_id>
    Destination:<node_id>
    RestrictedDrivingRoute:<node_id>,<node_id>,<node_id>,...,<node_id>(<total_time>)
    ```

    `<total_time>` is represented as an integer number of minutes

    If there is an impossible route, the output should be `RestrictedDrivingRoute:none`

### Task 3 - Environmentally-Friendly Route Planning Functionalities (driving and walking)

This allows the users to drive to a certain point, park the car and then walk to the destination.

Assumptions:
- Origin and destination cannot be adjacent.
- Origin and destination cannot have parking spots.
- All routes must mix walking and driving.
- `Max. Walking Time` is the maximum time the user is willing to walk.

Tasks:

- [ ] *T3.1* - **Best route for driving and walking**. *(4 points)*

    Must be aware of the parameters, `Max. Walking Time`, `AvoidNodes` and `AvoidSegments`.

    Find the best route for driving and walking respecting the user constraints. Must mix driving and walking. If there are multiple routes, should choose the one the longest walking time. If there still are multple routes, choose any.

    It is only allowed to have a single stop. Parking the car count as a stop.

    If there is no suitable route, indicate which constraint was not met, like:
    - walking time was exceeded
    - absence of parking

    etc.

    - `input.txt`
    ```
    Mode:driving-walking
    Source:<node_id>
    Destination:<node_id>
    MaxWalkingTime:<int>
    AvoidNodes:<node_id>,<node_id>,...,<node_id>
    AvoidSegments:<node_id>,<node_id>,...,<node_id>
    ```
    If a certain restriction, namely the last two, is not used, it should be left blank, e.g. `AvoidNodes:`.

    - `output.txt`
    ```
    Source:<node_id>
    Destination:<node_id>
    DrivingRoute:<node_id>,<node_id>,<node_id>,...,<node_id>(<total_time_driving>)
    ParkingNode:<node_id>
    WalkingRoute:<node_id>,<node_id>,<node_id>,...,<node_id>(<total_time_walking>)
    TotalTime:<total_time>
    ```

    `<total_time>` represents the total time in minutes. `<total_time_driving>` and `<total_time_walking>` represent the time spent driving and walking, respectively. Time is an integer number of minutes.

    `ParkingNode` is the node where the user should park the car.

    In case of an impossible route, the `output.txt` should be:
    ```
    Source:<node_id>
    Destination:<node_id>
    DrivingRoute:none
    ParkingNode:none
    WalkingRoute:none
    TotalTime:
    Message:<error>
    ```

    `<error>` should be a message indicating the reason why the route is impossible.

- [ ] *T3.2* - **Approximate solution**. *(2 points)*

    If there is no solution for the previous task, find an approximate solution. If the solution increases the maximum walking time, it should the new time.

    Must present 2 alternatives sorted by the total time. Always include a driving and a walking segment in the solution.

    - `input.txt`
    ```
    Mode:driving-walking
    Source:<node_id>
    Destination:<node_id>
    MaxWalkingTime:<int>
    AvoidNodes:<node_id>,<node_id>,...,<node_id>
    AvoidSegments:<node_id>,<node_id>,...,<node_id>
    ```
    If a certain restriction, namely the last two, is not used, it should be left blank, e.g. `AvoidNodes:`.

    - `output.txt`
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

    `<total_time>` represents the total time in minutes. `<total_time_driving>` and `<total_time_walking>` represent the time spent driving and walking, respectively. Time is an integer number of minutes.

### Task 4 - Presentation and Turn-In
- [ ] *T4.1* - **Presentation** *(2 points)*

    10-minute demo of the project. Must have a PDF presentation highlighting key aspects:
    - Solution for the provided input datasets
    - Highlight the graph class, explaining conceptual decision and alterations (if made)
    - Highlight the most important and challenging aspects of our implementation
    
    More instructions about the PDF are on Moodle.

    For turn-in, we have to provide a zip file name *DA2025_PROJ1_G37.zip*. It should contain:
    - `code` folder with the source code
    - `docs` folder with the Doxygen documentation
    - Presentation file in PDF format
