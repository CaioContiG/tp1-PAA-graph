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
        //int n_soldier;
        vector<Edge> neighbors;
        int n_soldier;

        // Dijkstra
        int distance;
        int parent;
        int visited;

        // Construtor
        Node(int i = -1){
            idx = i;
            n_soldier = 0;
        }

        // Operator Overload for PQ
        bool operator<(const Node& n) const{
            return this->distance > n.distance; // > NOT < because the lower the better
        }
 };

// Dijkstra algorithm
// If it stops when node end is closed, can be much faster
void Dijkstra(vector<Node>& graph, int sIdx){
    priority_queue<Node> pq;

    // Initializing
    for(unsigned int i = 0; i < graph.size(); i++){
        graph[i].distance = 99999999; // MAX_INT bugged sometimes
        graph[i].parent = -2;
        graph[i].visited = 0;
        pq.push(graph[i]);
    }
    
    int idx = sIdx;
    graph[idx].distance = 0;
    graph[idx].parent = -1;
    pq.push(graph[idx]);

    while (!pq.empty()){
        Node n = pq.top();
        if(n.distance > 99999){break;}
        idx = n.idx;
        graph[idx].visited = 1;
        pq.pop();
        for(unsigned int j = 0; j < graph[idx].neighbors.size(); j++){
            int neighbor_idx = graph[idx].neighbors[j].idxNeighbor;
            int c = graph[idx].distance + graph[idx].neighbors[j].cost;
            if (graph[neighbor_idx].visited == 0 && c < graph[neighbor_idx].distance){
                graph[neighbor_idx].distance = c;
                graph[neighbor_idx].parent = idx;
                pq.push(graph[neighbor_idx]);
            }
        }
    }
}

int main() {
    //ifstream inputFile("leningrad.txt");
    //cin.rdbuf(inputFile.rdbuf());
    //ofstream fileOut("output.txt"); 
    //cout.rdbuf(fileOut.rdbuf());
    std::cout << std::fixed << std::setprecision(3); // Setting precision

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

        // Getting N
        cin >> N;

        // If EOF break loop
        if(cin.fail()){
           if (cin.eof()){break;}
        }

        // Get Initial Variables
        cin >> M >> K >> prob;
    
        // Allocating space and resizing for speed - this didnt work, why?
        //if (N > graph.capacity()) {graph.reserve(N);}
        //graph.resize(N);
        for(unsigned int i = 0; i < N; i++){
            graph.push_back({});
        }

        // Get points and add vertices/edges to the graph
        for(unsigned int i = 0; i < M; i++){
            cin >> pi >> pj;
            pi = pi - 1;
            pj = pj - 1;            

            graph[pi].idx = pi;
            graph[pj].idx = pj;
            graph[pi].neighbors.push_back(Edge(pj,0));
            graph[pj].neighbors.push_back(Edge(pi,0));
            //cout<< "Pi: " << pi << ", tamanho vizinhanca: " << graph[pi].neighbors.size() << endl;
        }

        // Get number of soldiers
        cin >> A;

        // Get soldiers location and update cost of edges
        for(int i = 0; i < A; i++){
            cin >> ps;
            ps = ps - 1;            
            graph[ps].n_soldier += 1;
        }

        // This step could be done in the step before, it is slow
        // for all neighbors of ps, update edges to ps
        // Matrix nxn would make it easier and faster  
        for(unsigned int i = 0; i < graph.size(); i++){
            for(unsigned int j = 0; j < graph[i].neighbors.size(); j++){
                int idxNeighbor = graph[i].neighbors[j].idxNeighbor;
                graph[i].neighbors[j].cost = graph[idxNeighbor].n_soldier;
            }
        }       

        // Get start point and destiny point
        cin >> sp >> dp;
        sp = sp - 1;
        dp = dp - 1;
        Dijkstra(graph,sp);
        unsigned int finalDist = graph[dp].distance;
        finalDist += graph[sp].n_soldier;
        float finalProb = 1;

        if (graph[dp].parent == - 2){
            finalProb = 0.000;
        }
        else{
            if (finalDist > K){
                finalProb = 0;
            } else{
            finalProb = pow(prob,finalDist);
            }
        }

        cout << finalProb << endl;
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