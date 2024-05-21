#include <bits/stdc++.h>  
using namespace std;
 
 // Only the Node class would be sufficient, this is not optmal
class Sensor{
    public:
        int x;
        int y;
        int s;
        int idxGraph;

        Sensor(int xs = -1, int ys = -1, int rs = -1){
            x = xs;
            y = ys;
            s = rs;
            idxGraph = -1;
        }
};

 // Node class
class Node{
    public:
        int idx;
        int isWall;
        int isSensor;
        Sensor sensor;
        vector<int> neighbors;

        // DFS
        int parent;
        int visited;

        // Construtor
        Node(int i){
            idx = i;
            parent = -2;
            visited = 0;
            isWall = 0;
            sensor = 0;
        }
};

double distanceTwoPoints(double x1, double y1, double x2, double y2){
    double xd = x2 - x1;
    double yd = y2 - y1;
    return sqrt(xd*xd + yd*yd);
}

void DFS(vector<Node>& graph, Node v){
    graph[v.idx].visited = 1;
    for(unsigned int i = 0; i < graph[v.idx].neighbors.size(); i++){
        int idxNeighbor = graph[v.idx].neighbors[i];
        if (graph[idxNeighbor].visited == 0){
            graph[idxNeighbor].parent = graph[v.idx].idx;
            DFS(graph,graph[idxNeighbor]);
        }
    }
}

int main() {
    ifstream inputFile("SimpleArtwork.txt");
    cin.rdbuf(inputFile.rdbuf());
    //ofstream fileOut("output.txt"); 
    //cout.rdbuf(fileOut.rdbuf());

    // Variables
    int M, N, K; // (M,N) Room size (x+,y+), K number of sensors
    int X, Y, S; // Sensor location, Sensor range
    vector<Sensor> sensorsList;
    vector<Node> graph;

    // Walls on graph
    for(int i = 0; i < 4; i++){
        graph.push_back(Node(i));
        graph[i].isWall = 1;
    }

    // Getting variables
    cin >> M >> N >> K;
    //cout << M << " " << N << " " << K << endl;

    // Getting sensors and building graph
    for(int i = 0; i < K; i++){
        
        // Getting sensors info
        cin >> X >> Y >> S;

        // Creating sensor and putting on the graph
        Sensor newSensor(X,Y,S);
        Node newNode(i+4);
        newSensor.idxGraph = i+4;
        newNode.sensor = newSensor;
        newNode.isSensor = 1;
        graph.push_back(newNode); // This can be slow, Alloc memory for speed
        graph.push_back(newNode); // This can be slow, Alloc memory for speed
        sensorsList.push_back(newSensor); // This can be slow, Alloc memory for speed

        // If sensors are touching walls (nodes 0 1 2 3) add edge
        if(Y + newSensor.s >= N) {graph[newNode.idx].neighbors.push_back(0); graph[0].neighbors.push_back(newNode.idx);}
        if(X + newSensor.s >= M) {graph[newNode.idx].neighbors.push_back(1); graph[1].neighbors.push_back(newNode.idx);}
        if(Y - newSensor.s <= 0) {graph[newNode.idx].neighbors.push_back(2); graph[2].neighbors.push_back(newNode.idx);}
        if(X - newSensor.s <= 0) {graph[newNode.idx].neighbors.push_back(3); graph[3].neighbors.push_back(newNode.idx);}

        // See if touch other sensor
        // -1  to not add if is the same sensor
        for(unsigned int j = 0; j < sensorsList.size()-1;j++){
            double d = distanceTwoPoints(newSensor.x,newSensor.y,sensorsList[j].x, sensorsList[j].y);
            if(d <= newSensor.s + sensorsList[j].s){
                graph[newNode.idx].neighbors.push_back(sensorsList[j].idxGraph);
                graph[sensorsList[j].idxGraph].neighbors.push_back(newNode.idx);
            }
        }
        //cout << X << " " << Y << " " << S << endl; 
    }
    // Testing if path is blocked

    // If wall 0 finds 2 or 1
    graph[0].visited = -1;
    DFS(graph,0);
    int result = 1;

//cout << graph[1].parent << ", " << graph[2].parent << ", " << endl;

    for(unsigned int i = 0; i < graph.size(); i++){
        //cout << "Node " << i << " vizinhos:  ";
        for(unsigned int j = 0; j < graph[i].neighbors.size();j++){
            //cout << graph[i].neighbors[j] << ", ";
        }
        //cout << endl;
    }

    if(graph[1].parent != -2 || graph[2].parent != -2){
        result = 0;
        }
    else{
        // Clearing graph
        for(unsigned int i = 0; i < graph.size(); i++){
            graph[i].visited = 0;
            graph[i].parent = -2;
        }
        // If wall 3 finds 1 or 2
        DFS(graph,3);
        if(graph[1].parent != -2 || graph[2].parent != -2){result = 0;}
    }

    //cout << graph[1].parent << ", " << graph[2].parent << endl;

    if (result == 1){
        cout << "S" << endl;
    } else {
        cout << "N" << endl;
    }

    return 0;
}