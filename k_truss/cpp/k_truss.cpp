#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <set>
using namespace std;

// Struct biểu diễn một cạnh trong đồ thị
struct Edge {
    int u, v, w;
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
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
            if (u != edge.v && find(adjList[edge.v].begin(), adjList[edge.v].end(), u) != adjList[edge.v].end()) {
                count++;
                if (count >= k - 2)
                    return true;
            }
        }
        return false;
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
    set<vector<int>> edgest;
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        int u, v, w;
        while (inputFile >> u >> v >> w) {
            if (edgest.insert({ max(u, v), min(u, v) }).second) {
                edges.push_back({ u, v , w });
            }
        }
        
        inputFile.close();
    }
    return edges;
}

void writeGraphToFile(const vector<Edge>& kTrussEdges, const string& filename) {
    ofstream outputFile(filename);
    if (outputFile.is_open()) {
        for (const Edge& edge : kTrussEdges) {
            outputFile << edge.u << " " << edge.v << " " << edge.w << endl;
        }
        outputFile.close();
        cout << "Ket qua da duoc ghi vao file " << filename << endl;
    }
    else {
        cout << "Khong the mo file " << filename << " de ghi ket qua." << endl;
    }
}
int main() {
    auto start = std::chrono::high_resolution_clock::now();
    // Đồ thị mẫu
    vector<Edge> edges = readGraphFromFile("graph_data.txt");
    cout << "So canh la: "<< edges.size() << endl;
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1 = end1 - start;
    double executionTime1 = duration1.count();
    std::cout << "Thoi gian doc du lieu: " << executionTime1 << " giay" << std::endl;

    int k = 6; // Giá trị k-Truss cần tìm
    vector<Edge> edges1 = findKTruss(edges, k); 
    vector<Edge> edges2 = findKTruss(edges1, k); 
    while (edges1.size() != edges2.size()) {
        edges1 = edges2;
        edges2 = findKTruss(edges1, k);
    }
    // In kết quả
cout << "k-Truss Edges:" << endl;
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration2 = end2 - end1;
    double executionTime2 = duration2.count();
    std::cout << "Thoi gian thuc hien ktruss: " << executionTime2 << " giay" << std::endl;

    writeGraphToFile(edges2, "output.txt");
    auto end3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration3 = end3 - end2;
    double executionTime3 = duration3.count();
    std::cout << "Thoi gian ghi file: " << executionTime3 << " giay" << std::endl;

    return 0;
}