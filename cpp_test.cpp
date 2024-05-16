#include <bits/stdc++.h>
using namespace std; 

// Creating a class
class Node{
    public:
        string word;
        string language1;
        string language2;
        int idx;
        int length;
        int idx_language1;
        int idx_language2;
        // Construtor
        Node(string l1,string l2,string p, int i){
            word = p;
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

        // Nodes list
        vector<Node> nodeList;

        // Mapping language string to int (idx)
        map<string,int> lang2idx;
        int langCounter = 0;

        ss >> q_words; // Pick the number of words expected
        if (q_words == 0){break; } // Stop if no words are being expected
        ss >> from; // Pick the language we want to begin with
        ss >> to; // Pick te language we want to reach
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

            Node newNode(l1,l2,p,i);
            nodeList.push_back(newNode);
            graph.push_back({-1}); // Put -1 as a neighbor just to initialize
            //graph[nodeList.size()-1].push_back(newNode);

            for(unsigned int k = 0; k < nodeList.size(); k++){
                if (nodeList[k].language1 == l1 || nodeList[k].language1 == l2){
                    if (nodeList[k].word[0] != newNode.word[0]){ 
                        int index = newNode.idx;
                        graph[k].push_back(index); // Add newNode as neighbor
                        graph[graph.size()-1].push_back(nodeList[k].idx); // Add neighbor to newNode
                    }
                }
                if (nodeList[k].language2 == l1 || nodeList[k].language2 == l2){
                    if (nodeList[k].word[0] != newNode.word[0]){ 
                        int index = newNode.idx;
                        graph[k].push_back(index); // Add newNode as neighbor
                        graph[graph.size()-1].push_back(nodeList[k].idx); // Add neighbor to newNode
                    }
                } 
            }
            //graph[lang2idx[l1]].push_back(newNode);
            //vector<Node> newNodeList;
            //newNodeList.push_back(newNode);

            //cout << l1 << " " << l2 << " " << p << endl;
        }

        for (unsigned int i = 0; i < graph.size(); i++){
            for(unsigned int j = 0; j < graph[i].size(); j++){
                cout << graph[i][j] << " ";
            }
            cout << endl;
        }
        for(unsigned int i=0; i<nodeList.size(); i++){
            cout << nodeList[i].word << endl;
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