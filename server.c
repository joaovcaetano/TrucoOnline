#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
	/* Variaveis para estabelecer a comunicacao */
	int socket_con = 0;
	//socklen_t cliente_len;
    struct sockaddr_in endereco_server;
    socket_con = socket(AF_INET, SOCK_STREAM,0); 
    memset(endereco_server.sin_zero, '\0', sizeof endereco_server.sin_zero);
    bzero((char *)&endereco_server, sizeof(endereco_server));
    endereco_server.sin_family = AF_INET;
    endereco_server.sin_addr.s_addr = INADDR_ANY;
    endereco_server.sin_port = htons(3000);
    bind(socket_con, (struct sockaddr *) &endereco_server,sizeof(endereco_server));
    if(listen(socket_con, 2) == 0){
        printf("Aguardando Jogadores!\n");
    }else{
        printf("Erro ao esperar jogadores!\n");
    }
    return 0;
}
  
