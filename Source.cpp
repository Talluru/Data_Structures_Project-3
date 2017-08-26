// Gowtham Talluru Project-3


# include <iostream>
# include <queue>
# include <stack>
using namespace std;

bool found( int *arr, int e, int n)
{
	bool f = false;
	for (int i = 0; i < n; i++)
	{
		if (arr[i] == e) { return true; }
	}

	return false;
}

class BitMatrixGraph {

	 friend  ostream& operator<<(ostream& s, BitMatrixGraph& b);      // Prints Adjacency list

protected:
	unsigned char** bitAdjacencyMatrix;
	int n;				 //number of nodes in the graph
	int size;			 //number of char in each row

public:
	BitMatrixGraph();
	BitMatrixGraph(int numNodes);
	BitMatrixGraph(BitMatrixGraph& otherGraph);
	void copy(BitMatrixGraph& b);		// copy method
	virtual ~BitMatrixGraph();
	int getNumNodes();
	void printBits(unsigned char s);
	void addEdge(int u, int v);
	bool isAnEdge(int u, int v);
	void print();   // Prints the Adjacency Matrix
	void operator=(BitMatrixGraph& b);
};


// Empty Constructor
BitMatrixGraph::BitMatrixGraph()
{
	// Creating a 8x8 matrix for de
	n = 8;

	size = 1;

	// Initilizing the array of char arrays
	bitAdjacencyMatrix = new unsigned char*[n];
	for (int i = 0; i < n; i++) {
		bitAdjacencyMatrix[i] = new unsigned char[size];
	}

	//Initialize the bit Adjacency Matrix structure
	for (int i = 0; i < n; i++)
		for (int j = 0; j < size; j++)
			bitAdjacencyMatrix[i][j] = 0x00 << 8;

}

// Non Empty constructor
BitMatrixGraph::BitMatrixGraph(int numNodes)
{

	n = numNodes;

	if (n % 8 == 0)               // Determines number of unsigned char in each row
		size = n / 8;
	else
		size = (int)(n / 8) + 1;


	// Initilizing the array of char arrays
	bitAdjacencyMatrix = new unsigned char*[n];
	for (int i = 0; i < n; i++) {
		bitAdjacencyMatrix[i] = new unsigned char[size];
	}

	//Initialize the bit Adjacency Matrix structure with zeros
	for (int i = 0; i < n; i++)
		for (int j = 0; j < size; j++)
			bitAdjacencyMatrix[i][j] = 0x00 << 8;

}

// Copy constructor
BitMatrixGraph::BitMatrixGraph(BitMatrixGraph& otherGraph)
{
	copy(otherGraph);
}

// Copy method
 void BitMatrixGraph::copy(BitMatrixGraph& b)
{
	 // Deleting the data currently present in the graph
	 for (int i = 0; i < n; i++)
		 delete	bitAdjacencyMatrix[i];

	 delete bitAdjacencyMatrix;

	 // Determining number of blocks in each row
	 n = b.getNumNodes();
	 if (n % 8 == 0)
		 size = n / 8;
	 else
		 size = (int)(n / 8) + 1;

	 // Defining bitAdjacency matrix with new size

	 bitAdjacencyMatrix = new unsigned char*[n];
	 for (int i = 0; i < n; i++) {
		 bitAdjacencyMatrix[i] = new unsigned char[size];
	 }

	 //Initialize the bit Adjacency Matrix structure
	 for (int i = 0; i < n; i++)
		 for (int j = 0; j < size; j++)
			 bitAdjacencyMatrix[i][j] = 0x00 << 8;


	 //Copy the edges in other graph
	 for (int i = 0; i < n; i++)
		 for (int j = 0; j < n; j++)
			 if (b.isAnEdge(i, j))
			 {
				 addEdge(i, j);
				 addEdge(j, i);
			 }


}

 // Destructor
BitMatrixGraph::~BitMatrixGraph()
{
	
	for (int i = 0; i < n; i++)
			delete	bitAdjacencyMatrix[i];  // deletes each row in bitAdjacencyMatrix

	delete bitAdjacencyMatrix;  // deletes row containing pointers

	bitAdjacencyMatrix = NULL;

}

// Overloaded = operator
void BitMatrixGraph::operator=(BitMatrixGraph& b)
{

	copy(b);
}

// Method to get number of nodes
int BitMatrixGraph::getNumNodes()
{
	return n;
}

// Overloaded ostream operator
 ostream& operator << (ostream& s, BitMatrixGraph& b)
{
	int n = b.getNumNodes();
	 int totalEdges = 0;		// Counts edges
	cout << "**********Graph Representation Using Adjacency List**********\n" << endl;
	for (int i = 0; i < n; i++)	// Runs over all edges
	{
		cout << i << "------>";
		for (int j = 0; j < n; j++)	// Runs over all edges
		{
			if (b.isAnEdge(i, j))     // Checks if an edge exists between node i and j
			{ 
				cout << j << " "; 
				totalEdges++;
			}
			
		//	else { cout << "0 "; }
		}
		cout << "   " << endl;
	}
	cout << " Total Edges in the graph: " << totalEdges/2 << endl;
	return s;
}

 // Print function will print graph in adjacency Matrix format
