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
    std::string name = " ";
    std::string last_name = " ";
    //while(True){}
        //if theme == fantasy, first name 
            int num = rand() % 200;
            name = fantasy_first_name[num];   

        //if theme == sci_fi, first name 
            int num = rand() % 200;
            name = sci_fi_first_name[num];

        //if theme == modern, first name 
            int num = rand() % 200;
            name = modern_first_name[num];

        //if theme == fantasy, last name 
            num = rand() % 200;
            last_name = fantasy_last_name[num];   

        //if theme == sci_fi, last name 
            int num = rand() % 200;
            last_name = sci_fi_last_name[num];

        //if theme == modern, last name 
            int num = rand() % 200;
            last_name = modern_last_name[num];

        //if name != " " && last_name != " "
            std::string full_name = name + " " + last_name;
            //return full_name to caller
        //else if name != " "
            //return name to caller
        //else if last_name != " "
            //return last_name to caller
}
