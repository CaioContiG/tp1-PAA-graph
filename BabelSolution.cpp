#include <bits/stdc++.h>
using namespace std; 

string shortSample(){
    string sample(
    "4\n"
    "portugues frances\n"
    "ingles espanhol red\n"
    "espanhol portugues amigo\n"
    "frances ingles date\n"
    "espanhol ingles actual\n"
    "0");
    return sample;
}

// Creating a class
class Node{
    public:
        string word;
        string language;
        string language1;
        string language2;
        int idx;
        int length;
        int idx_language1;
        int idx_language2;

        // Dijkstra
        int distance;
        int parent;
        int visited;

        // Construtor
        Node(string l1,string l2,string p, int i, string lang){
            word = p;
            language = lang;
            language1 = l1;
            language2 = l2;
            idx = i;
            length = p.length();
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

string mySample(){
    // First Line, number of words
    // Second, start and finish language
    // Others, l1, l2, p: two languages and word in common
    // All strings got length 1 to 50 max, lowercase, never repeats
    string sample(
    "4\n"
    "portugues frances\n"
    "ingles espanhol red\n"
    "espanhol portugues amigo\n"
    "frances ingles date\n"
    "espanhol ingles actual\n"
    "4\n"
    "portugues alemao\n"
    "ingles espanhol red\n"
    "espanhol portugues amigo\n"
    "frances ingles date\n"
    "espanhol ingles actual\n"
    "6\n"
    "portugues frances\n"
    "ingles espanhol red\n"
    "espanhol portugues amigo\n"
    "frances ingles date\n"
    "frances espanhol la\n"
    "portugues ingles a\n"
    "espanhol ingles actual\n"
    "0");
    return sample;
}

void printGraph(vector<vector<Edge>> graph, vector<Node> NodeList){
    for(int i = 0; i < graph.size(); i++){
        for(int j = 0; j < graph[i].size(); j++){
            cout << "idV: " << graph[i][j].idxNeighbor << ", c: " << graph[i][j].cost << "; ";
            //cout << "V: " << NodeList[graph[i][j].idxNeighbor].word << ", c: " << NodeList[graph[i][j].idxNeighbor].distance << "; ";
        }
        cout << endl;
    }
}

void printList(vector<Node> nodeList){
    cout<< "---Print List---" << endl;
    for(int i = 0; i < nodeList.size(); i++){
        cout << nodeList[i].word << "|" << nodeList[i].language << "; Distancia: "<< nodeList[i].distance << endl;
    }
    cout << "---Print list end---" << endl;
}

// Dijkstra algorithm
vector<Node> Dijkstra(vector<vector<Edge>> graph, Node s, vector<Node> NList){
    priority_queue<Node> pq;
    // Initializing
    for(unsigned int i = 0; i < NList.size(); i++){
        NList[i].distance = 99999999;
        NList[i].parent = -2;
        NList[i].visited = 0;
        pq.push(NList[i]);
    }
    
    int idx = s.idx;
    NList[idx].distance = 0;
    NList[idx].parent = -1;
    //printList(NList);
    pq.push(NList[idx]);
    while (!pq.empty()){
        Node n = pq.top();
        idx = n.idx;
        NList[idx].visited = 1;
        pq.pop();
        //cout << "----pq----"<<endl;
        for(unsigned int j = 0; j < graph[idx].size(); j++){
            int neighbor_idx = graph[idx][j].idxNeighbor;
            int c = NList[idx].distance + graph[idx][j].cost;
            //cout << NList[neighbor_idx].word << "|" << NList[neighbor_idx].language << "; Distancia: "<< NList[neighbor_idx].distance << endl;

           // cout << "Custo grafo: " << NList[idx].distance <<", Custo v: " << graph[idx][j].cost << ", Custo c: " << c << endl;
            if (NList[neighbor_idx].visited == 0 && c < NList[neighbor_idx].distance){
                //cout << "Atualizou: " << NList[neighbor_idx].word <<"|"<< NList[neighbor_idx].language << ", custo:" << c<<endl;
                NList[neighbor_idx].distance = c;
                NList[neighbor_idx].parent = idx;
                pq.push(NList[neighbor_idx]);
            }
        }
    }
    //printList(NList);
  return NList;
}

// Print Dijkstra result
void printResult(vector<Node> NList, Node end){
    if (end.parent > -1 ){
        printResult(NList,NList[end.parent]);
    }
    if (end.parent == -2){
        cout << "nao chegou" << endl;
    }
    cout << end.word << "|" << end.language << " ";
    cout << "distancia: " << end.distance << endl;
}

// Return Dijkstra result
int returnDijkstraResult(vector<Node> NList, Node end){
    int r = 0;
    if (end.parent > -1 ){
        r = returnDijkstraResult(NList,NList[end.parent]);
    }
    if (end.parent == -2){
        return -1;
    }
    return r;
}

void buildGraph(){
    ifstream inputFile("babel.txt");
    cin.rdbuf(inputFile.rdbuf());
    ofstream fileOut("output.txt"); 
    cout.rdbuf(fileOut.rdbuf()); 

    // Initiate variables
    int q_words = -1;
    string from;
    string to;
    string l1;
    string l2;
    string p;

    // Using stringstream to collect values
    //stringstream ss(input);
    
    while(true){

        // Graph - adjacency list
        vector<vector<Edge>> graph;
        graph.clear();

        // Nodes list
        vector<Node> nodeList;
        nodeList.clear();
        int idxCounter = -1; 

        // Mapping language string to int (idx)
        map<string,int> lang2idx;
        lang2idx.clear();
        int langCounter = 0;

        cin >> q_words; // Pick the number of words expected
        if (q_words == 0){break; } // Stop if no words are being expected
        cin >> from; // Pick the language we want to begin with
        cin >> to; // Pick te language we want to reach

        vector <int> idxLangTo;
        vector <int> idxLangFrom;
        
        // Iterates over the string to grab the words
        for (int i = 0; i < q_words; i++ ){
            for (int j = 0; j < 3; j++){
                if (j == 0){cin >> l1;};
                if (j == 1){cin >> l2;};
                if (j == 2){cin >> p;};
            }

            // Mapping language to idx
            if(lang2idx.find(l1) == lang2idx.end()){
                lang2idx.insert({l1, langCounter});
                langCounter += 1;
            }
            if(lang2idx.find(l2) == lang2idx.end()){
                lang2idx.insert({l2, langCounter});
                langCounter += 1;
            }            

            // Push two, because one word has 2 language associated
            idxCounter += 1;          
            Node newNode1(l1,l2,p,idxCounter,l1);
            if (newNode1.language == to){
                idxLangTo.push_back(newNode1.idx);
            }
            if (newNode1.language == from){
                idxLangFrom.push_back(newNode1.idx);
            }
            idxCounter += 1;  
            Node newNode2(l1,l2,p,idxCounter,l2);
            if (newNode2.language == to){
                idxLangTo.push_back(newNode2.idx);
            }
            if (newNode2.language == from){
                idxLangFrom.push_back(newNode2.idx);
            }
            nodeList.push_back(newNode1);
            nodeList.push_back(newNode2);
            graph.push_back({}); // initialize
            graph.push_back({}); // initialize            

            // Add edge between nodes from the same language
            graph[graph.size()-2].push_back(Edge(newNode2.idx,0));
            graph[graph.size()-1].push_back(Edge(newNode1.idx,0));
            
            // Add edge to every other with same lang and diff initial letter
            for(unsigned int k = 0; k < nodeList.size(); k++){
                if (nodeList[k].language == l1){
                    if (nodeList[k].word[0] != newNode1.word[0]){ 
                        int index = newNode1.idx;
                        Edge newEdge1(index,nodeList[k].word.length());
                        graph[k].push_back(newEdge1); // Add newNode as neighbor
                        //weightsMatrix[nodeList[k].idx][index] = nodeList[k].word.length(); // Add weight
                        
                        Edge newEdge2(nodeList[k].idx,newNode1.word.length());
                        graph[graph.size()-2].push_back(newEdge2); // Add neighbor to newNode
                        //weightsMatrix[index][nodeList[k].idx] = newNode1.word.length(); // Add weight

                    }
                }
                if (nodeList[k].language == l2){
                    if (nodeList[k].word[0] != newNode2.word[0]){ 
                        int index = newNode2.idx;
                        Edge newEdge1(index,nodeList[k].word.length());
                        graph[k].push_back(newEdge1); // Add newNode as neighbor
                        //weightsMatrix[nodeList[k].idx][index] = nodeList[k].word.length(); // Add weight
                        
                        Edge newEdge2(nodeList[k].idx,newNode2.word.length());
                        graph[graph.size()-1].push_back(newEdge2); // Add neighbor to newNode
                        //weightsMatrix[index][nodeList[k].idx] = newNode2.word.length(); // Add weight
                    }
                } 
            }
        }

        int impossible = 0;
        int best_distance = INT_MAX;
        Node bestNodeFrom = nodeList[0];
        Node bestNodeTo = nodeList[0];
        vector<Node> bestNodeList;

        // If the languages exists in the graph
        if (idxLangFrom.size() != 0 && idxLangTo.size() != 0){            
            for(unsigned int i = 0; i<idxLangFrom.size();i++){           
                int idxFrom = idxLangFrom[i];
                vector<Node> resultNodeList = Dijkstra(graph,nodeList[idxFrom],nodeList);
                int less = INT_MAX;
                Node bestNode = resultNodeList[0];
                for(unsigned int j = 0; j<idxLangTo.size();j++){
                    int idxTo = idxLangTo[j];
                    int dist = resultNodeList[idxTo].distance + resultNodeList[idxTo].word.length();
                    if (dist < less){
                        less = dist;
                        bestNode = resultNodeList[idxTo];
                    }
                }
                if (less < best_distance){
                    bestNodeFrom = resultNodeList[idxFrom];
                    bestNodeTo = resultNodeList[bestNode.idx]; // ver como melhorar isso
                    best_distance = less;
                    bestNodeList = resultNodeList;
                }
            }
        }
        else{
            impossible = 1;
            cout << "impossivel" << endl;
        }
        
        if (impossible == 0){
            int res = returnDijkstraResult(bestNodeList,bestNodeTo);
            //printResult(bestNodeList,bestNodeTo);
            if (res == 0){
                int distancia = bestNodeTo.distance + bestNodeTo.word.length();
                cout << distancia << endl;
            }
            else{
                cout << "impossivel" << endl;
            }
        }
        //cout << "printando grafo: " << endl;
        //printList(bestNodeList);
        //printGraph(graph,bestNodeList);
    }

}



int main() {
    //string v_input;
    //string sample;
    //sample = mySample();
    buildGraph();
    return 0;
}