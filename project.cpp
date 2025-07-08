#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>
using namespace std;
class TrafficSignalManagement;


class Node
{
public:
    char id;
    int weight;
    bool blocked;
    Node *next;
    Node(char id, int weight, Node *next = nullptr)
    {
        this->id = id;
        this->weight = weight;
        this->next = next;
        blocked = false;
    }
};

class list
{
public:
    Node *head;
    list()
    {
        head = nullptr;
    }
    void insert(char id, int weight)
    {
        if (head == nullptr)
            head = new Node(id, weight);
        else
        {
            Node *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            Node *temp2 = new Node(id, weight);
            temp->next = temp2;
        }
    }
    void print()
    {
        Node *temp = head;
        while (temp)
        {
            cout << "(" << temp->id << ", " << temp->weight << ") ";
            temp = temp->next;
        }
    }
};
class QueueNode
{
public:
    char data;
    QueueNode *next;
    QueueNode(char data, QueueNode *next = nullptr)
    {
        this->data = data;
        this->next = next;
    }
};
class Queue
{
private:
    QueueNode *head;
    QueueNode *tail;

public:
    Queue()
    {
        head = nullptr;
        tail = nullptr;
    }

    void enqueue(char value)
    {
        QueueNode *temp = new QueueNode(value);
        if (!tail)
        {
            head = tail = temp;
        }
        else
        {
            tail->next = temp;
            tail = temp;
        }
    }

    char dequeue()
    {
        if (!head)
        {
            cout << "Queue Underflow\n";
            return '\0';
        }
        QueueNode *temp = head;
        char value = temp->data;
        head = head->next;
        if (!head)
        {
            tail = nullptr;
        }
        delete temp;
        return value;
    }

    bool isEmpty()
    {
        return head == nullptr;
    }
};
class GraphNode
{
public:
    char id;
    GraphNode *next;
    list linklist;
    GraphNode(char id, GraphNode *next = nullptr)
    {
        this->id = id;
        this->next = next;
    }
};

class Graphlist
{
public:
    GraphNode *head;
    Graphlist()
    {
        head = nullptr;
    }

    void insert(char id)
    {
        if (head == nullptr)
            head = new GraphNode(id);
        else
        {
            GraphNode *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            GraphNode *temp2 = new GraphNode(id);
            temp->next = temp2;
        }
    }

