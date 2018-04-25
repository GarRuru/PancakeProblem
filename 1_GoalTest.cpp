#include<iostream>
using namespace std;

struct Node
{
    int *state;
    int totalPancake;
    bool isGoal();
};

bool Node::isGoal()
{
    for(int i=0;i<totalPancake-1;i++)
    {
        if(state[i] > state[i+1])
            return false;
    }
    return true;
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
        if(N->isGoal())
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
        delete N;
    }
    return 0;
}