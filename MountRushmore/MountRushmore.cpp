#include <bits/stdc++.h> 
using namespace std;

 // Node class
class Node{
    public:
        int idx;
        double x;
        double y;
        vector<int> neighbors;

        // DFS
        int parent;
        int visited;

        // Construtor
        Node(int i = -1){
            idx = i;
            parent = -2;
            visited = 0;
        }
};

int DFS(vector<Node>& graph, Node v, Node objective){
    int idx = v.idx;
    int idxObjective = objective.idx;
    graph[idx].visited = 1;
    int result = 0;
    if (idx == idxObjective){
        result = 1;
        return result;
    }
    else{
        for(unsigned int i = 0; i < graph[idx].neighbors.size(); i++){
            int idxNeighbor = graph[idx].neighbors[i];
            if(graph[idxNeighbor].visited == 0){
                result = DFS(graph,graph[idxNeighbor],objective);
                if (result == 1){break;}
            }
        }
    }
    return result;
}

int main() {
    // Variables
    int m, n; // number of translations, of word pairs
    char a, b; // a (letter) translates to b (letter)
    string word1, word2; // word pair
    vector<Node> graph;
    map<char,int> word2idx;

    cin >> m >> n;

    // Getting translations - Building Graph
    int cnt = 0;
    for(int i = 0; i < m; i++){
        cin >> a >> b;

        // If word wasn't added yet (maybe it is not needed as map has one key per element?)
        if(word2idx.find(a) == word2idx.end()) {            
            word2idx.insert({a,cnt});
            graph.push_back(Node(cnt));
            cnt += 1;
        }        
        if(word2idx.find(b) == word2idx.end()) {            
            word2idx.insert({b,cnt});
            graph.push_back(Node(cnt));
            cnt += 1;
        }        

        int idxL1 = word2idx[a];
        int idxL2 = word2idx[b];
        graph[idxL1].neighbors.push_back(idxL2);
    }

    // Testing pairs
    int result = 0;    
    for(int i = 0; i < n; i++){
        cin >> word1 >> word2;
        int wordResult = 0; 
        if (word1.size() == word2.size()){
            for(unsigned int j = 0; j < word1.size();j++){
                // If letters exists in map
                if(word2idx.find(word1[j]) != word2idx.end() && word2idx.find(word2[j]) != word2idx.end()){
                    // Setting start node and end node
                    Node start(word2idx[word1[j]]);
                    Node to(word2idx[word2[j]]);
                
                    // Clearing visited graph
                    for(unsigned int k = 0; k < graph.size(); k++){
                        graph[k].visited = 0;
                    }

                    // Searching path
                    wordResult = DFS(graph,start,to);                
                    if (wordResult == 0){
                        result = 0;
                        break;
                    }
                    else{
                        result = 1;
                    }
                } else { // Letters don't exist im map
                    if (word1[j] == word2[j]){
                        result = 1;
                    }else{
                        result = 0;
                        break;
                    }
                }
            }
        }
        else{
            result = 0;
        }

        if(result == 1){
            cout << "yes" << endl;
        }
        else{
            cout << "no" << endl;
        }
    }
 
    return 0;
}