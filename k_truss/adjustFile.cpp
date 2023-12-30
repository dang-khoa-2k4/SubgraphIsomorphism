#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>  //Thêm thư viện này để sử dụng hàm std::remove

int main() {
    std::ifstream inputFile("file.txt");  // Thay đổi "input.txt" thành tên tệp tin đầu vào của bạn
    std::ofstream outputFile("..\\output\\ktruss_out.txt");  // Thay đổi "output.txt" thành tên tệp tin đầu ra của bạn

    if (inputFile.is_open() && outputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            // Xóa khoảng trắng thừa từ đầu và cuối dòng
            line.erase(0, line.find_first_not_of(" \t"));
            line.erase(line.find_last_not_of(" \t") + 1);

            // Nếu dòng không rỗng
            if (!line.empty()) {
                // Xóa các ký tự không cần thiết trong dòng
                line.erase(std::remove(line.begin(), line.end(), '('), line.end());
                line.erase(std::remove(line.begin(), line.end(), ')'), line.end());
                std::replace(line.begin(), line.end(), ',', ' ');
                // Sử dụng stringstream để tách chuỗi thành các phần tử
                std::stringstream ss(line);
                std::string x, y, z;
                ss >> x >> y >> z;
                if (stoi(z) != 1) continue;
                // Ghi dữ liệu vào tệp tin đầu ra
                outputFile << x << " " << y << " " << z << std::endl;
            }
        }

        // Đóng tệp tin
        inputFile.close();
        outputFile.close();

        std::cout << "Chuyen doi da hoan tat." << std::endl;
    } else {
        std::cout << "Khong mo duoc tep tin dau vao hoac dau ra." << std::endl;
    }

    return 0;
}