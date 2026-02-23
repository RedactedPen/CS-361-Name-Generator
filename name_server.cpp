#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <cstdlib>

//load data into vectors
std::vector<std::string> sci_fi_first_name;
std::vector<std::string> sci_fi_last_name;
std::vector<std::string> fantasy_first_name;
std::vector<std::string> fantasy_last_name;
std::vector<std::string> modern_first_name;
std::vector<std::string> modern_last_name;

void load_data(){
    std::ifstream file("fantasy_first_name.txt");
    if(!file){
        std::cerr << "Could not open file" << std::endl;
    }
    std::string name1;

    while(std::getline(file, name1)){
        fantasy_first_name.push_back(name1);
    }
    file.close();

    std::ifstream file2("fantasy_last_name.txt");
    
    std::string fl_name; 
    while(std::getline(file2, fl_name)){
        fantasy_last_name.push_back(fl_name);
    }
    file2.close();

    std::ifstream file3("modern_first_name.txt");
    std::string mf_name; 
    while(std::getline(file3, mf_name)){
        modern_first_name.push_back(mf_name);
    }
    file3.close();

    std::ifstream file4("modern_last_name.txt");
    
    std::string ml_name; 
    while(std::getline(file4, ml_name)){
        modern_last_name.push_back(ml_name);
    }
    file4.close();

    std::ifstream file5("sci_fi_first_name.txt");
    
    std::string sf_name; 
    while(std::getline(file5, sf_name)){
        sci_fi_first_name.push_back(sf_name);
    }
    file5.close();

    std::ifstream file6("sci_fi_last_name.txt");
    std::string sl_name; 
    while(std::getline(file6, sl_name)){
        sci_fi_last_name.push_back(sl_name);
    }
    file6.close();
}
int main(){
    load_data();
    //while(True)
        //if theme == fantasy
            //if first_name

    int num = rand() % 201;

    std::string name = sci_fi_first_name[num];
    std::cout << name << std::endl;
}



            

