# Project Proposal
## Leading Question 

To the taxi tourists of Chicago,

We know that navigating can be daunting.  There are so many options to consider and places to visit.  We wanted to create a high-level informative service that would help a taxi user navigate Chicago.  Some leading questions we want to answer include…
- How to navigate from zone A to zone B with the least amount of money?
- How to navigate from zone A to zone B with the least amount of time?
- How to navigate from zone A to zone B with the least amount of miles?
- Given a starting zone, which other zones can you travel to?
- Which zones are visited the most?

This is a general search tool for a taxi tourist to filter the way they want to travel via taxi in Chicago.

To answer the questions above, we will be using the data from the Chicago Data Portal Transportation, which contains information on a taxi, travel time, travel distance, to and from location, the fare, and the taxi company.  We will use this dataset to find the cheapest way to travel between zones and the cheapest way to visit every zone, which will help a user identify ways to travel around Chicago with the least amount of money.

When answering the questions above we will use the following algorithms: 
- BFS.  We plan to use the BFS traversal for finding out which other zones you can travel to given a starting zone.  Essentially will help identify connected zones.
- Dijkstra's Algorithm.  We plan to use Dijkstra’s Algorithm to find the cheapest path, the quickest path, or the path with the least amount of miles between two different zones.
- Betweeness Centrality Alogrithm. We plan to use the Betweenness Centrality Algorithm to find which zones are center points within Chicago.


## Dataset Acquisition and Processing
Our dataset is from the [Chicago Data Portal Transportation](https://data.cityofchicago.org/Transportation/Taxi-Trips/wrvz-psew/data).

### Data Format
Our dataset is from the Chicago Data Portal Transportation section (https://data.cityofchicago.org/Transportation/Taxi-Trips/wrvz-psew/data). The input is a CSV file and the dataset has 32,193 entries. The data input appears as the first couple lines being information about the dataset, and the rest of the file consists of lines with the respective data that corresponds to the header line, separated by commas. The only columns we are interested in are pickup zones, drop-off zones, fare, time, and miles.  Since there is a pickup and dropoff zone, this graph will be a directed graph. As for collecting fares, miles driven, and travel time between zones, if there are varying amounts, we will average them to weigh the edges. 

### Data Correction
Since we know the first several lines are text information regarding the data, we will ignore that section, but keep track of which columns contain the data we are looking for. For every line after, which is the corresponding information about how two nodes are connected, we will look for our respective data in the columns we noted down. If a data point consists of any non-numeric characters or if one of the necessary entries is missing, we will ignore that entire line.  We will also ignore entries that have the same start and end zone so there are no self-loops.  For each line, we will check first if they satisfy what we defined above, we will then create and insert the nodes into the graph or we will average the fare, time, and miles if the edge already exists.

### Data Storage

We will be creating an overarching Graph class, which will store a different class Node in a C++ standard vector.  Each Node will store a C++ standard map of other Nodes, in which the keys will be their neighboring nodes, and the values will be an instance of another class Edge. Edges will store 3 double values: fare, time, and miles.  The expected space complexity is O(V) for the vector, and O(E) for the maps,  resulting in an O(V+E) size.

Here is a visual of our [data structures, variables, and algorithms](https://lucid.app/lucidchart/0ca84bf6-6378-4cd5-96d3-1a3280ba7a60/edit?view_items=k0r5oRvgkwqO&invitationId=inv_a7727084-f564-4628-b019-52f3d605a3df) 

## Graph Algorithms 

### Function Inputs:
We are given a CSV file with a list of edges and nodes as input. We would have to iterate through the file and create nodes using the pickup and dropoff zones and edges using the fares and time to build into a graph before using any algorithms on the dataset. We would then take an input of two nodes for the start and end nodes to calculate the shortest path between the two given nodes using Dijkstra’s algorithm and BFS. For the Betweenness Centrality Algorithm, we will use the graph we built as the input and then run Dijkstra’s Algorithm for every zone combination.

### Function Outputs
Our output would be a vector of nodes from our first point to our second point that stores the path of nodes that takes the shortest amount of time and that results in the cheapest fare between the two given nodes. We would also store the time and fares in other variables. We would visualize the nodes by creating a function to print out the nodes in the vector in order, with the time it took for the whole path to be printed following the nodes. The Betweenness Centrality Algorithm would output a vector with the most visited zones (one if there is a definite victor, and more if there are ties).  

### Function Efficiency
If we have V vertices and E edges, the time complexity of Dijkstra’s algorithm is O(E log V) ~ O(n log n), the time complexity of BFS in a graph is O(n), and the time complexity of the Betweenness algorithm is O(V*E) ~ O(n^2). We would want to target an algorithm that is at most O(n^3) to maintain Dijkstra’s time complexity while also traversing the tree with BFS. The space complexity of Dijkstra’s algorithm is O(V^2) ~ O(n^2), the space complexity of BFS is O(|V|) ~ O(n), and the space complexity for the Betweenness algorithm is O(V+E) ~ O(n). We would also want to target an algorithm with space complexity O(n^2) to maintain Dijkstra’s space complexity. 

## Timeline

#### Week 1 (11/4): 
- Create a development log 
- Database Schema
- Class implementation
- Create the Read.Me
- Create the makefile 
- Create a small dataset to test against (at most 20 nodes)
- Configure user input

#### Week 2 (11/5 - 11/11): 
- Create a development log
- Ingest the data + parse file
- Build graph
- Begin implementing BFS
- Begin implementing Dijkstra’s Algorithm

#### Week 3 (11/12 - 11/18) - Mid-Project Check In:  
- Create a development log
- Write test cases for building the graph
- Finish implementing Dijkstra’s Algorithm
- Write test cases for Dijkstra’s Algorithm
- Finish implementing BFS
- Write test cases for BFS
- Begin implementing Betweenness Centrality Algorithm

### Thanksgiving Break (11/19 - 11/25)

#### Week 4 (11/26 - 12/2): 
- Finish implementing Betweenness Centrality Algorithm
- Write test cases for Betweenness Centrality Algorithm
- Code and documentation clean up
- Write written report
- Clean up the Schema,
- Update README

#### Week 5 (12/3 - 12/8): 
- Complete Final Presentation/video
