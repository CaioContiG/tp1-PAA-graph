#include <bits/stdc++.h>
using namespace std;

// Edge Class
class Edge{
    public:
        int idxNeighbor;
        int cost;
    // Constructor
    Edge(int index = -1, int c = 0){
        idxNeighbor = index;
        cost = c;
    }
};
 
 class Node{
    public:
        int idx;
        vector<Edge> neighbors = {};

        // Dijkstra
        int distance;
        int parent;
        int visited;

        // Construtor
        Node(int i = -1){
            idx = i;
        }

        // Operator Overload for PQ
        bool operator<(const Node& n) const{
            return this->distance > n.distance; // > NOT < because the lower the better
        }
 };

void getVar(int& N, int& M, int& K, float& p){
    cin >> N >> M >> K >> p;
}

int main() {
    ifstream inputFile("leningrad.txt");
    cin.rdbuf(inputFile.rdbuf());
    //ofstream fileOut("output.txt"); 
    //cout.rdbuf(fileOut.rdbuf());
    
    // Declaring Variables
    unsigned int N, M, K; // Number of: strategic points, strategic roads, bullets
    float prob; // probability
    int pi, pj; // point i and point j
    int A; // Number of enemy soldiers
    int ps; // Point location of enemy
    int sp, dp; // Start point and Destiny point

    vector<Node> graph; // Adjacency List Graph
    while(true){
        // Clearing graph
        graph.clear();

        // Get Initial Variables
        cin >> N >> M >> K >> prob;
        if (cin.eof()){break;} // If EOF break loop
    
        // Allocating space and resizing for speed
        if (N > graph.capacity()) {graph.reserve(N);}
        graph.resize(N);

        // Get points and add vertices/edges to the graph
        for(unsigned int i = 0; i < M; i++){
            cin >> pi >> pj;
            pi = pi - 1;
            pj = pj - 1;            

            graph[pi] = Node(pi);
            graph[pj] = Node(pj);
            graph[pi].neighbors.push_back(Edge(pj,0));
            graph[pj].neighbors.push_back(Edge(pi,0));
        }

        // Get number of soldiers
        cin >> A;

        // Get soldiers location and update cost of edges
        for(int i = 0; i < A; i++){
            cin >> ps;
            ps = ps - 1;

            // for all neighbors of ps, update edges to ps
            // Matrix nxn would make it easier and faster            
            for(unsigned int j = 0; j < graph[ps].neighbors.size(); j++){
                int idxNeighbor = graph[ps].neighbors[j].idxNeighbor;
                for(unsigned int k = 0; k < graph[idxNeighbor].neighbors.size(); k++){
                    //int idxNN = graph[idxNeighbor].neighbors[k].idxNeighbor;
                    if (graph[idxNeighbor].neighbors[k].idxNeighbor == ps){
                         graph[idxNeighbor].neighbors[k].cost += 1;
                    }
               }
                
            }
        }

        // Get start point and destiny point
        cin >> sp >> dp;
        sp = sp - 1;
        dp = dp - 1;

        cout << N << endl;
    }




    return 0;
}

// Sample
// Important: he need to land every shot
// First Line:
    // N - number of strategic points
    // M - number of strategic roads
    // K - bullets loaded
    // P - probability of killing sniper
// Next M lines
    // i and j: road linking i to j
// Second Last line
    // A - number of shooters
    // Next A integers - position of each shot
// Last line
    // s and d: starting point and destination of soldier   
/*
3 2 10 0.1
1 2
2 3
10 1 1 3 3 1 3 1 1 3 3
1 3
5 5 10 0.3
1 2
2 4
2 5
4 5
5 3
6 3 3 3 3 3 3
1 3
*/