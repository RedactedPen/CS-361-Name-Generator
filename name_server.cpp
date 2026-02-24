#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>

//Networking headers
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 34568
#define LOCAL_HOST "127.0.0.1"

//load data into vectors
std::vector<std::string> sci_fi_first_name;
std::vector<std::string> sci_fi_last_name;
std::vector<std::string> fantasy_first_name;
std::vector<std::string> fantasy_last_name;
std::vector<std::string> modern_first_name;
std::vector<std::string> modern_last_name;

//Sets up the network connection
int establish_socket(){
    //Create the socket
    int socket_num = socket(AF_INET, SOCK_STREAM, 0);

    //Create the address info struct 
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(LOCAL_HOST);

    //Attempt to bind to localhost
    int bind_result = bind(socket_num, &server_addr, sizeof(server_addr));
    if(bind_result != 0){
        std::cout << "Failed to bind to localhost" << std::endl;
        return -1;
    }

    //Attempt to listen to the bound port
    int listen_result = listen(socket_num, 1);
    if(listen_result != 0){
        std::cout << "Failed to listen to the port" << std::endl;
        return -1;
    }
    return socket_num;

}

//Gets the request data from the client over the provided socket
//Stores the data in the provided variables
//Returns 0 on success and -1 on a failure
int get_request(int socket, std::string &theme, bool &first_name, bool &last_name){
    int initial_size = 100;
    char* message = (char*) malloc(sizeof(char) * initial_size);
    int total_bytes_received = 0;
    int max_bytes_remaining = initial_size;

    
    //Used to detect the end of transmission character used to denote the end
    //of the client's request
    char end_of_transmission = {4, '\0'};


    while(strstr(message, end_of_transmission) == null){
        //Check if there is more space in the message buffer
        if(max_bytes_remaining <= 0){
            //Resize the buffer to handle more text
            max_bytes_remaining += initial_size;
            initial_size *= 2;
            peekmessage_text = (char *) realloc(message, initial_size);
        }

        //receive the data from the client
        int bytes_received = recv(
            socket,
            message + total_bytes_received,
            max_bytes_remaining,
            MSG_PEEK
        );

        if(bytes_received > 0){
            //Client sent data, record how much was received
            total_bytes_received += bytes_received;
            max_bytes_remaining -= bytes_received;
        }else if(bytes_received == 0){
            //Client sent no data
            return -1;
        }else{
            //recv had an error
            std::cout << "Error receiving data from client, recv returned " << bytes_received << std::endl;
            return -1;
        }
    }

    //Ensure the string is properly null terminated
    char* transmission_end = strstr(peek_text, eot);
    transmission_end[0] = '\0';

    char* message_base = message;

    //Message syntax: theme:first_name:last_name
    //theme: string
    //first_name: bool
    //last_name: bol

    //Isolate the theme from the rest of the request
    char* first_delimiter = strstr(message, ":");
    if(first_delimiter == nullptr){
        std::cout << "Client sent bad request |" << message << "|" << std::endl;
        close(socket);
        return -1;
    }
    first_delimiter[0] = '\0';
    first_delimiter++;

    //Store the theme text in the theme variable
    theme = message;

    message = first_delimiter;

    //Isolate the first_name bool from the rest of the request
    char* second_delimiter = strstr(message, ":");
    if(second_delimiter == nullptr){
        std::cout << "Client sent bad request |" << message << "|" << std::endl;
        close(socket);
        return -1;
    }
    second_delimiter[0] = '\0';
    second_delimiter++;

    //Check the value
    if(std::strcmp(message, "true")){
        first_name = true;
    }else if(std::strcmp(message, "false")){
        first_name = false;
    }else{
        std::cout << "Client sent bad request |" << message << "|" << std::endl;
        close(socket);
        return -1;
    }

    message = second_delimiter;

    //Check the value of the last_name variable
    if(std::strcmp(message, "true")){
        last_name = true;
    }else if(std::strcmp(message, "false")){
        last_name = false;
    }else{
        std::cout << "Client sent bad request |" << message << "|" << std::endl;
        close(socket);
        return -1;
    }

    //Clean up resources
    free(message_base);
    return 0;
}

void send_response(int socket, std::string first_name, std::string last_name){
    std::string message = "";
    message += first_name;
    message += " ";
    message += last_name;

    //Set up the variables for sending data
    int total_bytes_sent = 0;
    int bytes_to_send = message.length;
    int bytes_remaining = bytes_to_send;

    //Loop until all bytes have been sent
    while(total_bytes_sent < bytes_to_send){
        //Send the message
        int bytes_sent = send(
            socket, 
            message + total_bytes_sent,
            bytes_remaining,
            0
        );

        if(bytes_sent != -1){
            total_bytes_sent += bytes_sent;
            bytes_remaining -= bytes_sent;
        }else{
            //Some error occured. Print an error message
            std::cout << " Error on sending response\n" << std::endl
            return;
        }
    }
}

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
    //Set up the listening port
    int socket = establish_socket();
    if(socket == -1){
        return -1;
    }

    //Load the name data into memory
    load_data();
    
    while(True){
        int client_socket = accept(socket, 0, 0);
        if(client_socket == -1){
            std::cout << "Failed to connect to the client" << std::endl;
            continue;
        }

        std::string theme;
        bool first_name;
        bool last_name;

        int request_result = get_request(client_socket, theme, first_name, last_name);
        if(request_result < 0){
            //Something went wrong
            close(client_socket);
            return -1;
        }

        //Ensure the client actually requested either a first name or a last name
        if(!first_name && !last_name){
            std::cout << "Client did not request a first name or a last name" << std::endl;
            close(client_socket);
            continue;
        }
        std::string first_name_str = "";
        std::string last_name_str = "";
        if(theme == "fantasy"){
            if(first_name){
                int num = rand() % 200;
                first_name_str = fantasy_first_name[num];
            }

            if(last_name){
                int num = rand() % 200;
                last_name_str = fantasy_last_name[num];
            }
        }else if(theme == "sci-fi"){
            if(first_name){
                int num = rand() % 200;
                first_name_str = sci_fi_first_name[num];
            }

            if(last_name){
                int num = rand() % 200;
                last_name_str = sci_fi_last_name[num];
            }
        }else if(theme == "modern"){
            if(first_name){
                int num = rand() % 200;
                first_name_str = modern_first_name[num];
            }

            if(last_name){
                int num = rand() % 200;
                last_name_str = modern_last_name[num];
            }
        }else{
            std::cout << "Client sent bad request for theme |" << theme << "|" << std::endl;
            close(client_socket);
            continue;
        }

        //Send the name in response
        send_response(client_socket, first_name, last_name);

        //Close the socket
        close(client_socket);
    }
        // //if theme == fantasy, first name 
        //     int num = rand() % 200;
        //     name = fantasy_first_name[num];   

        // //if theme == sci_fi, first name 
        //     int num = rand() % 200;
        //     name = sci_fi_first_name[num];

        // //if theme == modern, first name 
        //     int num = rand() % 200;
        //     name = modern_first_name[num];

        // //if theme == fantasy, last name 
        //     num = rand() % 200;
        //     last_name = fantasy_last_name[num];   

        // //if theme == sci_fi, last name 
        //     int num = rand() % 200;
        //     last_name = sci_fi_last_name[num];

        // //if theme == modern, last name 
        //     int num = rand() % 200;
        //     last_name = modern_last_name[num];

        // //if name != " " && last_name != " "
        //     std::string full_name = name + " " + last_name;
        //     //return full_name to caller
        // //else if name != " "
        //     //return name to caller
        // //else if last_name != " "
        //     //return last_name to caller
}
