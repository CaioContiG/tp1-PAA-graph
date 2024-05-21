#include <bits/stdc++.h>  
using namespace std;
 
class Sensor{
    public:
        int x;
        int y;
        int s;

        Sensor(int xs = -1, int ys = -1, int rs = -1){
            x = xs;
            y = ys;
            s = rs;
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
            wall = 0;
            sensor = 0;
        }
};

int main() {
    ifstream inputFile("simpleArtwork.txt");
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
    cout << M << " " << N << " " << K << endl;
    // Getting sensors and building graph
    for(int i = 0; i < K; i++){
        
        // Getting sensors info
        cin >> X >> Y >> S;

        // Creating sensor and putting on the graph
        Sensor newSensor(X,Y,S);
        Node newNode(i+4);
        newNode.sensor = newSensor;
        newNode.isSensor = 1;
        graph.push_back(newNode); // This can be slow, Alloc memory for speed
        sensorsList.push_back(newSensor); // This can be slow, Alloc memory for speed

        // If sensors are touching walls (nodes 0 1 2 3)
        if(Y + newSensor.s >= N)
        if(X + newSensor.s >= M)
        if(Y - newSensor.s >= 0)
        if(Y - newSensor.s >= 0)

        for(unsigned int j = 0; j < sensorsList.size();j++){

        }

        cout << X << " " << Y << " " << S << endl; 
    }  

    return 0;
}