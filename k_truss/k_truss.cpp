#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <fstream>
using namespace std;

// Struct biểu diễn một cạnh trong đồ thị
struct Edge {
    int u, v;
    Edge(int u, int v) : u(u), v(v) {}
};

// Hàm tìm k-Truss của đồ thị
vector<Edge> findKTruss(const vector<Edge>& edges, int k) {
    // Tạo danh sách kết nối của mỗi đỉnh
    unordered_map<int, vector<int>> adjList;
    for (const Edge& edge : edges) {
        adjList[edge.u].push_back(edge.v);
        adjList[edge.v].push_back(edge.u);
    }

    // Hàm kiểm tra xem một cạnh có thuộc k-Truss hay không
    auto isKTrussEdge = [&](const Edge& edge) {
        int count = 0;
        for (int u : adjList[edge.u]) {
            if (u != edge.v && find(adjList[edge.v].begin(), adjList[edge.v].end(), u) != adjList[edge.v].end()) 
            {
                count++;
                
            }
        }
        if (count >= k - 2)
            return true;
        else return false;
    };

    // Tạo danh sách kết quả
    vector<Edge> kTrussEdges;

    // Lặp qua các cạnh và kiểm tra
    for (const Edge& edge : edges) {
        if (isKTrussEdge(edge))
            kTrussEdges.push_back(edge);
    }

    return kTrussEdges;
}
vector<Edge> readGraphFromFile(const string& filename) {
    vector<Edge> edges;
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        int u, v, t;
        while (inputFile >> u >> v >> t) {
            edges.push_back({ u, v });
        }
        inputFile.close();
    }
    return edges;
}

void writeGraphToFile(const vector<Edge>& kTrussEdges, const string& filename) {
    ofstream outputFile(filename);
    if (outputFile.is_open()) {
        for (const Edge& edge : kTrussEdges) {
            outputFile << edge.u << " " << edge.v << endl;
        }
        outputFile.close();
        cout << "Ket qua da duoc ghi vao file " << filename << endl;
    }
    else {
        cout << "Khong the mo file " << filename << " de ghi ket qua." << endl;
    }
}
int main() {
    // Đồ thị mẫu
    vector<Edge> edges = readGraphFromFile("graph_data.txt");

    int k = 4; // Giá trị k-Truss cần tìm

    // Tìm k-Truss của đồ thị
    vector<Edge> kTrussEdges = findKTruss(edges, k);

    // In kết quả
    cout << "k-Truss Edges:" << endl;
    writeGraphToFile(kTrussEdges, "output.txt");

    return 0;
}