#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

std::string* read_files(std::vector<std::string> files, int*);
std::string* get_results(std::string*, int*);
int match_result(int, int);


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
    std::string* DATA = read_files(files, &n);
    std::string* RESULTS = get_results(DATA, &n);
    for (int i = 0; i < n; i++)
    {
        std::cout << RESULTS[i] << std::endl;
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

std::string* get_results(std::string* DATA, int* n)
{
    std::string* RESULTS = new std::string[*n];
    std::string temp1, temp2;
    int j;
    int k;
    int result;
    for (int i = 0; i < *n; i++)
    {
        j = 0;
        k = 0;
        result = 0;
        j = DATA[i].find(',', j);
        RESULTS[i] += DATA[i].substr(0, j);
        k = j;
        DATA[i] += ',';
        while (DATA[i].find(',',j+1) != -1)
        {
            j = DATA[i].find(',', j+1);
            k++;
            while (DATA[i][k] != ':')
            {
                temp1 += DATA[i][k];
                k++;
            }
            k++;
            while (k < j)
            {
                temp2 += DATA[i][k];
                k++;
            }
            result += match_result(stoi(temp1), stoi(temp2));
            temp1 = "";
            temp2 = "";
        }
        RESULTS[i] += ',' + std::to_string(result);
        DATA[i].erase(DATA[i].length() - 1);
    }
    return RESULTS;
}

int match_result(int a, int b)
{
    if (a > b)
    {
        return 3;
    }
    else if (a == b)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

