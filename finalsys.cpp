//pancake final System
#include<iostream>
using namespace std;

int TOTALPANCAKES;

class Pancake{
public:
    int mynode[17]; //pancake stack
    int totalPancakes;
    int preAction;  //Part 3:Successor
    int F;
    int g,h;

    Pancake();
    ~Pancake();
    int getPancakeCount();
    int getTopCakeNo();
    void printPancake();
    void setup();
    bool isGoal();
    int gapNumber();
    void upsidedownUX();
    void upsidedown(int,int);
    bool searchBestSolution(int flipCounter,int preAction);
    int compareState(const Pancake&);
    
};

void swapNode(Pancake *x, Pancake *y)
{
    Pancake temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
class Heap
{
public:
    int heapSize;
    int No;
    int h;
    int g;
    Pancake *p;

    Heap();
    ~Heap();
    int f(Pancake &pcake);
    int parent(int index);
    int left(int index);
    int right(int index);
    void insert(int state[] , int g ,int h,int);
    Pancake getTop();
    void minHeapify(int index);
    bool isEmpty();
};


Heap *heap;



Heap::Heap() : heapSize(0), p(new Pancake[100]) {}

Heap::~Heap()
{
    //for(int i=0 ;i< heapSize ;i++)
        //delete[] p[i].mynode;
        //delete p[i];
    delete[] p;
}

int Heap::f(Pancake &node)
{
    return (node.g + node.h);
}

int Heap::parent(int index)
{
    return (index- 1) / 2;
}

int Heap::left(int index)
{
    return (index *2) + 1;
}

int Heap::right(int index)
{
    return (index *2) +2;
}

void Heap::insert(int state[] , int g ,int h,int preAction)
{
    int i,j;
    for(i=0;i<TOTALPANCAKES;i++)   p[heapSize].mynode[i] = state[i];
    p[heapSize].totalPancakes = TOTALPANCAKES;
    p[heapSize].F = g+h;
    p[heapSize].g = g;
    p[heapSize].h = h;
    p[heapSize].preAction = preAction;
    bool needSwap;
    i = heapSize;
    while(i != 0 && f(p[parent(i)]) >= f(p[i]))
    {
        needSwap = true;

        if(f(p[parent(i)]) == f(p[i]))
        {
            for(j=0;j<TOTALPANCAKES;j++)
            {
                if(p[parent(i)].mynode[j] < p[i].mynode[j])
                {
                    needSwap = false;
                    break;
                }
                else if(p[parent(i)].mynode[j] > p[i].mynode[j])
                    break;
            }
        }

        if(needSwap)
        {
            swapNode(&p[parent(i)], &p[i]);
            i = parent(i);
        }
        else break;
    }

    heapSize++;
}

Pancake Heap::getTop()
{
    if(heapSize == 1)
    {
        heapSize--;
        return p[0];
    }

    Pancake root = p[0];
    p[0] = p[heapSize-1];
    heapSize--;
    minHeapify(0);

    return root;

}

void Heap::minHeapify(int index)
{
    int l = left(index);
    int r = right(index);
    int smallest = index;
    int i;

    if( l < heapSize && f(p[l]) < f(p[index]))
        smallest=l;
    else if( l < heapSize && f(p[l]) == f(p[index]))
    {
        for(i = 0; i <TOTALPANCAKES; i++)
        {
            if(p[l].mynode[i] < p[index].mynode[i])
            {
                smallest = l;
                break;
            }
            else if(p[l].mynode[i] > p[index].mynode[i])
                break;
        }
    }

    if(r < heapSize && f(p[r]) < f(p[smallest]))
        smallest=r;
    else if(r<heapSize && f(p[r]) == f(p[smallest]))
    {
        for(i=0;i<TOTALPANCAKES;i++)
        {
            if(p[r].mynode[i] < p[smallest].mynode[i])
            {
                smallest = r;
                break;
            }
            else if(p[r].mynode[i] > p[smallest].mynode[i])
                break;
        }
    }

    if(smallest != index)
    {
        swapNode(&p[index], &p[smallest]);
        minHeapify(smallest);
    }
}

bool Heap::isEmpty()
{
    return (heapSize == 0 ? true : false);
}



Pancake::Pancake()      //ctor
{ } 
Pancake::~Pancake()
{ }
void Pancake::setup()    //Data from Keyboard
{
    cout << "Enter total pancakes: ";
    cin >> totalPancakes;
    TOTALPANCAKES = totalPancakes;
    cout << "Pancake List: ";
    for(int i=0;i<totalPancakes;i++)
        cin >> mynode[i];
}

int Pancake::getPancakeCount()
{
    return totalPancakes;
}

int Pancake::getTopCakeNo()
{
    return mynode[0];
}
void Pancake::printPancake()
{
    //cout << "PanCake: [";
    for(int i=0;i<totalPancakes;i++)
        cout << " " << mynode[i];
    //cout << "]\n";
}
bool Pancake::isGoal()       //Part 1
{
    for(int i=0;i<totalPancakes-1;i++)
    {
        if(mynode[i] > mynode[i+1])
            return false;
    }
    return true;
}

int Pancake::gapNumber()     //Part 2
{
    int gap = 0;
    for(int i = 1; i < totalPancakes; i++)
    {
        if(mynode[i] - mynode[i - 1] != 1 && mynode[i] - mynode[i - 1] != -1)
            gap++;
    }
    return gap;
}

void Pancake::upsidedownUX() //Part 3
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
void Pancake::upsidedown(int k,int g)   //Part 3
{
    //cout << k << " " << g << " ";
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

    preAction = action;
    //heap->insert(this->mynode,g,this->gapNumber());
    //return F;
}


//flipCount = g,
bool Pancake::searchBestSolution(int flipCounter,int prevAction)
{
    cout<< "PREV " <<  prevAction << endl;
    int minF=99,temp,minTopCake,Selected;
    Pancake pk[totalPancakes+2];
    for(int i=0;i<=totalPancakes;i++)
    {
        pk[i] = *this;
        pk[i].preAction = preAction;
    }
        flipCounter++;
        for(int i=2;i<=totalPancakes;i++)
        {
            if(i != preAction)
            {
                pk[i].upsidedown(i-1,flipCounter);
                heap->insert(pk[i].mynode,flipCounter,pk[i].gapNumber(),pk[i].preAction);
               
            //    if(minF>temp)
            //        minF = temp,Selected = i;
            //   else if(minF == temp && this->compareState(pk[i]) == 1)
            //        minF = temp,Selected = i;
            }
        }

        *this = heap->getTop();
        heap->heapSize = 0;
        this->printPancake();
        cout << "  >Mininst F:" << this->F << " Flip Pos: \n"; 
        //cout << ">Mininst F: " << minF << " Flip Pos: " << Selected << endl;

    //*this = pk[Selected];
    if(!isGoal())
        this->searchBestSolution(flipCounter,this->preAction);
    else return true;
}


int Pancake::compareState(const Pancake &P)
{
    for(int i=0;i<totalPancakes;i++)
    {
        if(this->mynode[i] > P.mynode[i])
            return 1;
        else if(this->mynode[i] < P.mynode[i])
            return -1;
        else continue;
    }
}


int main()
{
    heap = new Heap();
    Pancake N;
    N.setup();
    //N.upsidedownUX();
    N.searchBestSolution(0,0);
    return 0;
}