    GraphNode *findNode(char id)
    {
        GraphNode *temp = head;
        while (temp)
        {
            if (temp->id == id)
            {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    void edge(char from, char to, int weight)
    {
        GraphNode *fromn = findNode(from);
        GraphNode *ton = findNode(to);
        if (fromn && ton)
        {
            fromn->linklist.insert(to, weight);
        }
        else
        {
            cout << "Error: Nodes not found!\n";
        }
    }

    int heuristic(char current, char goal)
    {
        return abs(current - goal);
    }

    void blockEdge(char from, char to)
    {
        GraphNode *fromNode = findNode(from);
        if (fromNode)
        {
            Node *edge = fromNode->linklist.head;
            while (edge)
            {
                if (edge->id == to)
                {
                    edge->blocked = true;
                    cout << "Edge from " << from << " to " << to << " is now blocked.\n";
                    return;
                }
                edge = edge->next;
            }
        }
        cout << "Error: Edge not found!\n";
    }
    void unblockEdge(char from, char to)
    {
        GraphNode *fromNode = findNode(from);
        if (fromNode)
        {
            Node *edge = fromNode->linklist.head;
            while (edge)
            {
                if (edge->id == to)
                {
                    edge->blocked = false;
                    cout << "Edge from " << from << " to " << to << " is now unblocked.\n";
                    return;
                }
                edge = edge->next;
            }
        }
        cout << "Error: Edge not found!\n";
    }
    void displayBlockedEdges()
    {
        GraphNode *currentNode = head;
        bool anyBlocked = false;

        while (currentNode)
        {
            Node *edge = currentNode->linklist.head; // Assuming 'linklist' has a head pointer
            while (edge)
            {
                if (edge->blocked)
                {
                    cout << currentNode->id << " -> " << edge->id << endl;
                    anyBlocked = true;
                }
                edge = edge->next;
            }
            currentNode = currentNode->next;
        }

        if (!anyBlocked)
        {
            cout << "No blocked routes in the graph." << endl;
        }
    }

    void readfile()
    {
        ifstream file("road_network.csv");
        if (!file.is_open())
        {
            cout << "Error: Unable to open file!" << endl;
            return;
        }

        string line;

        getline(file, line);

        while (getline(file, line))
        {
            stringstream ss(line);
            string from, to;
            int weight;

            getline(ss, from, ',');
            getline(ss, to, ',');
            ss >> weight;
            char fromChar = from[0];
            char toChar = to[0];
            if (!findNode(fromChar))
                insert(fromChar);
            if (!findNode(toChar))
                insert(toChar);
            edge(fromChar, toChar, weight);
        }

        file.close();
    }
    void printGraph()
    {
        GraphNode *temp = head;
        while (temp)
        {
            cout << temp->id << ": ";
            temp->linklist.print();
            cout << endl;
            temp = temp->next;
        }
    }

    void showMenu()
    {
        int choice = 0;
        char node1, node2;
        int weight;

        do
        {
            cout << "\n1. Insert Node\n";
            cout << "2. Add Edge\n";
            cout << "3. Block Edge\n";
            cout << "4. UnBlock Edge\n";
            cout << "5. Print Graph\n";
            cout << "6. Load Graph from File\n";
            cout << "7. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                cout << "Enter node id to insert: ";
                cin >> node1;
                insert(node1);
                break;

            case 2:
                cout << "Enter the starting node id: ";
                cin >> node1;
                cout << "Enter the ending node id: ";
                cin >> node2;
                cout << "Enter the weight of the edge: ";
                cin >> weight;
                edge(node1, node2, weight);
                break;
            case 3:
                cout << "Enter the starting node id: ";
                cin >> node1;
                cout << "Enter the ending node id: ";
                cin >> node2;
                blockEdge(node1, node2);
                break;

            case 4:
                cout << "Enter the starting node id: ";
                cin >> node1;
                cout << "Enter the ending node id: ";
                cin >> node2;
                unblockEdge(node1, node2);
                break;
            case 5:
                printGraph();
                break;

            case 6:
                readfile();
                cout << "Graph loaded from file.\n";
                break;

            case 7:
                cout << "Exiting the program.\n";
                return;

            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 7);
    }
    string dijkstra(Graphlist &graph, char start, char end)
    {
        const int MAX_NODES = 26;
        int distances[MAX_NODES];
        bool visited[MAX_NODES];
        char predecessors[MAX_NODES];

        for (int i = 0; i < MAX_NODES; i++)
        {
            distances[i] = INT_MAX;
            visited[i] = false;
            predecessors[i] = '\0';
        }

        distances[start - 'A'] = 0;

        for (int count = 0; count < MAX_NODES - 1; count++)
        {

            int minDistance = INT_MAX;
            char currentNode = '\0';
            for (int i = 0; i < MAX_NODES; i++)
            {
                if (!visited[i] && distances[i] < minDistance)
                {
                    minDistance = distances[i];
                    currentNode = i + 'A';
                }
            }

            if (currentNode == '\0')
            {
                break;
            }

            visited[currentNode - 'A'] = true;

            GraphNode *node = graph.findNode(currentNode);
            if (node)
            {
                Node *neighbor = node->linklist.head;
                while (neighbor)
                {
                    int neighborIndex = neighbor->id - 'A';

                    if (neighbor->blocked)
                    {
                        neighbor = neighbor->next;
                        continue;
                    }

                    if (!visited[neighborIndex] && distances[currentNode - 'A'] != INT_MAX &&
                        distances[currentNode - 'A'] + neighbor->weight < distances[neighborIndex])
                    {
                        distances[neighborIndex] = distances[currentNode - 'A'] + neighbor->weight;
                        predecessors[neighborIndex] = currentNode;
                    }
                    neighbor = neighbor->next;
                }
            }
        }

        string path = "";
        char current = end;
        while (current != '\0')
        {
            path = current + path;
            if (current == start)
            {
                break;
            }
            path = " -> " + path;
            current = predecessors[current - 'A'];
        }

        if (path.empty() || current != start)
        {
            return "No path found!";
        }

        return path;
    }

    void BFS(char start, char end)
    {
        string routes = "";
        Queue queue;
        QueueNode *visitedQueue = nullptr;

        queue.enqueue(start);
        visitedQueue = new QueueNode(start);

        while (!queue.isEmpty())
        {
            char currentNode = queue.dequeue();

            GraphNode *node = findNode(currentNode);
            if (node)
            {
                Node *neighbor = node->linklist.head;
                while (neighbor)
                {
                    char neighborNode = neighbor->id;

                    if (neighborNode == end && currentNode == start)
                    {
                        neighbor = neighbor->next;
                        continue;
                    }

                    QueueNode *temp = visitedQueue;
                    bool visited = false;
                    while (temp)
                    {
                        if (temp->data == neighborNode)
                        {
                            visited = true;
                            break;
                        }
                        temp = temp->next;
                    }

                    if (!visited)
                    {

                        string newPath = string(1, currentNode) + " -> " + string(1, neighborNode);

                        if (neighborNode == end)
                        {
                            routes += newPath + "\n";
                        }
                        else
                        {
                            queue.enqueue(neighborNode);

                            visitedQueue = new QueueNode(neighborNode, visitedQueue);
                        }
                    }

                    neighbor = neighbor->next;
                }
            }
        }

        if (!routes.empty())
        {
            cout << "Alternative routes:\n"
                 << routes;
        }
        else
        {
            cout << "No alternative route found.\n";
        }
    }
};

class PriorityQueue
{
private:
    struct Node
    {
        char intersection;
        int priority;
    };

    Node *queue;
    int size;
    int capacity;

public:
    PriorityQueue(int capacity = 10)
    {
        this->capacity = capacity;
        size = 0;
        queue = new Node[capacity];
    }

    ~PriorityQueue()
    {
        delete[] queue;
    }

    void enqueue(char intersection, int priority)
    {
        if (size >= capacity)
        {
            capacity *= 2;
            Node *newQueue = new Node[capacity];
            for (int i = 0; i < size; ++i)
                newQueue[i] = queue[i];
            delete[] queue;
            queue = newQueue;
        }

        int i;
        for (i = size - 1; i >= 0 && queue[i].priority < priority; --i)
            queue[i + 1] = queue[i];
        queue[i + 1] = {intersection, priority};
        ++size;
    }

    char dequeue()
    {
        if (size == 0)
        {
            cout << "Priority queue is empty";
            return '\0';
        }
        char intersection = queue[0].intersection;

        for (int i = 1; i < size; ++i)
            queue[i - 1] = queue[i];

        --size;
        return intersection;
    }

    bool isEmpty()
    {
        return size == 0;
    }
};
class HashtableNode
{
public:
    string vehicleID;
    HashtableNode *next;

    HashtableNode(string id)
    {
        this->vehicleID = id;
    }
};

class HashTable
{
private:
    struct Chain
    {
        HashtableNode *head;
        Chain() : head(nullptr) {}
    };

    Chain *table;
    int size;

    int hashFunction(char start, char end)
    {
        return (start - 'A') * 26 + (end - 'A');
    }

public:
    HashTable(int tableSize = 676)
    {
        size = tableSize;
        table = new Chain[size];
    }

    ~HashTable()
    {
        for (int i = 0; i < size; i++)
        {
            HashtableNode *current = table[i].head;
            while (current)
            {
                HashtableNode *temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }

    void insert(char start, char end, string vehicleID)
    {
        int index = hashFunction(start, end);
        HashtableNode *newHashtableNode = new HashtableNode(vehicleID);
        newHashtableNode->next = table[index].head;
        table[index].head = newHashtableNode;
    }
    void search(char start, char end)
    {
        int index = hashFunction(start, end);
        HashtableNode *current = table[index].head;

        int count = 0;
        if (!current)
        {
            cout << "No vehicles found on road " << start << " -> " << end << ".\n";
            return;
        }

        cout << "Vehicles on road " << start << " -> " << end << ": ";
        while (current)
        {
            cout << current->vehicleID << " ";
            count++;
            current = current->next;
        }
        cout << "\nNumber of vehicles: " << count << endl;
    }

    int countVehicles(char start, char end)
    {
        int index = hashFunction(start, end);
        HashtableNode *current = table[index].head;
        int count = 0;
        while (current)
        {
            count++;
            current = current->next;
        }
        return count;
    }
    void deleteVehicle(char start, char end, string vehicleID)
    {
        int index = hashFunction(start, end);
        HashtableNode *current = table[index].head;
        HashtableNode *prev = nullptr;

        while (current)
        {
            if (current->vehicleID == vehicleID)
            {
                if (prev == nullptr) 
                {
                    table[index].head = current->next;
                }
                else
                {
                    prev->next = current->next;
                }
                delete current;
                cout << "Vehicle " << vehicleID << " deleted from road " << start << " -> " << end << ".\n";
                return;
            }
            prev = current;
            current = current->next;
        }
        
    }

    void countAllVehicles()
    {
        int totalCount = 0;

        for (int i = 0; i < size; i++)
        {
            HashtableNode *current = table[i].head;
            while (current)
            {
                totalCount++;
                current = current->next;
            }
        }

        cout << "Total vehicles " << totalCount << endl;
    }
};
class VehicleNode
{
public:
    string id;
    char start;
    char end;

    VehicleNode(string id, char start, char end)
    {
        this->id = id;
        this->start = start;
        this->end = end;
    }

    VehicleNode() {}
};

class VehicleManagement
{

public:
    VehicleNode *vehicles;
    int capacity;
    int count;
    HashTable hashTable;
    int max;

    void resizeArray()
    {
        int newCapacity = capacity + 5;
        VehicleNode *newVehicles = new VehicleNode[newCapacity];

        for (int i = 0; i < count; i++)
        {
            newVehicles[i] = vehicles[i];
        }

        delete[] vehicles;

        vehicles = newVehicles;
        capacity = newCapacity;

        cout << "Array resized. New capacity: " << capacity << endl;
    }

    VehicleManagement(int capacity)
    {
        this->capacity = capacity;
        this->count = 0;
        this->vehicles = new VehicleNode[capacity];
        max = 5;
    }

    ~VehicleManagement()
    {
        delete[] vehicles;
    }

    void addVehicle()
    {
        if (count >= capacity)
        {
            resizeArray();
        }

        string id;
        char start, end;
        cout << "Enter Vehicle ID: ";
        cin >> id;
        cout << "Enter Start Intersection: ";
        cin >> start;
        cout << "Enter End Intersection: ";
        cin >> end;

        vehicles[count++] = VehicleNode(id, start, end);
        hashTable.insert(start, end, id);
        cout << "Vehicle added successfully.\n";
    }

    void addVehicle(char start, char end, string id, string path)
    {
        if (count >= capacity)
        {
            resizeArray();
        }

        vehicles[count++] = VehicleNode(id, start, end);
        hashTable.insert(start, end, id);
        cout << "Vehicle added successfully.\n";
    }

    void loadVehicles()
    {
        ifstream file("vehicles.csv");
        if (!file.is_open())
        {
            cout << "Error: Could not open file " << endl;
            return;
        }

        string line;
        getline(file, line);
        while (getline(file, line))
        {
            if (count >= capacity)
            {
                resizeArray();
            }

            stringstream ss(line);
            string id;
            char start, end;

            getline(ss, id, ',');
            ss >> start;
            ss.ignore();
            ss >> end;

            vehicles[count++] = VehicleNode(id, start, end);
            hashTable.insert(start, end, id);
        }
        file.close();
        cout << "Vehicles loaded successfully from CSV file.\n";
    }

    void displayVehicles()
    {
        if (count == 0)
        {
            cout << "No vehicles to display.\n";
            return;
        }
        cout << "Vehicle List:\n";
        for (int i = 0; i < count; i++)
        {
            cout << "ID: " << vehicles[i].id
                 << ", Start: " << vehicles[i].start
                 << ", End: " << vehicles[i].end << endl;
        }
    }
    void deleteVehicle(string id)
    {
        if (count == 0)
        {
            cout << "No vehicles to delete.\n";
            return;
        }

        bool found = false;

        for (int i = 0; i < count; i++)
        {
            if (vehicles[i].id == id)
            {
                found = true;

                hashTable.deleteVehicle(vehicles[i].start, vehicles[i].end, vehicles[i].id);

                for (int j = i; j < count - 1; j++)
                {
                    vehicles[j] = vehicles[j + 1];
                }

                count--;

                cout << "Vehicle with ID " << id << " Reached its Destination .\n";
                break;
            }
        }

        if (!found)
        {
            cout << "Vehicle with ID " << id << " not found.\n";
        }
    }


    void analyzeCongestion(Graphlist &graph)
    {
        bool flag = false;
        for (char start = 'A'; start <= 'Z'; start++)
        {
            for (char end = 'A'; end <= 'Z'; end++)
            {
                int vehicleCount = hashTable.countVehicles(start, end);
                if (vehicleCount >= max)
                {
                    flag = true;
                    cout << "Road " << start << " -> " << end << " is congested with "
                         << vehicleCount << " vehicles.\n";
                    cout << "Suggesting alternative routes...\n";
                    graph.BFS(start, end);
                }
            }
        }
        if (!flag)
            cout << "No Congestion found\n";
    }

    void vehicleConsole(TrafficSignalManagement &tsm, Graphlist &graph)
    {
        int choice;

        do
        {
            cout << "\n--- Vehicle Management Menu ---\n";
            cout << "1. Add Vehicle\n";
            cout << "2. Load Vehicles from CSV\n";
            cout << "3. Display Vehicles\n";
            cout << "4. Find Shortest Paths\n";
            cout << "5. Count Vehicles Between Two Intersections\n";
            cout << "6. Count Total vehicles on the road\n";
            cout << "7. Analyze Congestion\n";
            cout << "8. Update Movement\n";
            cout << "9. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                addVehicle();
                break;
            case 2:
                loadVehicles();
                break;
            case 3:
                displayVehicles();
                break;
            case 4:
                findShortestPaths(graph);
                break;
            case 5:
                char start, end;
                cout << "Enter Starting Intersection:";
                cin >> start;
                cout << "Enter ending Intersection:";
                cin >> end;

                cout << "Number of vehicles : " << hashTable.countVehicles(start, end) << endl;
                break;
            case 6:
                hashTable.countAllVehicles();
                break;
            case 7:
                analyzeCongestion(graph);
                break;
            case 8:
                updatemovement(tsm, graph);
                break;
            case 9:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 9);
    }

    void findShortestPaths(Graphlist &graph)
    {
        for (int i = 0; i < count; i++)
        {
            cout << "Shortest Path for " << vehicles[i].id << " is:\n"
                 << endl;
            cout << graph.dijkstra(graph, vehicles[i].start, vehicles[i].end) << endl
                 << endl;
        }
    }

    void findCurrentMovement(Graphlist&graph)
    {
        for (int i = 0; i < count; i++)
        {
            string path=graph.dijkstra(graph, vehicles[i].start, vehicles[i].end);
            cout  << vehicles[i].id << " is currently moving from: ";
            if(path.length()>=5)
            {
                cout<<path[0]<<" to "<<path[5];
            }
            else{
                cout<<"NOT MOVING";
            }
            cout<<endl;

            
        }
    }
    
    void updatemovement(TrafficSignalManagement &tsm, Graphlist& graph);

    int getCount()
    {
        return count;
    }

    VehicleNode getVehicle(int index)
    {
        if (index >= 0 && index < count)
            return vehicles[index];
        else
        {
            cout << "Error: Vehicle index out of bounds!\n";
            return VehicleNode();
        }
    }
};

class TrafficSignalManagement
{
private:
    PriorityQueue queue;
    struct SignalTiming
    {
        char intersection;
        int greenTime;
    };
    SignalTiming *signalTimings;
    int timingCount;
    int signalCapacity;

public:
    bool signalAdjusted = false;
    TrafficSignalManagement(int signalCapacity = 10)
    {
        this->signalCapacity = signalCapacity;
        signalTimings = new SignalTiming[signalCapacity];
        timingCount = 0;
    }

    ~TrafficSignalManagement()
    {
        delete[] signalTimings;
    }

    int getTimingCount()
    {
        return timingCount;
    }

    SignalTiming getSignalTimings(int index) 
    {
        return signalTimings[index];
    }

    void setSignalTimings(int index, int greenTime)
    {
        signalTimings[index].greenTime = greenTime;
    }

void loadSignalTimings()
{
    ifstream file("traffic_signals.csv");
    if (!file.is_open())
    {
        cout << "Error: Could not open traffic_signals.csv file" << endl;
        return;
    }

    timingCount = 0;
    string line;
    getline(file, line); 

    while (getline(file, line))
    {
        stringstream ss(line);
        string intersection;
        int greenTime;

        if (!getline(ss, intersection, ',') || !(ss >> greenTime))
        {
            cout << "Warning: Skipping invalid line: " << line << endl;
            continue; 
        }

        if (timingCount >= signalCapacity)
        {
            signalCapacity *= 2;
            SignalTiming *newTimings = new SignalTiming[signalCapacity];
            for (int i = 0; i < timingCount; i++)
                newTimings[i] = signalTimings[i];
            delete[] signalTimings;
            signalTimings = newTimings;
        }

        signalTimings[timingCount].intersection = intersection[0];
        signalTimings[timingCount].greenTime = greenTime;
        timingCount++;
    }

    file.close();
    cout << "Traffic signal timings loaded successfully." << endl;
    signalAdjusted = false;
}

    void displaySignalTimings()
    {
        cout << "Traffic Signal Timings:" << endl;
        cout << "Intersection\tGreenTime(s)" << endl;
        for (int i = 0; i < timingCount; i++)
            cout << signalTimings[i].intersection << "\t\t" << signalTimings[i].greenTime << " seconds" << endl;
    }

    void adjustSignalTimings(VehicleManagement &vm)
    {
        if (signalAdjusted)
        {
            cout << "Signal timings already adjusted based on vehicle density." << endl;
            return;
        }
        for (int i = 0; i < vm.getCount(); i++)
        {
            char start = vm.getVehicle(i).start;
            for (int j = 0; j < timingCount; j++)
                if (signalTimings[j].intersection == start)
                  if(signalTimings[j].greenTime>10)
                    signalTimings[j].greenTime -= 10;
                  else
                    signalTimings[j].greenTime -= 1;
        }

        for (int i = 0; i < timingCount; i++)
            if (signalTimings[i].greenTime > 60)
                signalTimings[i].greenTime = 60;

        cout << "Signal timings adjusted based on vehicle density." << endl;
        signalAdjusted = true;
        displaySignalTimings();
    }

void emergencyOverride(VehicleManagement &vm, Graphlist &graph)
{
    char startIntersection, endIntersection;
    string priority;

    cout << "Enter start intersection for the emergency vehicle: ";
    cin >> startIntersection;
    cout << "Enter end intersection for the emergency vehicle: ";
    cin >> endIntersection;
    cout << "Enter priority (High/Medium/Low): ";
    cin >> priority;

    cout << "Emergency vehicle is being re-routed." << endl;

    int MAX_NODES = 26;
    int gScore[MAX_NODES];
    int fScore[MAX_NODES];
    bool visited[MAX_NODES];
    char predecessors[MAX_NODES];

    for (int i = 0; i < MAX_NODES; i++)
    {
        gScore[i] = INT_MAX;
        fScore[i] = INT_MAX;
        visited[i] = false;
        predecessors[i] = '\0';
    }

    gScore[startIntersection - 'A'] = 0;
    fScore[startIntersection - 'A'] = graph.heuristic(startIntersection, endIntersection);

    PriorityQueue openSet(MAX_NODES); 
    openSet.enqueue(startIntersection, fScore[startIntersection - 'A']);

    while (!openSet.isEmpty())
    {
        char currentNode = openSet.dequeue();

        if (currentNode == endIntersection)
        {
            string path = "";
            char current = endIntersection;
            while (current != '\0')
            {
                path = current + path;
                if (current == startIntersection)
                {
                    break;
                }
                path = " -> " + path;
                current = predecessors[current - 'A'];
            }

            cout << "Emergency Vehicle Path: " << path << endl;
            string emergencyID = "EV1"; 
            vm.addVehicle(startIntersection, endIntersection, emergencyID, path);
            

    cout << "Adjusting traffic signals for priority: " << priority << endl;
    for (char intersection : path)
    {
        for (int i = 0; i < timingCount; i++)
        {
            if (signalTimings[i].intersection == intersection)
            {
                if (priority == "High" || priority == "high")
                    signalTimings[i].greenTime = 5;
                else if (priority == "Medium" || priority == "medium")
                    signalTimings[i].greenTime = 10;
                else if (priority == "Low" || priority == "low")
                    signalTimings[i].greenTime = 18;
            }
        }
    }
    displaySignalTimings();
            return;
        }

        visited[currentNode - 'A'] = true;

        GraphNode *node = graph.findNode(currentNode);
        if (node)
        {
            Node *neighbor = node->linklist.head;
            while (neighbor)
            {
                char neighborNode = neighbor->id;
                if (visited[neighborNode - 'A'])
                {
                    neighbor = neighbor->next;
                    continue;
                }

                int tentativeGScore = gScore[currentNode - 'A'] + neighbor->weight;
                if (tentativeGScore < gScore[neighborNode - 'A'])
                {
                    predecessors[neighborNode - 'A'] = currentNode;
                    gScore[neighborNode - 'A'] = tentativeGScore;
                    fScore[neighborNode - 'A'] = gScore[neighborNode - 'A'] + graph.heuristic(neighborNode, endIntersection);

                    openSet.enqueue(neighborNode, fScore[neighborNode - 'A']);
                }

                neighbor = neighbor->next;
            }
        }
    }
    cout << "Emergency vehicle route not found!" << endl;
    cout << "Restoring normal traffic flow." << endl;
}

    void trafficSignalMenu(VehicleManagement &vm, Graphlist &graph)
    {
        int choice;
        do
        {
            cout << "\n--- Traffic Signal Management Menu ---" << endl;
            cout << "1. Load Signal Timings" << endl;
            cout << "2. Adjust Signal Timings" << endl;
            cout << "3. Emergency Override" << endl;
            cout << "4. Display Signal Timings" << endl;
            cout << "5. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                loadSignalTimings();
                break;
            case 2:
                adjustSignalTimings(vm);
                break;
            case 3:
                emergencyOverride(vm, graph);
                break;
            case 4:
                displaySignalTimings();
                break;
            case 5:
                cout << "Exiting Traffic Signal Management." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 5);
    }
};

void VehicleManagement::updatemovement(TrafficSignalManagement &tsm, Graphlist &graph)
{
    for (int i = 0; i < count; i++)
    {
        string path = graph.dijkstra(graph, vehicles[i].start, vehicles[i].end);

        if (path.length() >= 5 && path != "No path found!")
        {
            char start = path[0];
            char end = path[5];

            if (vehicles[i].id == "EV1") 
            {
                for (int j = 0; j < tsm.getTimingCount(); j++)
                {
                    if (tsm.getSignalTimings(j).intersection == vehicles[i].start)
                    {
                        tsm.setSignalTimings(j, 30); 
                        cout << "Restored signal timing at intersection "<< vehicles[i].start << " to 30 seconds." << endl;
                    }
                }
            }

            vehicles[i].start = end; 
            cout << vehicles[i].id << " moved to " << end << endl;

            if (vehicles[i].start == vehicles[i].end) 
            {
                deleteVehicle(vehicles[i].id);
                i--;
            }
        }
    }
}

int main()
{
    Graphlist graph;
    TrafficSignalManagement tsm;
    VehicleManagement vm(5);
   
    int choice;
    do
    {
        cout << "\n--- Traffic Management Menu ---" << endl;
        cout << "1. Manage Traffic" << endl;
        cout << "2. Vehicles Menu" << endl;
        cout << "3. Traffic Signal Management" << endl;
        cout << "4. Update Traffic Logs" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Graph Representation:" << endl;
            graph.showMenu();
            break;
        case 2:
            vm.vehicleConsole(tsm, graph);
            break;
        case 3:
            tsm.trafficSignalMenu(vm, graph);
            break;

        case 4:
            cout << "\n--- Logs ---" << endl;
            cout << "\n --Vehicle Counts--" << endl;
            vm.hashTable.countAllVehicles();
            cout << "\n --Congestions--" << endl;
            vm.analyzeCongestion(graph);
            cout << "\n --Signal Timings--" << endl;
            tsm.displaySignalTimings();
            cout << "\n --Closed Routes--" << endl;
            graph.displayBlockedEdges();
            cout << "\n --Vehicle Movements--" << endl;
            vm.findCurrentMovement(graph);
            cout << endl
            << endl;

            break;
        case 5:
            cout << "Exiting Traffic Management System." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
