#include <bits/stdc++.h>
using namespace std; 

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
    string a;
    a = mySample();
    cout << a;
    return 0;
}