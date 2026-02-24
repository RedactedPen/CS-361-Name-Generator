#include <iostream>
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

//Sets up the network connection
int establish_socket(){
    //Create the socket
    int socket_num = socket(AF_INET, SOCK_STREAM, 0);

    //Create the address info struct 
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(LOCAL_HOST);

    //Attempt to connect to the server
    int result = connect(socket_num, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(result !=0){
        std::cout << "Failed to connect to the server" << std::endl;
        return -1;
    }
    return socket_num;
}

int send_request(int socket, std::string request){

    //Add the end of transmission character
    char eot = 4;
    request += eot;

    //Set up the variables for sending data
    int total_bytes_sent = 0;
    int bytes_to_send = request.length();
    int bytes_remaining = bytes_to_send;

    char* request_ptr = &(request[0]);

    //Loop until all bytes have been sent
    while(total_bytes_sent < bytes_to_send){
        //Send the message
        int bytes_sent = send(
            socket, 
            request_ptr + total_bytes_sent,
            bytes_remaining,
            0
        );

        if(bytes_sent != -1){
            total_bytes_sent += bytes_sent;
            bytes_remaining -= bytes_sent;
        }else{
            //Some error occured. Print an error message
            std::cout << " Error on sending request\n" << std::endl;
            return -1;
        }
    }

    return 0;
}

int get_response(int socket, std::string &response){
    int initial_size = 100;
    char* message = (char*) malloc(sizeof(char) * initial_size);
    int total_bytes_received = 0;
    int max_bytes_remaining = initial_size;

    
    //Used to detect the end of transmission character used to denote the end
    //of the server's response
    char end_of_transmission[2] = {4, '\0'};


    while(strstr(message, end_of_transmission) == nullptr){
        //Check if there is more space in the message buffer
        if(max_bytes_remaining <= 0){
            //Resize the buffer to handle more text
            max_bytes_remaining += initial_size;
            initial_size *= 2;
            message = (char *) realloc(message, initial_size);
        }

        //receive the data from the client
        int bytes_received = recv(
            socket,
            message + total_bytes_received,
            max_bytes_remaining,
            MSG_PEEK
        );

        if(bytes_received > 0){
            //Server sent data, record how much was received
            total_bytes_received += bytes_received;
            max_bytes_remaining -= bytes_received;
        }else if(bytes_received == 0){
            //Server sent no data
            return -1;
        }else{
            //recv had an error
            std::cout << "Error receiving data from server, recv returned " << bytes_received << std::endl;
            return -1;
        }
    }

    //Ensure the string is properly null terminated
    char* transmission_end = strstr(message, end_of_transmission);
    transmission_end[0] = '\0';

    response = message;
    free(message);
    return 0;

}

int main(){
    constexpr int num_requests = 4;
    std::string requests[num_requests] ={
        "fantasy:true:true",
        "sci-fi:true:false",
        "modern:false:true",
        "sci-fi:true:true"
    };

    for(int i = 0; i < num_requests; i++){
        int socket = establish_socket();
        if(socket < 0){
            continue;
        }

        std::string message = requests[i];

        //Send the request
        int request_result = send_request(socket, message);
        if(request_result < 0){
            close(socket);
            continue;
        } 
        std::cout << "Sent request |" << message << "|" << std::endl;

        //Get the response
        std::string response;
        int response_result = get_response(socket, response);
        if(response_result < 0){
            close(socket);
            continue;
        }
        std::cout << "Got response |" << response << "|" << std::endl;
        close(socket);

        //Just makes the system wait to send the next request
        //std::cin >> requests[i];
    }
}