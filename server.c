#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define MAX (256)
#define PORT (60003)

void rec_and_print(int socket_fd){

    char buff[MAX];

    for (;;){
        read(socket_fd, buff, sizeof(buff));
        if( buff[0] == '\0'){
            break;
        }
        printf("From client: %s \n", buff);
        memset(buff,'\0',MAX);

    }
}



int main(){
    const char * addr = "138.68.107.119";

    const struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = inet_addr(addr),
        .sin_port = htons(PORT)
    };
    struct sockaddr_in client;

    int file_descriptor = socket(AF_INET,SOCK_STREAM,0);
    if (file_descriptor == -1){
        printf("Socket function failed \n");
    } else{
        printf("Socket created \n");
    }

    int bind_ret = bind(file_descriptor, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if (bind_ret == -1){
        printf("Bind function failed \n");
    } else {
        printf("Socket bound \n");
    }

    int listen_ret = listen(file_descriptor, SOMAXCONN);
    if (listen_ret == -1){
        printf("Listen function failed \n");
    } else {
        printf("Socket listening \n");
    }

    socklen_t len_client = sizeof(client);

    int accept_ret = accept(file_descriptor, (struct sockaddr *) &client, &len_client);
    if (accept_ret == -1){
        printf("Accept function failed \n");
    } else{
        char * client_addr;

        struct in_addr ip = {
            .s_addr = client.sin_addr.s_addr
        };

        printf("Connection from: (%s , %i) \n", inet_ntoa(ip), client.sin_port);
    }
  
    rec_and_print(accept_ret);


    return 0;
}


    /* bind - bind socket to address
     * Sockaddr is a generic descriptor for any kind of socket operation, 
     * whereas sockaddr_in is a struct specific to IP-based communication 
    */

    /* listen - listen for incomming connection
        SOMAXCONN tells the system to use the maximum backlog size for incoming connections.
        Up to this value incoming connections are put in the backlog, when the value is reached,
        connections are refused.
    */