void BitMatrixGraph::print()
{

	cout << "********** Graph Representaion using Adjacency Matrix **********\n" << endl;

	for (int i = 0; i < n; i++)   // Runs over each row
	{
		for (int j = 0; j < size; j++)  // Runs over each block in row
		{
			printBits(bitAdjacencyMatrix[i][j]);     // Prints unsigned char as bits
		}
		cout << "   " << endl;
	}
}

 // Method to print bits in an unsigned character
void BitMatrixGraph::printBits(unsigned char s) {

	//print the bit pattern
	for (int i = 0; i < 8; i++)
	{
		if (s & (1 << (7 - i)))
			cout << 1 << " ";
		else
			cout << 0 << " ";
	}
}

// Method ot add an edge to the graph
void BitMatrixGraph::addEdge(int u, int v)
{
	int block;
	block = int( floor(v / 8));   // Block of v

	int index = v - (block * 8) ;	// Idex of v in its block

	bitAdjacencyMatrix[u ][block] |= 0x01 << (8-index-1);   // Setting the corresponding bit = 1
	
	swap(u, v);    // Adding edge representing v --> u

	block = int(floor(v / 8));

	 index = v - (block * 8);

	bitAdjacencyMatrix[u][block] |= 0x01 << (8 - index - 1);

}

// Method to check if there is an edge between two vertices
bool BitMatrixGraph::isAnEdge(int u, int v)
{

	int block;		// block containing v

	block = int(floor(v / 8));

	int index = v - (block * 8); // index ot v in its block

	if (bitAdjacencyMatrix[u][block] & (1 << (8 - index - 1))) { return true; } // Check if the index is one
	else { return false; }

}


void BFS(BitMatrixGraph& Bmg, int start)
{

	int n = Bmg.getNumNodes();    // Number of nodes in the graph
	int curr = -1;							  // Current node
	int* parent = new int[n];			  // Parent node for each node


	// Visited initialized to false 
	bool *visited = new bool[n];
	for (int i = 0; i < n; i++) { visited[i] = false; }

	visited[start] = true;

	// Queue containing next nodes
	queue<int> nextNodes;
	nextNodes.push(start);
	parent[start] = curr;

	// Iterative form of breadth first search
	while (!nextNodes.empty())
	{
		curr = nextNodes.front();  // New node is popped
		nextNodes.pop();

		for (int i = 0; i < n; i++)     // Iterating over all nodes
		{

			if (Bmg.isAnEdge(curr, i))		// Neighbours of the current node
			{
				if (!visited[i])
				{
					nextNodes.push(i);      
					parent[i] = curr;
					visited[i] = true;

				}

			}

		}

	}

	// Printing parent of each node in Breadth first search
	cout << "********** Breadth First Search *********\n" << endl;
	cout << "Node ---> Parent Node" << endl;
	for (int i = 0; i < n; i++)
	{
		cout <<"    "<< i << "--->" << parent[i] << endl;
	}
	cout << "" << endl;
	

}

void DFS(BitMatrixGraph& Bmg, int start)
{

	int n = Bmg.getNumNodes();    // Number of nodes in the graph
	int curr = -1;							  // Current node
	int* parent = new int[n];			  // Parent node for each node


										  // Visited initialized to false 
	bool *visited = new bool[n];
	for (int i = 0; i < n; i++) { visited[i] = false; }

	visited[start] = true;

	// Queue containing next nodes
	stack<int> nextNodes;
	nextNodes.push(start);
	parent[start] = curr;

	// Iterative form of breadth first search
	while (!nextNodes.empty())
	{
		curr = nextNodes.top();  // New node is popped
		nextNodes.pop();

		for (int i = 0; i < n; i++)     // Iterating over all nodes
		{

			if (Bmg.isAnEdge(curr, i))		// Neighbours of the current node
			{
				if (!visited[i])
				{
					nextNodes.push(i);
					parent[i] = curr;
					visited[i] = true;

				}

			}

		}

	}

	// Printing parent of each node in Breadth first search
	cout << "********* Depth First Search **********\n" << endl;
	cout << "Node ---> Parent Node" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "    " << i << "--->" << parent[i] << endl;
	}
	cout << "" << endl;


}

int main() {

	cout << "Gowtham Talluru Project 3\n\n" << endl;

	// Temperory parameters to read input
	int n;
	int a;
	int b;

	
	// Number of nodes in the graph
	cin >> n;
	cout << "Number of Nodes: "<< n<<"\n"<<endl;
	
	// Graph object
	BitMatrixGraph GraphObject(n);

	// Reading input and printing the lines
	cout << "EdgeList" << endl;
	while (!cin.eof())
	{

			cin >> a;
			cin >> b;
			GraphObject.addEdge(a, b);
			cout << a << "   " << b << endl;
	}
	cout << endl;

	// Prints graph in Adjacency list format
	cout << GraphObject << "\n"<<endl;
	
	// Prints graph in Adjacency Matrix format
	GraphObject.print();
	cout << "\n" << endl;
	
	// New object to illustrate = operator
	BitMatrixGraph GraphObject2;
	
	GraphObject2 = GraphObject;

	// Breadth First Search
	BFS(GraphObject, 0);

	// Depth First Search
	DFS(GraphObject, 0);


	getchar();

	//Final Code

	return 0;

}


