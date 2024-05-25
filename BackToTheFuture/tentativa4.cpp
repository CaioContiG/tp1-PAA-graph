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

class Edge{
    public:
        int idxNeighbor;
        int cost;
        int capacity;
        int friends;

    // Constructor
    Edge(int in = 0, int c = -1){
        idxNeighbor = in;
        cost = c;
        capacity = 0;
        friends = 0;
    }
};

// Dijkstra algorithm
// If it stops when node end is closed, can be much faster
void Dijkstra(vector<Node>& graph, int sIdx, vector<vector<Edge>>& edgesMatrix){
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
            if (neighbor_idx >= 0){
                //cout << "neighbor: " << neighbor_idx << endl;
                int c = graph[idx].distance + edgesMatrix[idx][neighbor_idx].cost;
                if (graph[neighbor_idx].visited == 0 && c < graph[neighbor_idx].distance){
                    graph[neighbor_idx].distance = c;
                    graph[neighbor_idx].parent = idx;
                    pq.push(graph[neighbor_idx]);
                }
            }
        }
    }
}

// Can be faster using edgesMatrix
void removeEdges(vector<Node>& graph, int eIdx, vector<vector<Edge>>& edgesMatrix, int nFriends){

    //cout << "entrou: " << eIdx << endl;
    if(graph[eIdx].parent >= 0){
        removeEdges(graph,graph[eIdx].parent, edgesMatrix, nFriends);
        int idxParent = graph[eIdx].parent;
        edgesMatrix[idxParent][eIdx].friends = nFriends;
        
        
        // for(unsigned int i = 0; i < graph[eIdx].neighbors.size(); i++){
        //     if (graph[eIdx].neighbors[i] == idxParent){
        //         graph[eIdx].neighbors[i] = -1; // "Removed"
        //     }
        // }
        for(unsigned int i = 0; i < graph[idxParent].neighbors.size(); i++){
            if (graph[idxParent].neighbors[i] == eIdx){
                graph[idxParent].neighbors[i] = -1; // "Removed"
            }
        }
    }
}

void clearGraph(vector<Node>& graph){
    for(unsigned int i = 0; i < graph.size();i++){
        graph[i].distance = 99999999; // MAX_INT bugged sometimes
        graph[i].parent = -2;
        graph[i].visited = 0;
    }
}

// Print Dijkstra result
void printResult(vector<Node>& graph, Node end){
    cout << end.idx;
    if (end.parent > -1 ){
        cout <<  " -> ";
        printResult(graph,graph[end.parent]);
    }
    if (end.parent == -2){
        cout << "nao chegou" << endl;
    }
    //cout << end.word << "|" << end.language << " ";
    //cout << "distancia: " << end.distance << endl;
}

