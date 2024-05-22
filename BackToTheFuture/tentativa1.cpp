#include <bits/stdc++.h>  
using namespace std;

// Node class
class Node{
    public:
        int idx;
        vector<int> neighbors;

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

// Dijkstra algorithm
// If it stops when node end is closed, can be much faster
void Dijkstra(vector<Node>& graph, int sIdx, int edgesMatrix[100][100]){
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
       // cout << "pq popou: " << idx<< endl;
        for(unsigned int j = 0; j < graph[idx].neighbors.size(); j++){
            //cout << "entrou no for" << endl;
            int neighbor_idx = graph[idx].neighbors[j];
            //cout << "neighbor: " << neighbor_idx << endl;
            int c = graph[idx].distance + edgesMatrix[idx][neighbor_idx];
            if (graph[neighbor_idx].visited == 0 && c < graph[neighbor_idx].distance){
                graph[neighbor_idx].distance = c;
                graph[neighbor_idx].parent = idx;
                pq.push(graph[neighbor_idx]);
            }
        }
    }
}

int main() {
    ifstream inputFile("SimpleBTTF.txt");
    cin.rdbuf(inputFile.rdbuf());
    //ofstream fileOut("output.txt"); 
    //cout.rdbuf(fileOut.rdbuf());


    // Variables
    int N, M; // Number of cities and routes
    int A, B, C; // Route A<->B and cost C
    int D, K; // Number of friends and free sits
    vector<Node> graph;

    int cnt = 0;
    while(true){
        graph.clear();

        // Instancia Counter
        cnt += 1;

        // Getting N and M
        cin >> N >> M;

        // If EOF break loop
        if(cin.fail()){
            if (cin.eof()){break;}
        }

        // 100x100 (max) Matrix to grab edgesWeight quickly
        int edgesWeight[100][100];

        // Initializing graph - (THIS IS SLOW?)
        for(int i = 0; i < N; i++){
            graph.push_back(Node(i));
        }

        cout << N << " " << M << endl;

        // Getting A B C and Building graph
        for(int i = 0; i < M; i++){
            cin >> A >> B >> C;
            A = A - 1;
            B = B - 1;            
            edgesWeight[A][B] = C;
            edgesWeight[B][A] = C;
            graph[B].neighbors.push_back(A);
            graph[A].neighbors.push_back(B);
            cout << A << " " << B << " " << C << endl;
        }

        //for(int i = 0; i < graph.size(); i++){
        //    cout << i << ": ";
        //    for(int j = 0; j < graph[i].neighbors.size();j++){
        //        cout << graph[i].neighbors[j] << ", ";
        //    }
        //    cout<<endl;
        //}
        
        // Getting D and K
        cin >> D >> K;
        cout << D << " " << K << endl;

        // Dijkstra
        Dijkstra(graph,0,edgesWeight);

    }
    return 0;
}