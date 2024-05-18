#include <bits/stdc++.h>
using namespace std; 

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
        string word;
        string language1;
        string language2;
        int cost;
        int idx_language1;
        int idx_language2;
};

// Extract values from sample string
void readSample(string input){

    // Initiate variables
    int q_words = -1;
    string from;
    string to;
    string l1;
    string l2;
    string p;

    // Using stringstream to collect values
    stringstream ss(input);
    
    while(true){        
        ss >> q_words; // Pick the number of words expected
        if (q_words == 0){break; } // Stop if no words are being expected
        ss >> from; // Pick the language we want to begin with
        ss >> to; // Pick te language we want to reach
        cout << q_words << " " << from << " " << to << endl;

        // Iterates over the string to grab the words
        for (int i = 0; i < q_words; i++ ){
            for (int j = 0; j < 3; j++){
                if (j == 0){ss >> l1;};
                if (j == 1){ss >> l2;};
                if (j == 2){ss >> p;};
            }
            cout << l1 << " " << l2 << " " << p << endl;
        }
        cout << "-------------" << endl;
    }
 
}

void extractSample(string input){
    // Initiate variables
    int q_words = -1;
    string from;
    string to;
    string l1;
    string l2;
    string p;

    // language list
    vector<string> language;

    // words list
    vector<vector<int>> words;

    // Using stringstream to collect values
    stringstream ss(input);
    
    while(true){        
        ss >> q_words; // Pick the number of words expected
        if (q_words == 0){break; } // Stop if no words are being expected
        ss >> from; // Pick the language we want to begin with
        ss >> to; // Pick te language we want to reach
        cout << q_words << " " << from << " " << to << endl;

        // Iterates over the string to grab the words
        for (int i = 0; i < q_words; i++ ){
            for (int j = 0; j < 3; j++){
                if (j == 0){ss >> l1;};
                if (j == 1){ss >> l2;};
                if (j == 2){ss >> p;};
            }
            cout << l1 << " " << l2 << " " << p << endl;
        }
        cout << "-------------" << endl;
    }
}