int main() {
    ifstream inputFile("complex2BTTF.txt");
    cin.rdbuf(inputFile.rdbuf());
    //ofstream fileOut("output.txt"); 
    //cout.rdbuf(fileOut.rdbuf());


    // Variables
    int N, M; // Number of cities and routes
    int A, B, C; // Route A<->B and cost C
    int D, K; // Number of friends and free sits
    vector<Node> graph;
    vector<vector<Edge>> edgesMatrix;

    int cnt = 0;
    while(true){
        graph.clear();
        edgesMatrix.clear();

        // Instancia Counter
        cnt += 1;

        // Getting N and M
        cin >> N >> M;

        // If EOF break loop
        if(cin.fail()){
            if (cin.eof()){break;}
        }

        // 100x100 (max) Matrix to grab edgesWeight quickly
        //int edgesWeight[100][100];

        // Initializing graph and edges - (THIS IS SLOW?)
        for(int i = 0; i < N; i++){
            graph.push_back(Node(i));
            edgesMatrix.push_back({});
        }
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                edgesMatrix[i].push_back(Edge(j,-1));
            }
        }

        // for(int i = 0; i < N; i++){
        //     for(int j = 0; j < N; j++){
        //         cout << edgesMatrix[i][j].idxNeighbor << ", ";
        //     }
        //     cout<<endl;
        // }

        //cout << N << " " << M << endl;

        // Getting A B C and Building graph
        for(int i = 0; i < M; i++){
            cin >> A >> B >> C;
            A = A - 1;
            B = B - 1;            
            //edgesWeight[A][B] = C;
            //edgesWeight[B][A] = C;

            edgesMatrix[A][B].cost = C;
            edgesMatrix[B][A].cost = C;
            
            graph[B].neighbors.push_back(A);
            graph[A].neighbors.push_back(B);
            //cout << A << " " << B << " " << C << endl;
        }

        for(unsigned int i = 0; i < graph.size(); i++){
            //cout << i << ": ";
            for(unsigned int j = 0; j < graph[i].neighbors.size();j++){
                //cout << graph[i].neighbors[j] << ", ";
            }
            //cout<<endl;
        }
        
        // Getting D and K
        cin >> D >> K;
        //cout << D << " " << K << endl;

        // Dijkstra
        //Dijkstra(graph,0,edgesWeight);
        //cout << D % K << endl;
        //cout << D / K << endl;
        //cout << "-----" << endl;
        int possible = 0;
        int totalCost = 0;
        int nFriends;

        
        if (K>=D){
            Dijkstra(graph,0,edgesMatrix);
            if(graph[N-1].parent >= 0){
                possible = 1;
                totalCost = graph[N-1].distance*D;
            }
        }
        else{
            int remaining = D % K;
            int div = D / K;
            int repeat = 0;
            if(remaining != 0){repeat = div + 1;}
            else{repeat = div;}
            //cout << "Remaining and div: "<< remaining << ", " << div << endl;
            
            for(int i = 0; i < repeat; i++){
                //cout << i << endl;
                nFriends = K;
                Dijkstra(graph,0,edgesMatrix);
                //cout<< "---" << endl;
                for(unsigned int i = 0; i < graph.size(); i++){
                    //cout << i << ": ";
                    for(unsigned int j = 0; j < graph[i].neighbors.size();j++){
                        //cout << graph[i].neighbors[j] << ", ";
                    }
                    //cout<<endl;
                }
                
                //printResult(graph,graph[N-1]);
                //cout<<endl;
                //cout<< "---" << endl;
                if(graph[N-1].parent >= 0){possible = 1;} 
                else{possible = 0; break;}
                //cout << "Distance: " << graph[N-1].distance << endl;
                if(i < repeat - 1){
                    nFriends = K;
                    //if(remaining == 0){nFriends = K;}else{nFriends = remaining;}                    
                    totalCost += graph[N-1].distance*K;
                    //cout << "Total cost " << i << ": " << totalCost << endl;
                } 
                else{
                    if(remaining == 0){nFriends = K;}else{nFriends = remaining;}  
                    //cout << "Distance:  " << graph[N-1].distance << ": " << totalCost << endl;
                    //if(remaining == 0){
                        totalCost += graph[N-1].distance*K;
                        //cout << "Total cost " << i << ": " << totalCost << endl;
                    //}else{
                    //    totalCost += graph[N-1].distance*remaining;
                    //}
                }
                //cout << "Antes do remove" << endl;
                removeEdges(graph,N-1,edgesMatrix,nFriends);
                //cout << "Depois do remove" << endl;
            }
        }


    // Calculate total cost
    //cout << "------ total cost ------" << endl;
    if(K<D){
        totalCost = 0;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                //cout << i << ", " << j << ": " << edgesMatrix[i][j].friends << endl;
                if (edgesMatrix[i][j].friends > edgesMatrix[j][i].friends){
                    //cout << i << ", " << j << ": " << edgesMatrix[i][j].friends << endl;
                    int nf = edgesMatrix[i][j].friends - edgesMatrix[j][i].friends;
                    totalCost += nf*edgesMatrix[i][j].cost;
                }
                //if (edgesMatrix[j][i].friends > edgesMatrix[i][j].friends){
                //    int nf = edgesMatrix[j][i].friends - edgesMatrix[i][j].friends;
                //    totalCost += nf*edgesMatrix[j][i].cost;
                //}            

            }
            //cout<<endl;
        }
    }
    // Final prints
    cout << "Instancia " << cnt << endl;
    if(possible == 1){
        //cout << "Sim" << endl;
        //cout << "Custo: "<< totalCost << endl;
        cout << totalCost << endl;
    }
    else{
        cout << "impossivel" << endl;
        //cout << "Custo: "<< totalCost << endl;
    }
    cout << endl;
    }
    //cout <<"fim" << endl;
    return 0;
}