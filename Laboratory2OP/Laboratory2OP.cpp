#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

std::string* read_files(std::vector<std::string> files, int*);



int main()
{
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

    int n=0;
    std::string* L = read_files(files, &n);
    for (int i = 0; i < n; i++)
    {
        std::cout << L[i] << std::endl;
    }
        
}

std::string* read_files(std::vector<std::string> files, int* n)
{
    std::string temp;
    std::string* DATA = nullptr;
    for (int i = 0; i < files.size(); i++)
    {
        std::fstream outf(files[i]);
        getline(outf, temp);
        *n += stoi(temp);
    }
    DATA = new std::string[*n];
    int k = 0 , j = 0;
    for (int i = 0; i < files.size(); i++)
    {
        std::fstream outf(files[i]);
        getline(outf, temp);
        k += stoi(temp);
        while (j < k)
        {
            getline(outf, DATA[j]);
            j++;
        }
    }
    return DATA;
}
