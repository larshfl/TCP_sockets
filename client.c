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
#include<string.h>


#define MAX (256)
#define PORT (60003)

int nordic_inet_addr (uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
	uint32_t value = 0;

	value |= (uint32_t)((((uint32_t)(d)) << 24) & 0xFF000000);
	value |= (uint32_t)((((uint32_t)(c)) << 16) & 0x00FF0000);
	value |= (uint32_t)((((uint32_t)(b)) << 8) & 0x0000FF00);
	value |= (uint32_t)((((uint32_t)(a)) << 0) & 0x000000FF);

	return value;
}


int main(){

    const char * addr = "138.68.107.119";

    printf("C: %i, Nordic: %i \n", inet_addr(addr), nordic_inet_addr(138,68,107,119));

    const struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = inet_addr(addr),
        .sin_port = htons(PORT)
    };

    printf("htons(6003): %i \n", htons(PORT));

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

    char * send_buff = "Hello, World";
    int len = strlen(send_buff);

    for (;;){
        write(file_descriptor, send_buff, len);
        sleep(1);
    }

    return 0;
}