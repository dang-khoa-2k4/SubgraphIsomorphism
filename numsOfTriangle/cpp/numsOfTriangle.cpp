/*   File này là tổng hợp các thuật toán để tính số tam giác trong đồ thị. 
 *   Thuật toán chính được nêu trong báo cáo là hàm 
 *   int numsOfTriangle3(unordered_map<int, vector<int>> adjList, set<vector<int>> edgeList, const char * outFile, vector<int>& triangleOfVertex)
 */
#include<algorithm>
#include<iostream>
#include<fstream>
#include <chrono>
#include<vector>
#include<cmath>
#include "..\readFile\readFile.h"
#include "..\convertGraph\convert.h"
using namespace std;

#define ROW_SHIFT 1
#define COL_SHIFT 0

void multiMatrix(vector<vector<int>>& ans, vector<vector<int>> matrix1, vector<vector<int>> matrix2)
{   
    if (matrix1[0].size() != matrix2.size())
    {
        // cout << "Error, Can't mutli 2 matrix\n";
        return;
    }
    // cout << "multi 2 matrix...\n";
    for (int i = 0; i < matrix1.size(); i++)
    {
        for (int j = 0; j < matrix2[0].size(); j++)
        {
            ans[i][j] = 0;
            for (int k = 0; k < matrix1.size(); k++)
            {
                ans[i][j] += matrix1[i][k] * matrix2[k][j]; 
            }
        }
        // cout << "done " << i + 1 << "/" << matrix1.size() << endl;
    }
}

void print(vector<vector<int>> C)
{
    for (int i = 0; i < C.size(); i++) {
        for (int j = 0; j < C[0].size(); j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }
}

void shift(vector<vector<int>>& A, bool direction, bool firstStep)
{
    int size = A.size();
    int step;
    vector<int> temp(size, 0);
    if (direction)
    {
        if (firstStep) step = 0;
        else step = 1;
        for (int k = 0; k < size; k++)
        {
            int index = 0;
            for (int i = step; i < size; i++)
            {
                temp[index++] = A[k][i];
            }
            for (int i = 0; i < step; i++)
            {
                temp[index++] = A[k][i];
            }
            for (int i = 0; i < size; i++)
            {
                A[k][i] =  temp[i];
            }
            if (firstStep) step++;
        }
    }
    else 
    {
        if (firstStep) step = 0;
        else step = 1;
        for (int k = 0; k < size; k++)
        {
            int index = 0;
            for (int i = step; i < size; i++)
            {
                temp[index++] = A[i][k];
            }
            for (int i = 0; i < step; i++)
            {
                temp[index++] = A[i][k];
            }
            for (int i = 0; i < size; i++)
            {
                A[i][k] = temp[i];
            }
            if (firstStep) step++;
        }
    }
}


int countTriangles(const std::vector<std::vector<int>>& adjacencyMatrix, const std::vector<std::vector<int>>& incidenceMatrix)
{
    int numVertices = adjacencyMatrix.size();
    int numTriangles = 0;

    // Iterate over all possible triplets of vertices
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = i + 1; j < numVertices; j++)
        {
            for (int k = j + 1; k < numVertices; k++)
            {
                // Check if the triplet forms a triangle
                if (adjacencyMatrix[i][j] && adjacencyMatrix[j][k] && adjacencyMatrix[k][i])
                {
                    // Check if the edges of the triangle exist in the incidence matrix
                    int edge1 = -1, edge2 = -1, edge3 = -1;

                    for (int e = 0; e < incidenceMatrix[i].size(); e++)
                    {
                        if (incidenceMatrix[i][e] && incidenceMatrix[j][e])
                        {
                            edge1 = e;
                            break;
                        }
                    }

                    for (int e = 0; e < incidenceMatrix[j].size(); e++)
                    {
                        if (incidenceMatrix[j][e] && incidenceMatrix[k][e])
                        {
                            edge2 = e;
                            break;
                        }
                    }

                    for (int e = 0; e < incidenceMatrix[k].size(); e++)
                    {
                        if (incidenceMatrix[k][e] && incidenceMatrix[i][e])
                        {
                            edge3 = e;
                            break;
                        }
                    }

                    // If all three edges are found, increment the triangle count
                    if (edge1 != -1 && edge2 != -1 && edge3 != -1)
                    {
                        numTriangles++;
                    }
                }
            }
        }
        cout << "Done " << i + 1 << "/" << numVertices << endl;
    }

    return numTriangles;
}

// Hàm thực hiện thuật toán Cannon nhân 2 ma trận độ phức tạp thấp hơn :vv
vector<vector<int>> cannonMatrixMultiply(vector<vector<int>> A, vector<vector<int>> B) {
    int n = A.size(); // nums of row = col
    int p = sqrt(n*n); // nums of step
    vector<vector<int>> ans(n, vector<int>(n, 0));
    // first step
    bool firstStep = true;
    while (p)
    {
        shift(A, ROW_SHIFT, firstStep);
        shift(B, COL_SHIFT, firstStep);
        firstStep = false;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                ans[i][j] += A[i][j] * B[i][j];
            }
        }
        cout << "Done " << p << "/" << n << endl;
        p--;
    }
    return ans;
}

