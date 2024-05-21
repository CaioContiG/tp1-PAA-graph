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

    ifstream inputFile("SimpleMountRushmore.txt");
    cin.rdbuf(inputFile.rdbuf());
    ofstream fileOut("output.txt"); 
    cout.rdbuf(fileOut.rdbuf());

    // Variables
    int m, n; // number of translations, of word pairs
    char a, b; // a (letter) translates to b (letter)
    string word1, word2; // word pair
    vector<Node> graph;
    map<char,int> word2idx;

    cin >> m >> n;
    //cout << m << " " << n << endl;

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
        //cout << a << " " << b << endl;
    }

    // Testing pairs
    int result = 0;    
    for(int i = 0; i < n; i++){
        cin >> word1 >> word2;

        if (word1.size() == word2.size()){
            for(unsigned int j = 0; j < word1.size();j++){

                // Setting start node and end node
                Node start(word2idx[word1[j]]);
                Node to(word2idx[word2[j]]);

                // Clearing visited graph
                for(unsigned int k = 0; k < graph.size(); k++){
                    graph[k].visited = 0;
                    graph[k].parent = -2;
                }

                // Searching path
                if(word2idx.find(word1[j]) != word2idx.end() && word2idx.find(word2[j]) != word2idx.end()) { // If letter exist
                    int idxStart = word2idx[word1[j]];
                    graph[idxStart].parent = -1;
                    DFS(graph,start);                
                    int idxTarget = word2idx[word2[j]];
                    if (graph[idxTarget].parent == -2){
                    } else {
                        result = 1;
                    }
                } else {
                    result = 0;
                }

            }
        }
        else{
            result = 0;
        }

        //cout << word1 << " " << word2 << endl;
        if(result == 1){
            cout << "yes" << endl;
        }
        else{
            cout << "no" << endl;
        }
        //cout << result << endl;
    }
 
    return 0;
}