#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

std::string output_file = "results.csv";

namespace fs = std::filesystem;

std::vector<std::string> get_info_into_files(std::string, std::string);
std::string* read_files(std::vector<std::string> files, int*);
std::string* get_results(std::string*, int*);
int match_result(int, int);
void output_results(std::string*, int*, std::string);


int main()
{
    std::string directory_name;
    std::string ext = ".csv";
    std::vector<std::string> files;
    int n = 0;

    std::cout << "Input the directory path: "; std::cin >> directory_name;
    if (!fs::is_directory(directory_name))
    {
        std::cout << "Directory does not exist.";
        return 0;
    }
    files = get_info_into_files(directory_name, ext);
    if (files.empty())
    {
        std::cerr << "Directory does not contain .scv files. " << std::endl;
        return 0;
    }
    
    std::string* DATA = read_files(files, &n);
    std::string* RESULTS = get_results(DATA, &n);

    output_results(RESULTS, &n, directory_name);    
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

void output_results(std::string* RESULTS, int* n, std::string directory_name)
{
    std::ofstream outf(directory_name+'/'+output_file);
    for (int i = 0; i < *n; i++)
    {
        outf << RESULTS[i] << std::endl;
    }
}

std::vector<std::string> get_info_into_files(std::string DIRECTORY, std::string ext)
{
    std::vector<std::string> files;
    for (auto& entry : fs::directory_iterator(DIRECTORY))
    {
        if ((entry.path().extension() == ext) and ((entry.path().filename().generic_string()) != output_file ))
        {
            files.push_back(entry.path().generic_string());
        }
    }
    return files;
}

