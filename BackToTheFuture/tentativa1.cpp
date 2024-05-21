#include <bits/stdc++.h>  
using namespace std;

// Node class
class Node{
    public:
        int idx;
        vector<int> neighbors;

        // DFS
        int parent;
        int visited;
        int cost;

        // Construtor
        Node(int i = -1){
            idx = i;
            parent = -2;
            visited = 0;
            cost = 0;
        }
};

int main() {
    ifstream inputFile("SimpleBTTF.txt");
    cin.rdbuf(inputFile.rdbuf());
    //ofstream fileOut("output.txt"); 
    //cout.rdbuf(fileOut.rdbuf());
    int cnt = 0;
    while(true){
        
        // Instancia Counter
        cnt += 1;

        // Variables
        int N, M; // Number of cities and routes
        int A, B, C; // Route A<->B and cost C
        int D, K; // Number of friends and free sits

        // Getting N and M
        cin >> N >> M;

        // If EOF break loop
        if(cin.fail()){
            if (cin.eof()){break;}
        }

        cout << N << " " << M << endl;

        for(int i = 0; i < M; i++){
            cin >> A >> B >> C;
            cout << A << " " << B << " " << C << endl;;
        }

        cin >> D >> K;
        cout << D << " " << K << endl;

    }
    return 0;
}