#include<iostream>
#include<cmath>
using namespace std;

struct Node
{
    int *state;
    int totalPancake;
    //bool isGoal();
    int gapNumber();
};

int Node::gapNumber()
{
    int gap=0;
    for(int i=0;i<totalPancake-1;i++)
    {
        if(abs(state[i]-state[i+1])!=1)
            gap++;
    }
    return gap;
}

int main()
{
    int ncases;
    cin >> ncases;
    while(ncases--)
    {
        Node *N = new Node();
        cin >> N->totalPancake;
        N->state = new int[N->totalPancake];
        for(int i=0;i<N->totalPancake;i++)
            cin >> N->state[i];
        cout << N->gapNumber() << endl;
        delete N;
    }
    return 0;
}