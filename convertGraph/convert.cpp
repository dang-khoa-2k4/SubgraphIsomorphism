#include "convert.h"

void ToAdjMatrix(vector<vector<int>>& adjMatrix, vector<vector<int>> rawInput, int size)
{
    for (int i = 0; i < size; i++)
    {
        adjMatrix.push_back(vector<int> (size, 0));
    }
    cout << "initial adj matrix done\n";
    for (int i = 0; i < rawInput.size(); i++)
    {
        adjMatrix[rawInput[i][0] - 1][rawInput[i][1] - 1] = 1;
    }
}

void ToIncMatrix(vector<vector<int>>& incMatrix, vector<vector<int>> rawInput, int sizeRow, int sizeCol)
{
    for (int i = 0; i < sizeRow; i++)
    {
        incMatrix.push_back(vector<int> (sizeCol, 0));
    }
    cout << "initial inc matrix done\n";
    for (int i = 0; i < rawInput.size(); i++)
    {
        incMatrix[rawInput[i][0] - 1][rawInput[i][1] - 1] = 1;
    }
}

void ToAdjList(unordered_map<int, vector<int>>& adjList, vector<vector<int>> rawInput)
{
    for (auto edge : rawInput)
    {
        adjList[edge[0]].push_back(edge[1]);
        // adjList[edge[1]].insert(edge[0]);
    }
}
