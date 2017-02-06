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

/* Huffman coding
we will hace the charcters and their frequecies 
we should assign a code for each character so that one code is not prefix of other code 
for more problem description go to http://www.geeksforgeeks.org/greedy-algorithms-set-3-huffman-coding/
logic: 1 take all elements in minheap based on their frequencies 
       2 loop and  stop when heap has only one element   
            remove two min elements from heap  
            create another node with frequency of the sum of two min nodes 
            make first min as the left child with distance 0
            make second min as the right child with distance 1
            insert the new node in heap
       3 Traverse the tree using DFS and print all the concatinations of all distances along the path as the code of the leaf node
Main code to test the program:
        
            char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
            int freq[] = {5, 9, 12, 13, 16, 45};
            int size = sizeof(arr)/sizeof(arr[0]);
            HuffmanCodeGenerator(freq,arr,size);
*/
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
        this->left=left;
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
        Node *node1=q.top();
        q.pop();
        Node *node2=q.top();
        q.pop();
        int value=node1->value+node2->value;
        Node *newNode= new Node(value,' ',node2,node1);       
        q.push(newNode);
    }   
}
void Traversal(Node *n,string attach)
{
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
    Traversal(n,"");
}


























#include<iostream>
#include<queue>
using namespace std;
struct AdjacentNode
{
	int value;
	int distance;
	AdjacentNode* adj;
};
struct AdjacentNodeList
{
	AdjacentNode * head;
};
class Graph
{
public:

	int vertices;
	AdjacentNodeList * arr;
	Graph(int size)
	{
		this->vertices=size;
		this->arr=new AdjacentNodeList[size];
		for(int i=0;i<size;i++)
		{
			arr[i].head=NULL;
		}
	}
	void addEdge(int source,int dest ,int distance)
	{
		AdjacentNode *node=new AdjacentNode;
		node->value=dest;
		node->distance=distance;
		node->adj=arr[source].head;
		arr[source].head=node;

		AdjacentNode *node1=new AdjacentNode;
		node1->value=source;
		node1->distance=distance;
		node1->adj=arr[dest].head;
		arr[dest].head=node1;
	}
};
struct node
{
	int value;
	int key;
	node(int value,int key)
	{
		this->key=key;
		this->value=value;
	}
};
struct compare
{
	bool operator()(node * l,node * r)
	{
		return l->key>r->key;
	}
};
void printPRIMS(Graph * d)
{
	priority_queue<node *,vector<node *>,compare> heap;
	for(int i=1;i<9;i++)
	{
		node *n =new node(i,9999);
		heap.push(n);
	}
	node *n =new node(0,0);
	heap.push(n);
	while(!heap.empty())
	{
		node *n=
	}

}
int main()
{
	Graph* d=new Graph(9);
	d->addEdge( 0, 1, 4);
	d->addEdge( 0, 7, 8);
	d->addEdge( 1, 2, 8);
	d->addEdge( 1, 7, 11);
	d->addEdge( 2, 3, 7);
	d->addEdge( 2, 8, 2);
	d->addEdge( 2, 5, 4);
	d->addEdge( 3, 4, 9);
	d->addEdge( 3, 5, 14);
	d->addEdge( 4, 5, 10);
	d->addEdge( 5, 6, 2);
	d->addEdge( 6, 7, 1);
	d->addEdge( 6, 8, 6);
	d->addEdge( 7, 8, 7);
	printPRIMS(d);
}
