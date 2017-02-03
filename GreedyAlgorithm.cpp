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
/* Activity selection problem(Two arrays are given one for start time and other for end time you need to select maximum no of tasks he can complete)
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
/* KrushkalsMinimumSpanningTreees (Given the undirected weighed graph,the Minimum Weight Spanning Tree is the sub graph that is a tree that connects all nodes and total weight is minimum 
            logic: save graph 
                   sort the Edges based on weight in the increasing order
                   loop while the result contains V-1 edges:
                        take each edge and form a tree using union-find(that checks if there are any loops )
                        if that edge doesnt form a loop  add it to the result
            Required Modules:
                        Edge
                        Graph
                        addEdge
                        CompareEdges
                        subGraph
                        find
                        unionFind
                        KrushkalMST
            sample ecample to run the code. copy the following in main()
                            int V = 4;  // Number of vertices in graph
                            int E = 5;  // Number of edges in graph
                            Graph* graph= addEdge(V,E);   
                            // add edge 0-1
                            graph->edges[0].source = 0;
                            graph->edges[0].dest = 1;
                            graph->edges[0].dist = 10;
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
                            KrushkalMST(graph);
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
    int parent;
    int rank;
};
int find(int child,subGraph *parents)
{
    if(parents[child].parent!=child)
        parents[child].parent=find(parents[child].parent,parents);
    return parents[child].parent;
}
void unionFind(int child1,int child2,subGraph* parents)
{
    int  parent1=find(child1,parents);
    int parent2=find(child2,parents);
  
    if(parents[parent1].rank>parents[parent2].rank)
        parents[parent2].parent=parent1;
    else if(parents[parent2].rank>parents[parent1].rank)
        parents[parent1].parent=parent2;
    else 
    {
        parents[parent2].parent=parent1;
        parents[parent1].rank+=1;    
    }
}
void KrushkalMST(Graph  * graph)
{
    qsort(graph->edges,graph->E,sizeof(graph->edges[0]),CompareEdges);
    subGraph *g=(subGraph *)malloc(graph->V*sizeof(subGraph));
    for( int i=0;i<graph->V;i++)
    {
        g[i].parent=i;
        g[i].rank=0;
    }
    Edge * result= (Edge  *)malloc((graph->V-1)*sizeof(Edge));
    int j=0,i=0;
    while(j<(graph->V-1))
    {
        int vertex1= find(graph->edges[i].source,g);
        int vertex2= find(graph->edges[i].dest,g);
        if(vertex1!=vertex2)
        {
            cout<<vertex1<<vertex2<<i<<endl;            
             result[j++]=graph->edges[i];
             unionFind(vertex1, vertex2, g);
        }
    i++;        
    }
    for(int i=0;i<j;i++)
        cout<<result[i].source<<"\t"<<result[i].dest<<"     "<<result[i].dist<<endl;
}
//-------------------------------------------------------------------------------------------------------------------------------------


#include<iostream>
#include<queue>

using namespace std;

struct Node
{
    int value;
    char chValue;
    int rightDistance;
    int leftDistance;
    Node * right;
    Node * left;    
   
};

bool operator<(const Node & a , const Node & b)
{
    return a.value>b.value;
}
priority_queue<Node >  HuffmanCodeGenerator(int * valueArr, char * chValueArr, int size)
{
    priority_queue<Node > q;
    
    for(int i=0;i<size;i++)
    {
        Node newNode;
        newNode.value=valueArr[i];
        newNode.chValue=chValueArr[i];
        q.push(newNode);
    }
    HuffmanCodeGeneratorUtil(q);
    return q;
}
Node * HuffmanCodeGeneratorUtil(priority_queue<Node> q)
{
    while(q.size()!=1)
    {
        Node node1=q.pop();
        Node node2=q.pop();
        Node newNode;
        newNode.vlaue=node1.value+node2.value;
        newNode.chValue='';
        newNode.rightDistance='0';
        newNode.leftDistance='1';
        newNode.right=
    }
    
}

void printQueue(priority_queue<Node > q)
{
    int end=q.size();
    for( int i=0;i<end ;i++)
    {     
        Node  n= q.top();
        q.pop();
        cout<<n.value<<endl;
    }  

}
int main()
{
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(arr)/sizeof(arr[0]);
    priority_queue<Node > n=HuffmanCodeGenerator(freq,arr,size);
    printQueue(n);
    
}



















#include<iostream>
#include<queue>

using namespace std;

struct Node
{
    int value;
    char chValue;
    Node * right;
    Node * left;    
   
};
void printQueue(priority_queue<Node > q)
{
    int end=q.size();
    for( int i=0;i<end ;i++)
    {     
        Node  n= q.top();
        q.pop();
        cout<<n.value<<endl;
    }  

}

bool operator<(const Node & a , const Node & b)
{
    return a.value>b.value;
}
Node *HuffmanCodeGeneratorUtil(priority_queue<Node> q)
{
    while(q.size()!=1)
    {
        cout<<"printing " <<endl;
        printQueue(q);
        Node node1=q.top();
        q.pop();
        Node node2=q.top();
        q.pop();
        Node newNode;
        newNode.value=node1.value+node2.value;
        newNode.chValue=' ';
        newNode.right=&node2;
        newNode.left=&node1;
        cout<<" formed the new node value "<<newNode.value<<" with the values from "<<newNode.right->value<<" and " <<newNode.left->value<<endl;
        q.push(newNode);
    }
    Node n=q.top();
    return &n;
    
    
}
void Traversal(Node * n,string attach)
{
        cout<<"passed here "<<n->value<<endl;

    if(n->left==NULL&&n->right==NULL)
    {
          cout<<"this "<<n->chValue<< " "<<attach<<endl;
    }
    else
    {
        Traversal(n->left,attach+"0");
        Traversal(n->right,attach+"1");
    }
}
void   HuffmanCodeGenerator(int * valueArr, char * chValueArr, int size)
{
    priority_queue<Node > q;
    
    for(int i=0;i<size;i++)
    {
        Node newNode;
        newNode.value=valueArr[i];
        newNode.chValue=chValueArr[i];
        newNode.left=NULL;
        newNode.right=NULL;
        q.push(newNode);
    }
    Node *n=HuffmanCodeGeneratorUtil(q);
        int s=n->left->value;

    cout<<" formed the new node value "<<n->value<<" with the values from "<<n->right->value<<" and " <<n->left->value<<endl;
    //Node *m=n.left;
    //int s=n->left->value;
        cout<<" formed the new node value "<<" "<<s<<endl;//<<" with the values from "<<m->right->value<<" and " <<m->left->value<<endl;

    //Traversal(&n,"");
}



int main()
{
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(arr)/sizeof(arr[0]);
    HuffmanCodeGenerator(freq,arr,size);
    
}


#include<iostream>
#include<queue>

using namespace std;

struct Node
{
    int value;
    char chValue;
    Node * right;
    Node * left;   
    Node(int val,int chVal,Node * right ,Node * left )
    {
        this->value=val;
        this->chValue=chVal;
        this->right=right;
        this->left=right;
    }
    Node(){}
   
};
void printQueue(priority_queue<Node > q)
{
    int end=q.size();
    for( int i=0;i<end ;i++)
    {     
        Node  n= q.top();
        q.pop();
        cout<<n.value<<endl;
    }  

}
struct  compare
{
    bool operator()(Node * l ,Node * r)
    {
        return l->value >r->value ;
    }
};
bool operator<(const Node & a , const Node & b)
{
    return a.value>b.value;
}
void HuffmanCodeGeneratorUtil(priority_queue<Node *,vector<Node *>, compare> &q)
{
    while(q.size()!=1)
    {
        //printQueue(q);
        Node *node1=q.top();
        q.pop();
        Node *node2=q.top();
        q.pop();
        int value=node1->value+node2->value;
        Node *newNode= new Node(value,' ',node2,node1);
       
        newNode->right=node2;
        newNode->left=node1;
        q.push(newNode);
    }   
}
void Traversal(Node *n,string attach)
{
        //cout<<"passed here "<<n->value<<endl;

    if(n->left==NULL&&n->right==NULL)
    {
          cout<<n->chValue<< " "<<attach<<endl;
    }
    else
    {
        Traversal(n->left,attach+"0");
        Traversal(n->right,attach+"1");
    }
}
void   HuffmanCodeGenerator(int * valueArr, char * chValueArr, int size)
{
    priority_queue<Node *,vector<Node *>,compare > q;    
    for(int i=0;i<size;i++)
       q.push(new Node(valueArr[i],chValueArr[i],NULL,NULL));
    HuffmanCodeGeneratorUtil(q);
    Node *n=q.top();
    //cout<<n.value<<endl;
    Traversal(n,"");
}



int main()
{
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(arr)/sizeof(arr[0]);
    HuffmanCodeGenerator(freq,arr,size);
    
}
