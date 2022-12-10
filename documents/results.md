<h3><u>Algorithm Overview</u></h3>

**Breadth-First Search**

Our implementation of the breadth-first search algorithm takes in a zone name, which must be a valid zone in the graph. The output is a vector of zones that are connected to that zone. Since we do not know how our graph looks visually, this will let us know what zones are feasible to travel to by Taxi. Our implementation has a time complexity of O(n).

To test the breadth-first search algorithm, we wrote a small and medium dataset and computed the answer manually to see if our algorithm was truly giving a list of connected zones.

**Dijkstra's**

Our implementation of Dijkstra’s algorithm takes in two zone nodes in our graph and a metric for what value we are using to calculate the shortest path (time, cost, or distance). By doing so, we ensured that our Dijkstra's algorithm has a way of successfully computing comparisons of the different types of metrics. The method returns the “best” path between the start and end nodes. The “best” path means identifying the cheapest path, the quickest path, or the shortest path. Our implementation has a time complexity of O(nlogn) or O(Elog(V)), where V represents the number of vertices and E represents the number of edges. Overall, Dijkstra's algorithm was the main component behind the GPS functionality of our algorithm.

To test Dijkstra’s Algorithm, we wrote small basic, small complex, medium basic, and medium complex test cases for our dataset. (The difference between basic and complex is the number of directed edges, as the complex test case would mean node A directs to node B and node B directs to node A). For each, we required that the result of running the algorithm on the graph was the same as the expected result, which we calculated and confirmed by hand.

**Betweenness Centrality**

Our implementation of the Betweenness Centrality algorithm takes in a metric, which could be fare, time, or distance, and outputs the node that has the most intersections between the nodes or the node with the highest central point in a graph. We were able to do this by estimating the betweenness centrality score, where we sum each individual result by dividing the number of shortest paths between the start node and the end node that pass-through node u with the number of shortest paths between the start and end nodes. Thus, the algorithm allows us to find the busiest or central hub node of the cheapest path, quickest path, or shortest path. The algorithm runs at a time complexity of O(VE + V^2 log V), where V represents the number of vertices and E represents the number of edges.

We confirmed that the algorithm is working as intended by adding test cases using small datasets we manually wrote and verified.

![](https://lh5.googleusercontent.com/4JUMZBY6tOJVigwr8aSGMqOYS2X9UYmfAQNed6qw-FNI3m9P2Y_2lBpU6MkyPNrPeSueg1KbmfOSb_x3OVrj8QAkyHbXUR1qoivaQoUhVX6tH8p16wgpNL_y23ANZXCtLVJ7AoE7_zeQFt2HCwZZQqEPjUD7JHvoaAbNP27lQTcdocVTeLl_iS5Ner-R)

<h3><u>Leading Questions</u></h3>

By implementing the algorithms we defined above, we were able to accomplish our leading questions…

-   Given a starting zone, which other zones can you travel to?
    
-   How to navigate from zone A to zone B with the least amount of money?
    
-   How to navigate from zone A to zone B in the least amount of time?
    
-   How to navigate from zone A to zone B with the least amount of miles?
    
-   Which zone is a central point in Chicago?
    

For instance, BFS can be used to obtain a list of locations connected to the one a traveler is in. Meanwhile, Dijkstra’s algorithm acts as a GPS that provides travelers with the shortest route from one node (a potential current location of the traveler) to another with the least amount of money, time, or miles. By using our Betweenness Centrality algorithm, travelers can find the central locations of the cheapest, quickest, or shortest path in Chicago, thus finding the zones which act as center points in Chicago. Overall, it was very interesting to apply all these algorithms and see how their features can create a meaningful taxi trip navigator for tourists in Chicago.

<h3><u>Personal Thoughts</u></h3>

**Akul**

I mainly worked on Dijkstra’s algorithm and Dijkstra tests. I learned how to implement Dijkstra’s algorithm with custom data types in a larger project. With Dijkstra’s algorithm, I had to create a new graph that labels each node with the distance from the start node, and modify the Node class to store the previous node in the shortest path to save the path from the start to the end node. From this project, I had a greater understanding of the algorithm and can apply it in real-world scenarios.

With more time, I would like to add more algorithms like Dijkstra’s for calculating the shortest path (such as Prim’s or Kruskal’s algorithm) to test if they are faster in our specific use case.

**Megan**

Since I mainly worked with BFS and the data parsing, I learned a couple of things regarding that it is much faster to use pointers to access the data then no pointers. This sped up the ingestion and accessing the data. I also finally understood what BFS truly does. I knew it was a traversal method, but it makes sense that it finds what nodes are connected to a certain node.

If we had more time, instead of using zones, I would suggest to use the latitude and longitudes to get a more accurate representation of where a person was truly traveling to and from. Doing this, we would be able to have more nodes and more edges, so essentially a larger graph. I think it would also be more interactive with the user; however, the drawback may be that since the graph is larger, and our algorithm’s runtimes are at the minimum of O(N), computing each algorithm would be very timely.

**Nisha**

I mainly worked on the data parsing, graph building, and BFS algorithms, along with the main interaction function. I learned a fair amount about how to ingest and process data, especially data cleaning. There were some odd entries in our database so we had to filter through them to get a clean, sensible graph. I liked programming the interactive interface the most, and managing project memory the least. Given extra time, I would’ve liked to have a nicer interface than the one written in the terminal. I think it would’ve been nice to develop a simple graphical interface, albeit quite difficult.

**Yesui**

Throughout the project, I mainly worked on implementing the Betweenness Centrality Algorithm and helped create different types of datasets. As the algorithm was very new to me, I learned quite a bit. By applying and coding what I learned from research, I now have a better understanding of the betweenness centrality functionality and also Dijkstra’s as it was a crucial component of a successful betweenness algorithm. I enjoyed implementing it. If I had extra time, I would’ve liked to work on the efficiency of the algorithm as it runs extremely slow. So it would, at least, reduce the total amount of time (9 hours) to run the algorithm.
