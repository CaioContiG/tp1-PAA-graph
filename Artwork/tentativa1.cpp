#include <iostream>
 
using namespace std;
 
int main() {
    //ifstream inputFile("simpleFF.txt");
    //cin.rdbuf(inputFile.rdbuf());
    //ofstream fileOut("output.txt"); 
    //cout.rdbuf(fileOut.rdbuf());

    // Variables
    int M, N, K; // (M,N) Room size (x+,y+), K number of sensors
    int X, Y, S; // Sensor location, Sensor range

    // Getting variables
    cin >> M >> N >> K;
    cout << M << " " << N << " " << K << endl;
    // Getting sensors and building graph
    for(int i = 0; i < K; i++){
        
        // Getting sensors info
        cin >> X >> Y >> S;
        cout << X << " " << Y << " " << S << endl; 
    }  

    return 0;
}