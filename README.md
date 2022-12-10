# CS225 Final Project: The Chicago Taxi Trip Navigator
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

## Presentation
[Presentation Video](https://drive.google.com/file/d/1gnWoVbIn6YT2lCHMhpnKyHUe9TvL5xcV/view?usp=sharing)

## Data
We are using the data from the [Chicago Data Portal of Transportation](https://data.cityofchicago.org/Transportation/Taxi-Trips/wrvz-psew/data).  We will be focusing on the following columns
- Pickup Community Area
- Dropoff Community Area
- Trip Seconds
- Trip Miles
- Fare

## Deliverables
- All major files that contain our functions and classes are in the [/src](https://github.com/akuld2/cs225finalproject/src)
- The datasets are stored as csv files in [/datasets](https://github.com/akuld2/cs225finalproject/tree/main/datasets)
- The tests are in [/tests](https://github.com/akuld2/cs225finalproject/tree/main/tests)
- The Project Report, Development Logs, and other documents are in [/documents](https://github.com/akuld2/cs225finalproject/tree/main/documents)


## Development Setup
Make sure you are running the program in Docker.

### Executables
To run the Chicago Taxi Trip Navigator, run `./run.sh` in the root directory.  The terminal will give you instructions on what to input.  Here is what to expect...
1. Navigate Between Zones (Dijkstra's) 
   - Input: a `start zone` (integer), `end zone` (integer), and a `metric` (integer).  The zone has to be a zone that the is listed.  The metric a user chooses determines if they are looking for the shortest path (miles), quickest path (seconds), or cheapest path (money)
   - Output: a vector of zones that gives the directions a user needs to take on the path and a double that describes the total amount of the metric they chose. 
2. Navigate to Connected Zones (BFS)
   - Input: a `zone` (integer)
   - Output: a vector of zones a user can travel when starting at that zone
3. Find the Busiest Zone (Betweeness Centrality Algorithm)
   - Input: none
   - Output: a formatted string that tells the user which is the most center node for each metric
4. Quit 

### Tests
To run the test cases for the Chicago Taxi Trip Navigator, run `./tests.sh` in the root directory.  We are using several different sized datasets that are located in [/datasets](https://github.com/akuld2/cs225finalproject/tree/main/datasets).  Our test cases focus on small to medium sized graphs when creating the graph, using BFS, using DIjkstra's, and using the Betweeness Centrality Algorithm.  To see a visual of the test datasets, they are located in the datasets folder in the file called [TestDatasetVisuals.pdf](https://github.com/akuld2/cs225finalproject/blob/megan-ja-patch-1/datasets/TestDatasetsVisuals.pdf).

## Contributers
Nisha Prasad (nishap4)
Akul Datta (akuld2)
Megan Ja (meganja2)
Yesui Dovchinsuren (ydovc2)