int traceOfMatrix(vector<vector<int>> adjMatrix)
{
    int trace = 0;
    for (int i = 0; i < adjMatrix.size(); i++)
    {
        trace += adjMatrix[i][i];
    }
    return trace;
}

int numsOfTriangle1(vector<vector<int>> adjMatrix)
{
    vector<vector<int>> temp1 = adjMatrix;
    vector<vector<int>> temp2 = adjMatrix;

    temp1 = cannonMatrixMultiply(adjMatrix, adjMatrix);

    int num = 0;
    for (int i = 0; i < adjMatrix.size(); i++)
    {
        for (int j = 0; j < adjMatrix.size(); j++)
        {
            num += temp1[i][j] * adjMatrix[i][j]; 
        }
    }
    return num / 6;

    // Different ways
    /*
    temp1 = cannonMatrixMultiply(adjMatrix, adjMatrix);
    temp2 = cannonMatrixMultiply(temp1, adjMatrix);
    return traceOfMatrix(temp2) / 6;
    */

}

int numsOfTriangle2(vector<vector<int>> adjMatrix, vector<vector<int>> incMatrix)
{
    
    vector<vector<int>> temp (adjMatrix.size(), vector<int> (incMatrix[0].size(), 0));
    multiMatrix(temp, adjMatrix, incMatrix);

    // print(temp);

    int count = 0;
    for (int i = 0; i < temp.size(); i++)
    {
        for (int j = 0; j < temp[0].size(); j++)
        {
            if (temp[i][j] == 2)
            {
                count++;
            }
        }
    }
    return count / 3;

}

// chính là hàm này
int numsOfTriangle3(unordered_map<int, vector<int>> adjList, set<vector<int>> edgeList, const char * outFile, vector<int>& triangleOfVertex)
{   
    ofstream output(outFile);
    int count = 0;
    set<vector<int>> triangleList;
    auto countingTriangle = [&](int &u, int &v)
    {
        for (int w : adjList[u])
        {
            if (w != v && find(adjList[v].begin(), adjList[v].end(), w) != adjList[v].end())
            {
                vector<int> a = {u , v , w};
                sort(a.begin(), a.end());
                if (triangleList.insert(a).second)
                {
                    ++count;
                    // // counting triangle of each vertex
                    // triangleOfVertex[u]++;
                    // triangleOfVertex[v]++;
                    // triangleOfVertex[w]++;
                    // output << u << " " << v << " " << "1" << endl;
                    // output << v << " " << w << " " << "1" << endl;
                    // output << u << " " << w << " " << "1" << endl;
                }
            }
            // cout << u << " " << v << " " << w << endl;
        }
        return;
    };
    
    for (auto edge : edgeList)
    {
        countingTriangle(edge[0], edge[1]);
        // cout << edge[0] << " " << edge[1] << endl;
    }
    output.close();
    return count;
}


main()
{    
    const char *file1 = "roadNet-TX_adj.tsv";
    const char *file2 = "as20000102_inc.tsv";

    readFile input;
    // input.readAndConvert(file1, file2);
    input.readToAdjList(file1);
    vector<int> triangleOfVertex((int)(input.getNumOfVertex() + 1), 0);
    cout << "num of ver: " << input.getNumOfVertex() << endl;
    cout << "num of edge: " << input.getNumOfEdge() << endl;

    auto start = std::chrono::high_resolution_clock::now();
    cout << "Number of triangle is :" << numsOfTriangle3(input.getAdjList(), input.getEdgeList(), "output.txt", triangleOfVertex) << endl;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    double executionTime = duration.count();
    std::cout << "Processing Time: " << executionTime << " s" << std::endl;
    
    ofstream out("triangle of each vertex.txt");
    out << "Triangle number of each internal vertex in " << file1 << " file : " << endl;
    for (int i = 1; i <= input.getNumOfVertex(); i++)
    {
        out << "Vertex " << i << " has " << triangleOfVertex[i] << " triangles" << endl;
    }
    out.close();


    // input.printList(input.getAdjList());
    // print(input.getAdjMatrix());
    // print(input.getIncMatrix());
    // m = adjMatrix.size();
    // cout << "Nums of triangle is " << numsOfTriangle1(input.getAdjMatrix()) << endl;
    // cout << "Nums of triangle is " << numsOfTriangle2(input.getAdjMatrix(), input.getIncMatrix()) << endl;
    // cout << "Nums of triangle is " << countTriangles(input.getAdjMatrix(), input.getIncMatrix()) << endl;
}