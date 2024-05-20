#include <bits/stdc++.h>
using namespace std;

// Creating a class
class Node{
    public:
        int idx;

        // Dijkstra
        int distance;
        int parent;
        int visited;

        // Construtor
        Node(int i){
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

    // Constructor
    Edge(int in, int c){
        idxNeighbor = in;
        cost = c;
    }
};

int main() {
    ifstream inputFile("simpleFF.txt");
    cin.rdbuf(inputFile.rdbuf());
    //ofstream fileOut("output.txt"); 
    //cout.rdbuf(fileOut.rdbuf());
    
    // Variables
    int C, N; // number of test cases and people
    float x, y; // position of people

    // Grab C - not using
    cin >> C;
    cout << C << endl;

    while (true)
    {   
        // Grab number of people
        cin >> N;
        // If EOF break loop
        // I don't need to use C;
        if(cin.fail()){if (cin.eof()){break;}}
        cout << N << endl;

        // Grab people's position
        for(int i = 0; i < N; i++){
            cin >> x >> y;
            cout << x << " " << y << endl;
        }
         
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