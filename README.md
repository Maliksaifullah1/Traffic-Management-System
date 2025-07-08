# Traffic Management System
## Introduction
Traffic Management system is a software designed to control and view the analysis of city traffic. This includes managing road networks, vehicle movements, and signal timings. The system also checks for congested roads and provide alternate route to solve the problem. It also provides priority management for emergency vehicles. It also supports dynamic adjustments real time.
## Features
### Road Networks
Roads networks are implemented by using graphs. The vertices show the points and edges show the routes and weight show the length. It can be updated manually i.e vertices , edges can be added. Firstly, the the data is implemeted in graph from road_networks.csv. We have a feature of blocking and unblocking of roads based on an emergency or high protocol.
### Vehicle Managements
The vehicles are implemented by reading the vehicles.csv file. The data of vehicles includes its name, starting and ending point. Dijsktra Alogrithm is used to find the shortest distance. We can add new vehicles manually by giving their starting and ending indexes. All the vehicles move independently without relying on others.
### Traffic Signals
The TrafficSignalManagement class is responsible for managing traffic signal timings and providing features to load, adjust, display, and override traffic signal settings. It interacts with VehicleManagement and Graphlist to optimize traffic flow based on vehicle density and emergencies.
### Congestion Analysis
The congestion analysis is being done using hash tables. The program checks if the road has more than 5 cars and provides alternate routes for congested roads.
### Shortest Path
It finds the shortest path between the starting and ending point of vehicles using Dijsktra Alogrithm. It also looks for blocks and high congested roads and ignore those to reach the destination more fast and easily. It also provides alternative paths just like google maps depending upon congestion level and blockage. 
### Blocked Route Management
Block or unblock specific road connections dynamically.
### Emergency Vehiles Routing
Implements A* search algorithm to determine the shortest and fastest path for emergency vehicles.
Dynamically adjusts traffic signals along the path to prioritize emergency vehicle movement based on urgency levels (High, Medium, Low).
Fine-grained signal control for specific intersections during emergencies with predefined green light durations for each priority level.








