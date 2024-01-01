#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(int argc, char* argv[]) 
{
    string infile = argv[1];
    std::string file_path = "..\\data\\" + infile;
    std::ifstream file(file_path);  // Mở file để đọc

    if (file.is_open()) {
        // std::string line;
        std::ofstream output_file("..\\output\\ktruss_input.txt"); // File kết quả
        int x, y, z;
        while (file >> x >> y >> z) {  // Đọc từng dòng trong file
            // line += " 1";  // Thêm số 1 vào cuối dòng
            output_file << y << " " << x << " "<< z << std::endl;  // Ghi dòng đã được chỉnh sửa vào file kết quả
        }
        output_file.close();  // Đóng file kết quả
        file.close();  // Đóng file đầu vào
        std::cout << "Thêm số 1 thành công!" << std::endl;
    } else {
        std::cout << "Không thể mở file!" << std::endl;
    }
    return 0;
}