#include <bits/stdc++.h> 
using namespace std;

 // Node class
class Node{
    public:
        int idx;
        double x;
        double y;
        char letter;
        vector<int> neighbors;

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
    vector<Node> graph;
    map<char,int> word2idx;

    cin >> m >> n;
    cout << m << " " << n << endl;

    // Getting translations - Building Graph
    int cnt = 0;
    for(int i = 0; i < m; i++){
        cin >> a >> b;

        // If word wasn't added yet (maybe it is not needed as map has one key per element?)
        if(word2idx.find(a) == word2idx.end()) {            
            word2idx.insert({a,cnt});
            graph.push_back(Node(cnt));
            graph[cnt].letter = a;
            cnt += 1;
        }        
        if(word2idx.find(b) == word2idx.end()) {            
            word2idx.insert({b,cnt});
            graph.push_back(Node(cnt));
            graph[cnt].letter = b;
            cnt += 1;
        }        

        int idxL1 = word2idx[a];
        int idxL2 = word2idx[b];
        graph[idxL1].neighbors.push_back(idxL2);
        cout << a << " " << b << endl;
    }

    cout << "KEY\tELEMENT\n"; 
    for (auto itr = word2idx.begin(); itr != word2idx.end(); ++itr) { 
        cout << itr->first 
             << '\t' << itr->second << '\n'; 
    }
cout << "----------" << endl;

    // Testing pairs
    for(int i = 0; i < n; i++){
        cin >> word1 >> word2;

        if (word1.size() == word2.size()){
            for(unsigned int j = 0; j < word1.size();j++){
                // DFS
            }
        }   
        else{
            // cout << "different size" << endl;
        }

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