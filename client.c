#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>


#define MAX (256)
#define PORT (6003)

int main(){

    const char * addr = "127.0.0.1";

    const struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = inet_addr(addr),
        .sin_port = htons(PORT)
    };

    int file_descriptor = socket(AF_INET,SOCK_STREAM,0);
    if (file_descriptor == -1){
        printf("Socket function failed \n");
    } else{
        printf("Socket created \n");
    }

    int connect_ret = connect(file_descriptor, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (connect_ret == -1){
        printf("Connection failed \n");
    } else{
        printf("Connection established \n");
    }

    char send_buff[MAX] = "Hello, World";

    for (;;){
        write(file_descriptor, send_buff, MAX);
        sleep(1);
    }

    return 0;
}