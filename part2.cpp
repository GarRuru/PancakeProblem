#include <iostream>
using namespace std;

int gapNumber(int* state, int totalPancakes){
    int gap = 0;
    for(int i = 1; i < totalPancakes; i++){
        if(state[i] - state[i - 1] != 1 && state[i] - state[i - 1] != -1)
            gap++;
    }
    return gap;
}

int main(){
    int currentTestData = 0, totalTestData = 0, totalPancakes = 0, *state = 0;
    cin >> totalTestData;
    while(currentTestData < totalTestData)
    {
        cin >> totalPancakes;
        state = new int[totalPancakes];
        for(int i = 0; i < totalPancakes; i++){
            cin >> state[i];
        }
        cout << gapNumber(state, totalPancakes) << endl;
        currentTestData++;
    }
    delete [] state;
    return 0;
}
