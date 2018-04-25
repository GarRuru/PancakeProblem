//pancake final System
#include<iostream>
using namespace std;

class Pancake{
private:
    int mynode[17]; //pancake stack
    int totalPancakes;
    int preAction;  //Part 3:Successor
    int F;
    

    public:
    Pancake()      //ctor
    { } 
    ~Pancake()
    { }
    void setup()    //Data from Keyboard
    {
        cout << "Enter total pancakes: ";
        cin >> totalPancakes;
        cout << "Pancake List: ";
        for(int i=0;i<totalPancakes;i++)
            cin >> mynode[i];
    }

    int getPancakeCount()
    {
        return totalPancakes;
    }

    int getTopCakeNo()
    {
        return mynode[0];
    }
    void printPancake()
    {
        //cout << "PanCake: [";
        for(int i=0;i<totalPancakes;i++)
            cout << " " << mynode[i];
        //cout << "]\n";
    }
    bool isGoal()       //Part 1
    {
        for(int i=0;i<totalPancakes-1;i++)
        {
            if(mynode[i] > mynode[i+1])
                return false;
        }
        return true;
    }

    int gapNumber()     //Part 2
    {
        int gap = 0;
        for(int i = 1; i < totalPancakes; i++)
        {
            if(mynode[i] - mynode[i - 1] != 1 && mynode[i] - mynode[i - 1] != -1)
                gap++;
        }
        return gap;
    }

    void upsidedownUX() //Part 3
    {
        cout << "enter g and prev. action: ";
        int g,prev;
        cin >> g >> prev;
        g++;
        for(int k=2;k<=this->getPancakeCount();k++)
        {
            if(k!=prev)
            {
                Pancake M = *this;
                //M.printPancake();
                M.upsidedown(k-1,g);
            }
        }
    }

    //K: filp position
    int upsidedown(int k,int g)   //Part 3
    {
        cout << k << " " << g << " ";
        int start = 0, temp, action = k+1;
        while(start < k)
        {
            temp = mynode[start];
            mynode[start] = mynode[k];
            mynode[k] = temp;
            start++;
            k--;
        }
        
        cout << "[" << mynode[0];
        for(int i=1;i<totalPancakes;i++)
            cout << " " << mynode[i];
            //G , GAP COUNT , F , THIS ACTION.
        cout << "]" << ", " << g << " " << this->gapNumber() << " " << g+this->gapNumber() << " " << action << endl;
        F = g+gapNumber();
        return F;
    }

    //flipCount = g,
    bool searchBestSolution(int flipCounter,int prevAction)
    {
        int minF=99,temp,minTopCake,Selected;
        Pancake pk[totalPancakes+2];
        for(int i=0;i<=totalPancakes;i++)
            pk[i] = *this;

            flipCounter++;
            for(int i=2;i<=totalPancakes;i++)
            {
                if(i != preAction)
                {
                    temp = pk[i].upsidedown(i-1,flipCounter);
                    if(minF>temp)
                        minF = temp,Selected = i;
                    else if(minF == temp && Selected < i)
                        minF = temp,Selected = i;
                }
            }

            cout << ">Mininst F: " << minF << " Flip Pos: " << Selected << endl;

        *this = pk[Selected];
        if(!isGoal())
            this->searchBestSolution(flipCounter,Selected);
        else return true;
    }

};

class HeapList
{
private:
    int No;
    int f;
    int g;
    Pancake p;
public:
    void set();
};


int main()
{

    Pancake N;
    N.setup();
    //N.upsidedownUX();
    N.searchBestSolution(0,0);
    return 0;
}
