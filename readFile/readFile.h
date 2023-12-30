#ifndef _READ_FILE_
#define _READ_FILE_
#include<iostream>
#include<vector>
#include "..\convertGraph\convert.h"
#include<fstream>
#include<string>
#include<unordered_map>
#include<set>

struct Edge
{
    int u, v;
    Edge(int u, int v) : u(u), v(v) {};
};

class readFile
{
    private:
        vector<vector<int>> adjMatrix;
        vector<vector<int>> incMatrix;
        unordered_map<int , vector<int>> adjList; 
        set<vector<int>> edgeList; 
        int numOfVertex;
        int numOfEdge;
    public:

        readFile();

        vector<vector<int>> getAdjMatrix() {
            return this->adjMatrix;  
        };

        vector<vector<int>> getIncMatrix() {
            return this->incMatrix;  
        };
        
        unordered_map<int, vector<int>> getAdjList() {
            return this->adjList;
        };

        set<vector<int>> getEdgeList() {
            return this->edgeList;
        };
        
        int getNumOfEdge () {
            return this->numOfEdge;
        }
        
        int getNumOfVertex () {
            return this->numOfVertex;
        }

        void readAndConvert(const char *adjFile, const char *incFile);
        void readToAdjList(const char *adjFile);

        void print(vector<vector<int>> C)
        {
            for (int i = 0; i < C.size(); i++) {
                for (int j = 0; j < C[0].size(); j++) {
                    cout << C[i][j] << " ";
                }
                cout << endl;
            }
        }
        
        void printList(unordered_map<int, vector<int>> C)
        {
            for (auto vertex : C)
            {
                cout << vertex.first << " : ";
                for (auto i : vertex.second)
                {
                    cout << i << " ";
                }
                cout << endl;
            }
        }

    
};

#endif 