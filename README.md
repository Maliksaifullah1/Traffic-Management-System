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

## How to Run Code 
## 1. Compilation
![image](https://github.com/user-attachments/assets/dfbee02e-ccd2-4369-804a-0f29cabef62d)

## 2.Run
![image](https://github.com/user-attachments/assets/e88ee4f0-2654-4bcf-a93c-b0eddf3fa1d4)


## Sample Outputs
## Initail Dashboard
![image](https://github.com/user-attachments/assets/d50edb5a-556e-40ec-8956-77cad2468f80)
## Road Management
![image](https://github.com/user-attachments/assets/4b67ae95-3340-4f9b-a197-dc1a69ab2fe2)
## Vehicles management
![image](https://github.com/user-attachments/assets/58e6254e-7664-4643-9779-3f9c73d51261)
## Traffic Signal Management
![image](https://github.com/user-attachments/assets/db7a4cbb-6f35-4a15-8c5d-457b261769d8)
## Graph
![image](https://github.com/user-attachments/assets/da7901bd-7295-427f-8dee-6a300624283a)
## Vehicles
![image](https://github.com/user-attachments/assets/edc05a65-b74a-4a07-ad0f-c520daa3586f)
## Shortest Path
![image](https://github.com/user-attachments/assets/1771fd66-d39e-49dd-a542-ab65a91cf0c5)
## Movement 
![image](https://github.com/user-attachments/assets/d19aa469-6007-44a9-bb52-70e320a5ab19)
## Traffic signals 
![image](https://github.com/user-attachments/assets/ab644263-da29-4439-a154-80e530e08c2c)
## Logs
![image](https://github.com/user-attachments/assets/fcff018f-958f-44b6-9b6f-3524b18e6c7d)








