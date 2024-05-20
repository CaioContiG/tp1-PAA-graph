#include <bits/stdc++.h>
using namespace std;

// Node class
class Node{
    public:
        int idx;
        double x;
        double y;

        // PRIM
        double distance;
        int parent;
        int visited;

        // Construtor
        Node(int i = -1){
            idx = i;
            distance = INT_MAX;
            parent = -2;
            visited = 0;
        }

        // Operator Overload for PQ
        bool operator<(const Node& n) const{
            return this->distance > n.distance; // > NOT < because the lower the better
        }
};

class Edge{
    public:
        int idxNeighbor;
        int cost;

    // Constructor
    Edge(int in, int c){
        idxNeighbor = in;
        cost = c;
    }
};

double distanceTwoPoints(double x1, double y1, double x2, double y2){
    double xd = x2 - x1;
    double yd = y2 - y1;
    return sqrt(xd*xd + yd*yd);
}


void primAlg(vector<Node>& graph, vector<vector<double>>& weights){
    priority_queue<Node> pq;
    // Initializing
    for(unsigned int i = 0; i < graph.size(); i++){
        //graph[i].distance = 99999999; // MAX_INT bugged sometimes
        //graph[i].parent = -2;
        //graph[i].visited = 0;
        pq.push(graph[i]);
    }
    //cout << "Prim:";
    while (!pq.empty()){
        Node n = pq.top();
        //cout << n.idx << ", ";
        //if(n.distance > 99999){break;}
        pq.pop();
        int idx = n.idx;
        graph[idx].visited = 1;

        // It is a fully connected graph (but ij = ji can be optmized?)
        for(unsigned int i = 0; i < weights[idx].size(); i++){
            if(graph[i].visited == 0 && graph[i].distance > weights[idx][i]){
                graph[i].distance = weights[idx][i];
                graph[i].parent = graph[idx].idx;
                pq.push(graph[i]);
            }
        }
    }
    //cout << endl;
}

double calcTotalDistance(vector<Node>& graph, vector<vector<double>>& weights){
    double result = 0;
    for(unsigned int i = 0; i < graph.size(); i++){
        if (graph[i].parent != -2){
            if(graph[i].parent == -2){
                cout << "Problem, parent -2" << endl;
            } else {
                int idxParent = graph[i].parent;
                //result += distanceTwoPoints(graph[i].x, graph[i].y, graph[idxParent].x,graph[idxParent].y);
                result += weights[i][idxParent];
            }
        }
    }
    // for some reason is divided by 100
    return result/100;
}

int main() {
    //ifstream inputFile("simpleFF.txt");
    //cin.rdbuf(inputFile.rdbuf());
    //ofstream fileOut("output.txt"); 
    //cout.rdbuf(fileOut.rdbuf());
    std::cout << std::fixed << std::setprecision(2); // Setting precision
    
    // Declaring Variables
    int C, N; // number of test cases and people
    double x, y; // position of people
    vector<Node> graph; // Adjacency List Graph
    vector<vector<double>> edgesWeight; // NxN Matrix to grab edgesWeight quickly

    // Grab C - not using
    cin >> C;
    //cout << C << endl;
    int cnt = 0;
    while (true)
    {
        cnt+=1;
        // Clearing Variables
        graph.clear();
        edgesWeight.clear();
        

        // Grab number of people
        cin >> N;

        // Initializing graphs - (THIS IS SLOW?)
        for(int i = 0; i < N; i++){
            graph.push_back({});
            edgesWeight.push_back({});
        }
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                edgesWeight[i].push_back(INT_MAX);
            }
        }

        // If EOF break loop (not using C variable)
        if(cin.fail()){if (cin.eof()){break;}}
        //if(cnt == 7){cout << N << endl;}

        // Grab people's position and add node to graph
        for(int i = 0; i < N; i++){
            cin >> x >> y;
            //if(cnt == 7) {cout << x << " " << y << endl;}
            graph[i].idx = i;
            graph[i].x = x;
            graph[i].y = y;
        }

        // Update weights 
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                double d = distanceTwoPoints(graph[i].x, graph[i].y, graph[j].x, graph[j].y);
                //cout << "Distancia: " << graph[i].x << "," << graph[i].y << "," << graph[j].x << "," << graph[j].y << ": " << d << endl;
                edgesWeight[i][j] = d;
                edgesWeight[j][i] = d;
            }
        }

        // for(int i = 0; i < edgesWeight.size(); i++){
        //     for(int j = 0; j < edgesWeight[i].size(); j++){
        //         cout << edgesWeight[i][j] << ", ";
        //     }
        //     cout << endl;
        // }
        primAlg(graph,edgesWeight);
        //if(cnt == 7) 
        cout << calcTotalDistance(graph,edgesWeight) << endl;
    }     

    return 0;
}
// Input description
// First line
    // C - number of test cases
// Second line
    // N - number of people/vertices
// Next lines
    // x and y - position of vertex
// 2
// 5
// 0 0
// 0 100
// 100 200
// 200 400
// 300 300