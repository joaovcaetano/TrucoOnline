#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
	/* Variaveis para estabelecer a comunicacao */
	int socket_con, novo_socket;
	//socklen_t cliente_len;
    struct sockaddr_in serverAddr, serverStorage;
    socklen_t addr_size;

    socket_con = socket(PF_INET, SOCK_STREAM, 0);

    bzero((char *)&serverAddr, sizeof(serverAddr));    
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891); 
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
    bind(socket_con, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    
    if(listen(socket_con, 2) == 0){
        printf("Aguardando Jogadores!\n");
    }else{
        printf("Erro ao esperar jogadores!\n");
    }
    addr_size = sizeof serverStorage;
    novo_socket = accept(socket_con, (struct sockaddr *) &serverStorage, &addr_size);

    return 0;
}
  
