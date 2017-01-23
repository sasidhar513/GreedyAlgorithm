#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <vector> 
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <ctime>
#include <cassert>
using namespace std; 

/*Greedy Algorithms
--------------------------------------------------------------------------------------------------------------------------------------------
* Fractional Knapsack using Greedy method
            Logic:
                Sort the Items array in the Decending Order based on the profit/weight ratio
                loop while knapsack remaining weight >0
                    fill the knapsack 

            Required modules:
                Item
                compareItem
                KnapsackGreedy

            sample example to run the code.copy the following in main()
                Item i[]{{60, 10}, {100, 20}, {120, 30}};
                int maxWeight=50;
                int size=sizeof(i)/sizeof(i[1]);
                cout<<KnapsackFractionGreedy(i,size,maxWeight);                                 */
struct Item
{
    int value;
    int weight;
    Item(int value,int weight):value(value),weight(weight){}  
};
bool compareItem(Item i1,Item i2)
{
    return (double)i1.value/i1.weight>(double)i2.value/i2.weight;
}
double KnapsackFractionGreedy(Item item[],int size,int maxWeight)
{
    double profit=0.0l;
    sort(item,item+size,compareItem);
    int i=0;
    while(maxWeight>0)
    {
         if(item[i].weight<=maxWeight)
         {
             profit+=item[i].value;
             maxWeight-=item[i].weight;
         }
        else 
        {
          profit+=((float)item[i].value/item[i].weight)*maxWeight;
          break;
        }
        i++;
    }
    return profit;
}

//-----------------------------------------------------------------------------------------------------------------------------------------
* Activity selection problem(Two arrays are given one for start time and other for end time you need to select maximum no of tasks he can complete)
            logic: The end time arrow is  sorted in ascending order so
                Pick the minimum end time and do that job. 
                pick the next min end time if the start time is after the previous end time else go for next min.
                continue the process until no job is left
            Required modules:
                ActivitySelectionProblem
            sample ecample to run the code. copy the following in main()
                int s[] =  {1, 3, 0, 5, 8, 5};
                int f[] =  {2, 4, 6, 7, 9, 9};
                int n = sizeof(s)/sizeof(s[0]);
                ActivitySelection(s, f, n);                                                         */
void ActivitySelection(int start[],int end[],int size)
{
    int prev=0;
    for(int i=0;i<size;i++)
    {
        if(start[i]>prev)
        {
            cout<<i<<" ";
            prev=end[i];
        }
    }
    return;
}

//-----------------------------------------------------------------------------------------------------------------------------------------
* KrushkalsMinimumSpanningTreees



*/
struct Edge
{
    int source;
    int dest;
    int dist;   
};
struct Graph     
{
    int V, E;
    Edge *edges;
    
};
 Graph * addEdge(int v,int e)
{
    Graph * graph=(struct Graph*) malloc( sizeof(struct Graph) );;
    graph->V=v;
    graph->E=e;
    graph->edges=(Edge *) malloc(graph->E*sizeof(Edge));
    return graph;
}
int CompareEdges(void const* a,void  const*b)
{
    Edge * a1=(Edge *) a;
    Edge * b1=(Edge *) b;
    return a1->dist>b1->dist;
}

struct subGraph
{
    int v;
    int rank;
}
int find(int child,subGraph *parent)
{
    if()
}
void print(Graph * g)
{
    for(int i=0;i<g->E;i++)
    {
        cout<<g->edges[i].source<<g->edges[i].dest<<endl;
    }
}




int main()
{

     int V = 4;  // Number of vertices in graph
    int E = 5;  // Number of edges in graph

     Graph* graph= addEdge(V,E);

    
    // add edge 0-1
    graph->edges[0].source = 0;
    graph->edges[0].dest = 1;
    graph->edges[0].dist = 10;
               cout<<"dkfasldfa"<<endl;

    // add edge 0-2
    graph->edges[1].source = 0;
    graph->edges[1].dest = 2;
    graph->edges[1].dist = 6;
 
    // add edge 0-3
    graph->edges[2].source = 0;
    graph->edges[2].dest = 3;
    graph->edges[2].dist = 5;

    // add edge 1-3
    graph->edges[3].source = 1;
    graph->edges[3].dest = 3;
    graph->edges[3].dist = 15;
 
    // add edge 2-3
    graph->edges[4].source = 2;
    graph->edges[4].dest = 3;
    graph->edges[4].dist = 4;

    qsort(graph->edges,graph->E,sizeof(graph->edges[0]),CompareEdges);
    print(graph);
}
