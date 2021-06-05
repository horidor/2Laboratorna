#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;


int main()
{
    int n, i;
    n = 1;
    std::string directory_name = "C:/Users/topkek/source/repos/Laboratory2OP/2Laboratorna/tables";
    std::string ext = ".csv";
    std::vector<std::string> files;
    
    for (auto& entry : fs::directory_iterator(directory_name))
    {
        if (entry.path().extension() == ".csv")
        {
            files.push_back(entry.path().generic_string());
        }
    }

        
}
