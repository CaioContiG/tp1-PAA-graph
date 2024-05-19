#include <bits/stdc++.h>
using namespace std;

 
void getVar(int& N, int& M, int& K, float& p){
    cin >> N >> M >> K >> p;
}

int main() {
    ifstream inputFile("leningrad.txt");
    cin.rdbuf(inputFile.rdbuf());
    //ofstream fileOut("output.txt"); 
    //cout.rdbuf(fileOut.rdbuf());
    
    // Declaring Variables
    int N, M, K; // Number of: strategic points, strategic roads, bullets
    float p; // probability
    int pi, pj; // point i and point j
    int A; // Number of enemy soldiers
    int ps; // Point location of enemy
    int sp, dp; // Start point and Destiny point
    
    while(true){
        // Get Initial Variables
        cin >> N >> M >> K >> p;
        if (cin.eof()){
            break;
        }

        for(int i = 0; i < M; i++){
            cin >> pi >> pj;
        }

        cin >> A;

        for(int i = 0; i < A; i++){
            cin >> ps;
        }

        cin >> sp >> dp;

        cout << N << endl;
    }




    return 0;
}

// Sample
// Important: he need to land every shot
// First Line:
    // N - number of strategic points
    // M - number of strategic roads
    // K - bullets loaded
    // P - probability of killing sniper
// Next M lines
    // i and j: road linking i to j
// Second Last line
    // A - number of shooters
    // Next A integers - position of each shot
// Last line
    // s and d: starting point and destination of soldier   
/*
3 2 10 0.1
1 2
2 3
10 1 1 3 3 1 3 1 1 3 3
1 3
5 5 10 0.3
1 2
2 4
2 5
4 5
5 3
6 3 3 3 3 3 3
1 3
*/