string shortSample(){
    string sample(
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

// Dijkstra algorithm
vector<Node> Dijkstra(vector<vector<int>> graph, Node s, vector<Node> NList, vector<vector<int>> WMatrix){
    priority_queue<Node> pq;
    // Initializing
    for(unsigned int i = 0; i < NList.size(); i++){
        NList[i].distance = INT_MAX;
        NList[i].parent = -2;
        NList[i].visited = 0;
        pq.push(NList[i]);
    }
    int idx = s.idx;
    NList[idx].distance = 0;
    NList[idx].parent = -1;
    pq.push(NList[idx]);
    while (!pq.empty()){
        Node n = pq.top();
        idx = n.idx;
        NList[idx].visited = 1;
        pq.pop();
        for(unsigned int j = 0; j < graph[idx].size(); j++){
            int neighbor_idx = graph[idx][j];
            int c = NList[idx].distance + WMatrix[idx][neighbor_idx];
            if (NList[neighbor_idx].visited == 0 && c < NList[neighbor_idx].distance){
                NList[neighbor_idx].distance = c;
                NList[neighbor_idx].parent = idx;
                pq.push(NList[neighbor_idx]);
            }
        }
    }
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
    cout << end.word << "|" << end.language << " ";
    cout << "distancia: " << end.distance << endl;
    return r;
}

void buildGraph(string input){
    // Initiate variables
    int q_words = -1;
    string from;
    string to;
    string l1;
    string l2;
    string p;

    // Using stringstream to collect values
    stringstream ss(input);
    
    while(true){

        // Graph - adjacency list
        vector<vector<int>> graph;
        graph.clear();

        // Nodes list
        vector<Node> nodeList;
        nodeList.clear();
        int idxCounter = -1; 

        // Mapping language string to int (idx)
        map<string,int> lang2idx;
        lang2idx.clear();
        int langCounter = 0;

        ss >> q_words; // Pick the number of words expected
        if (q_words == 0){break; } // Stop if no words are being expected
        ss >> from; // Pick the language we want to begin with
        ss >> to; // Pick te language we want to reach

        vector <int> idxLangTo;
        vector <int> idxLangFrom;

        // Weights Matrix
        //int weightsMatrix[q_words*2][q_words*2];
        vector<vector <int>> weightsMatrix;
        for (int i = 0; i < q_words*2; i++){
            weightsMatrix.push_back({});
            for(int j = 0; j < q_words*2; j++){
                weightsMatrix[i].push_back(0);
            }
        }      
        
        // Iterates over the string to grab the words
        for (int i = 0; i < q_words; i++ ){
            for (int j = 0; j < 3; j++){
                if (j == 0){ss >> l1;};
                if (j == 1){ss >> l2;};
                if (j == 2){ss >> p;};
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
            graph.push_back({}); // Put -1 as a neighbor just to initialize
            graph.push_back({}); // Put -1 as a neighbor just to initialize            

            // Add edge between nodes from the same language
            graph[graph.size()-2].push_back(newNode2.idx);
            graph[graph.size()-1].push_back(newNode1.idx);

            // Add wheights to the matrix
            weightsMatrix[newNode1.idx][newNode2.idx] = 0;
            weightsMatrix[newNode2.idx][newNode1.idx] = 0;
            
            // Add edge to every other with same lang and diff initial letter
            for(unsigned int k = 0; k < nodeList.size(); k++){
                if (nodeList[k].language == l1){
                    if (nodeList[k].word[0] != newNode1.word[0]){ 
                        int index = newNode1.idx;
                        graph[k].push_back(index); // Add newNode as neighbor
                        weightsMatrix[nodeList[k].idx][index] = nodeList[k].word.length(); // Add weight
                        
                        graph[graph.size()-2].push_back(nodeList[k].idx); // Add neighbor to newNode
                        weightsMatrix[index][nodeList[k].idx] = newNode1.word.length(); // Add weight

                    }
                }
                if (nodeList[k].language == l2){
                    if (nodeList[k].word[0] != newNode2.word[0]){ 
                        int index = newNode2.idx;
                        graph[k].push_back(index); // Add newNode as neighbor
                        weightsMatrix[nodeList[k].idx][index] = nodeList[k].word.length(); // Add weight
                        
                        graph[graph.size()-1].push_back(nodeList[k].idx); // Add neighbor to newNode
                        weightsMatrix[index][nodeList[k].idx] = newNode2.word.length(); // Add weight
                    }
                } 
            }
        }

        for (unsigned int i = 0; i < graph.size(); i++){
            for(unsigned int j = 0; j < graph[i].size(); j++){
                int vizinho = graph[i][j];
                int peso = weightsMatrix[i][vizinho];
                cout << "(" << vizinho << "," << peso << ")" << " ";
            }
            cout << endl;
        }
        for(unsigned int i=0; i<nodeList.size(); i++){
            cout << nodeList[i].word << " " << nodeList[i].language << endl;
        }

        std::cout << "-------------" << endl;
        
        int impossible = 0;
        int best_distance = INT_MAX;
        Node bestNodeFrom = nodeList[0];
        Node bestNodeTo = nodeList[0];
        vector<Node> bestNodeList;

        // If the languages exists in the graph
        if (idxLangFrom.size() != 0 && idxLangTo.size() != 0){            
            for(unsigned int i = 0; i<idxLangFrom.size();i++){           
                int idxFrom = idxLangFrom[i];
                vector<Node> resultNodeList = Dijkstra(graph,nodeList[idxFrom],nodeList,weightsMatrix);
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
            cout << "Impossivel, nao ha linguas no grafo" << endl;
            cout << "-----------" << endl;
        }

        //vector<Node> resultNodeList = Dijkstra(graph,nodeList[3],nodeList,weightsMatrix);
        
        if (impossible == 0){
            cout << "De: " << from << ", Para: " << to << endl;
            cout<< "Saindo de: " << bestNodeFrom.word << "|" << bestNodeFrom.language << endl;
            cout<< "Indo para: " << bestNodeTo.word << "|" << bestNodeTo.language << endl;
            /*
            for(int i = 0; i < idxLangFrom.size(); i++){
                cout << nodeList[idxLangFrom[i]].word << "|" << nodeList[idxLangFrom[i]].language << "; ";
            }
            cout << endl;
            for(int i = 0; i < idxLangTo.size(); i++){
                cout << nodeList[idxLangTo[i]].word << "|" << nodeList[idxLangTo[i]].language << "; ";
            }
            cout << endl;
            cout<< "Saindo de: " << bestNodeFrom.word << "|" << bestNodeFrom.language << endl;
            cout<< "Indo para: " << bestNodeTo.word << "|" << bestNodeTo.language << endl;
            cout<< "----------------" << endl;        
            int res = returnDijkstraResult(bestNodeList,bestNodeTo);
            cout << "resultado: " << res << endl;
            */
            int res = returnDijkstraResult(bestNodeList,bestNodeTo);
            if (res == 0){
                int distancia = bestNodeTo.distance + bestNodeTo.word.length();
                cout << "Distancia: " << distancia << endl;
                cout<< "----------------" << endl;
            }
            else{
                cout << "impossivel" << endl;
                cout << "-----------" << endl;
            }
        }
    }

}



int main() {
    string v_input;
    string sample;
    sample = mySample();
    buildGraph(sample);



    return 0;
}