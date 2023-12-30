#include "readFile.h"

readFile::readFile()
{
    this->adjMatrix = {{0}};
    this->incMatrix = {{0}};
    this->numOfEdge = 0;
    this->numOfVertex = 0;
}


void readFile::readAndConvert(const char *adjFile, const char *incFile)
{
    ifstream input1(adjFile);
    ifstream input2(incFile);
    
    if (!input1.is_open())
    {
        cout << "Error, can't read " << adjFile << ", check again!";
        return;
    }
    
    if (!input2.is_open())
    {
        cout << "Error, can't read " << incFile << ", check again!";
        return;
    }

    vector<vector<int>> rawInput;
    int maxRow = -1e9;
    int maxCol = -1e9;
    int temp;

    //read adj matrix file
    while (input1 >> temp)
    {
        int vertex1;
        int vertex2;
        vertex1 = temp;
        input1 >> vertex2;
        
        maxRow = max(maxRow, max(vertex1, vertex2));

        vector<int> temp = {vertex1, vertex2};
        rawInput.push_back(temp);
        input1 >> vertex2; // remove 1 element
    }

    cout << "read file 1 done\n"; 
    ToAdjMatrix(this->adjMatrix, rawInput, maxRow);
    cout << "cnovert adj matrix done\n";
    
    numOfEdge = rawInput.size() / 2;
    numOfVertex = maxRow;
    maxRow = -1e9;
    rawInput.clear();

    //read inc matrix file
    while (input2 >> temp)
    {
        int vertex;
        int edge;
        vertex = temp;
        input2 >> edge;
        
        maxRow = max(maxRow, vertex);
        maxCol = max(maxRow, edge);

        vector<int> temp = {vertex, edge};
        rawInput.push_back(temp);
        input2 >> edge; // remove 1 element
    }
    

    cout << "read file 1 done\n"; 
    ToIncMatrix(this->incMatrix, rawInput, maxRow, maxCol);
    cout << "cnovert inc matrix done\n";
    
    rawInput.clear();
    // close file
    input1.close();
    input2.close();

}

void readFile::readToAdjList(const char *adjFile)
{
    ifstream input(adjFile);
    
    if (!input.is_open())
    {
        cout << "Error, can't read " << adjFile << ", check again!";
        return;
    }

    int u , v, t;

    if (numOfEdge != 0) numOfEdge = 0;
    while (input >> u >> v >> t)
    {
        if(edgeList.insert({max(u, v), min(u, v)}).second)
        {
            adjList[min(u, v)].push_back(max(u, v));
        }
        numOfVertex = max(numOfVertex, u);
        numOfEdge++;
    }
    numOfEdge /= 2;
    
    input.close();
}