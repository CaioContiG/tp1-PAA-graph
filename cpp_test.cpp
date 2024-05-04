#include <bits/stdc++.h>
using namespace std; 

// Node as words or edges as words? Let's try edges
// Adjacency Matrix


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

int main() {
    string v_input;
    //cin >> v_input;
    //cout << v_input;
    string sample;
    sample = mySample();
    readSample(sample);   

    return 0;
}