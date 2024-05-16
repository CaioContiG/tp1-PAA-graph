#include <bits/stdc++.h>
using namespace std; 

// Creating a class
class Node{
    public:
        string word;
        string language;
        string language1;
        string language2;
        int distance;
        int idx;
        int length;
        int idx_language1;
        int idx_language2;
        // Construtor
        Node(string l1,string l2,string p, int i, string lang){
            word = p;
            language = lang;
            language1 = l1;
            language2 = l2;
            idx = i;
            length = p.length();
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

        // Weights Matrix
        int weightsMatrix[q_words*2][q_words*2];

        //cout << q_words << " " << from << " " << to << endl;
        
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
            idxCounter += 1;  
            Node newNode2(l1,l2,p,idxCounter,l2);
            nodeList.push_back(newNode1);
            nodeList.push_back(newNode2);
            graph.push_back({-1}); // Put -1 as a neighbor just to initialize
            graph.push_back({-1}); // Put -1 as a neighbor just to initialize
            //graph[nodeList.size()-1].push_back(newNode);

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
            //graph[lang2idx[l1]].push_back(newNode);
            //vector<Node> newNodeList;
            //newNodeList.push_back(newNode);

            //cout << l1 << " " << l2 << " " << p << endl;
        }

        for (unsigned int i = 0; i < graph.size(); i++){
            for(unsigned int j = 1; j < graph[i].size(); j++){
                int vizinho = graph[i][j];
                int peso = weightsMatrix[i][vizinho];
                cout << "(" << vizinho << "," << peso << ")" << " ";
            }
            cout << endl;
        }
        for(unsigned int i=0; i<nodeList.size(); i++){
            cout << nodeList[i].word << " " << nodeList[i].language << endl;
        }
        
        //map<string, int>::iterator it = lang2idx.begin();
        //while(it != lang2idx.end()){
        //    cout << "Key: " << it->first << ", Value: " << it->second << endl;
        //    ++it;
        //}
        std::cout << "-------------" << endl;
    }

}

int main() {
    string v_input;
    //cin >> v_input;
    //cout << v_input;
    string sample;
    sample = mySample();
    //readSample(sample);
    buildGraph(sample);

    //vector<vector<int>> graph;
    //vector<int> v1 = {1, 2, 3};
    //graph.push_back(v1);
    //graph.push_back({1});
    //graph[0].push_back(5);
    //graph[1].push_back(5);
    //graph[1].push_back(6);

    //cout << graph[0][2] << endl;
    //cout << graph[1][0] << endl;
    //cout << graph[1][1] << endl;
    //for(int i; i < graph[1].size(); i++){
    //    cout << graph[1][i] << endl;
    //}    

    return 0;
}