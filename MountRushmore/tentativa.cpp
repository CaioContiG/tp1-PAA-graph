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
int main() {

    ifstream inputFile("SimpleMountRushmore.txt");
    cin.rdbuf(inputFile.rdbuf());
    //ofstream fileOut("output.txt"); 
    //cout.rdbuf(fileOut.rdbuf());

    // Variables
    int m, n; // number of translations, of word pairs
    char a, b; // a (letter) translates to b (letter)
    string word1, word2; // word pair

    cin >> m >> n;
    cout << m << " " << n << endl;

    for(int i = 0; i < m; i++){
        cin >> a >> b;
        cout << a << " " << b << endl;
    }

    for(int i = 0; i < n; i++){
        cin >> word1 >> word2;
        cout << word1 << " " << word2 << endl;
    }
 
    // // Mapping letter string to int (idx)
    // map<string,int> lang2idx;
    // lang2idx.clear();
    // int langCounter = 0;
    
    // // Mapping language to idx
    // if(lang2idx.find(l1) == lang2idx.end()){
    //     lang2idx.insert({l1, langCounter});
    //     langCounter += 1;
    // }
    // if(lang2idx.find(l2) == lang2idx.end()){
    //     lang2idx.insert({l2, langCounter});
    //     langCounter += 1;
    // }      
 
    return 0;
}