#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>

//load data into vectors
std::ifstream file("fantasy_first_name.txt");
std::vector<std::string> fantasy_first_name;
std::string name; 
while (std::getline(file, name)){
    fantasy_first_name.push_back(name);
}
file.close();

std::ifstream file("fantasy_last_name.txt");
std::vector<std::string> fantasy_last_name;
std::string fl_name; 
while (std::getline(file, fl_name)){
    fantasy_last_name.push_back(fl_name);
}
file.close();

std::ifstream file("modern_first_name.txt");
std::vector<std::string> modern_first_name;
std::string mf_name; 
while (std::getline(file, mf_name)){
    modern_first_name.push_back(mf_name);
}
file.close();

std::ifstream file("modern_last_name.txt");
std::vector<std::string> modern_last_name;
std::string ml_name; 
while (std::getline(file, ml_name)){
    modern_last_name.push_back(ml_name);
}
file.close();

std::ifstream file("sci_fi_first_name.txt");
std::vector<std::string> sci_fi_first_name;
std::string sf_name; 
while (std::getline(file, sf_name)){
    sci_fi_first_name.push_back(sf_name);
}
file.close();

std::ifstream file("sci_fi_last_name.txt");
std::vector<std::string> sci_fi_last_name;
std::string sl_name; 
while (std::getline(file, sl_name)){
    modern_last_name.push_back(sl_name);
}
file.close();

//while(True)
    //if theme == fantasy
        //if first_name
            

