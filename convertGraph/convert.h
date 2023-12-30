#ifndef _CONVERT_GRAPH_
#define _CONVERT_GRAPH_
#include<iostream>
#include<vector>
#include<utility>
#include<unordered_map>
#include<set>
using namespace std;

// convert to adj matrix
void ToAdjMatrix(vector<vector<int>>& adjMatrix, vector<vector<int>> rawInput, int size);
void ToIncMatrix(vector<vector<int>>& incMatrix, vector<vector<int>> rawInput, int sizeRow, int sizeCol);
void ToAdjList(unordered_map<int, vector<int>>& adjList, vector<vector<int>> rawInput);
#endif