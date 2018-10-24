#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct jogadores{
	int porta;
	char mao[3];
	char equipe[1];
	int id;
}jogador;

typedef struct baralho{
	char *nome;
	int valor;
}cartas;

void criaBaralho(struct baralho *bara, struct jogadores *client);

void embaralhar(struct baralho *bara, struct jogadores *client);


int main(int argc, char *argv[]) {
	int SERVER_PORT = 3000;

	struct sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;

	server_address.sin_port = htons(SERVER_PORT);

	server_address.sin_addr.s_addr = htonl(INADDR_ANY);

	int listen_sock;
	if ((listen_sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		printf("could not create listen socket\n");
		return 1;
	}

	// bind it to listen to the incoming connections on the created server
	// address, will return -1 on error
	if ((bind(listen_sock, (struct sockaddr *)&server_address,
	          sizeof(server_address))) < 0) {
		printf("could not bind socket\n");
		return 1;
	}

	int wait_size = 5;  // maximum number of waiting clients, after which
	                     // dropping begins
	if (listen(listen_sock, wait_size) < 0) {
		printf("could not open socket for listening\n");
		return 1;
	}

	// socket address used to store client address
	struct sockaddr_in client_address;
	int client_address_len = 0;
	jogador clientes[4];
	cartas baralho[40];
	char buffer[100];
	while (true) {
		// open a new socket to transmit data per connection
		int i;
		for(i=0; i<4; i++){
			clientes[i].porta = accept(listen_sock, (struct sockaddr *)&client_address,&client_address_len);
			clientes[i].id = i;
			send(clientes[i].porta, buffer, strlen(buffer), 0);
			memset(buffer, 0 , sizeof(buffer));
		}
		char q[20];
		printf("Todo mundo conectado");
		strcpy(q, "Todo mundo conectado");
		strcpy(buffer, q);
		send(clientes[0].porta, buffer, strlen(buffer), 0);
		send(clientes[1].porta, buffer, strlen(buffer), 0);
		send(clientes[2].porta, buffer, strlen(buffer), 0);
		send(clientes[3].porta, buffer, strlen(buffer), 0);
		memset(&buffer, 0, sizeof(buffer));
		printf("oi");
		criaBaralho(baralho, clientes);
		embaralhar(baralho, clientes);
		printf("olar");
		//char *pbuffer = buffer;

		printf("client connected with ip address: %s\n",
		       inet_ntoa(client_address.sin_addr));
	}
	close(listen_sock);
	return 0;
}

void criaBaralho(struct baralho *barai, struct jogadores *client ){
	barai[0].nome = "4p"; barai[0].valor= 13;
	barai[1].nome = "7c"; barai[1].valor= 12;
	barai[2].nome = "ae"; barai[2].valor= 11;
	barai[3].nome = "7o"; barai[3].valor= 10;
	barai[4].nome = "3p"; barai[4].valor= 9;
	barai[5].nome = "3c"; barai[5].valor= 9;
	barai[6].nome = "3e"; barai[6].valor= 9;
	barai[7].nome = "3o"; barai[7].valor= 9;
	barai[8].nome = "2p"; barai[8].valor= 8;
	barai[9].nome = "2c"; barai[9].valor= 8;
	barai[10].nome = "2e"; barai[10].valor= 8;
	barai[11].nome = "2c"; barai[11].valor= 8;
	barai[12].nome = "ap"; barai[12].valor= 7;
	barai[13].nome = "ac"; barai[13].valor= 7;
	barai[14].nome = "ao"; barai[14].valor= 7;
	barai[15].nome = "kp"; barai[15].valor= 6;
	barai[16].nome = "kc"; barai[16].valor= 6;
	barai[17].nome = "ke"; barai[17].valor= 6;
	barai[18].nome = "ko"; barai[18].valor= 6;
	barai[19].nome = "jp"; barai[19].valor= 5;
	barai[20].nome = "jc"; barai[20].valor= 5;
	barai[21].nome = "je"; barai[21].valor= 5;
	barai[22].nome = "jo"; barai[22].valor= 5;
	barai[23].nome = "qp"; barai[23].valor= 4;
	barai[24].nome = "qc"; barai[24].valor= 4;
	barai[25].nome = "qe"; barai[25].valor= 4;
	barai[26].nome = "qo"; barai[26].valor= 4;
	barai[27].nome = "7p"; barai[27].valor= 3;
	barai[28].nome = "7e"; barai[28].valor= 3;
	barai[29].nome = "6p"; barai[29].valor= 2;
	barai[30].nome = "6c"; barai[30].valor= 2;
	barai[31].nome = "6e"; barai[31].valor= 2;
	barai[32].nome = "6o"; barai[32].valor= 2;
	barai[33].nome = "5p"; barai[33].valor= 1;
	barai[34].nome = "5c"; barai[34].valor= 1;
	barai[35].nome = "5e"; barai[35].valor= 1;
	barai[36].nome = "5o"; barai[36].valor= 1;
	barai[37].nome = "4c"; barai[37].valor= 0;
	barai[38].nome = "4e"; barai[38].valor= 0;
	//barai[39].nome,="4o"); strcpy(barai[39].valor , 0);
	barai[39].nome = "4o";
	barai[39].valor = 0;
	char *q;
	q = "\noi";
	send(client[0].porta, q, strlen(q), 0);
}
void embaralhar(struct baralho *bara, struct jogadores *client){
	char *q;
	q = "\nalo";
	send(client[0].porta, q, strlen(q), 0);int contador = 0;
	int v[12], j = 0;
	char buffer[6];
	while(contador < 12){
		int r = (rand() % 40);
		v[contador] = r;
		contador = contador ++;
	}
	while(j < 12){
		/*buffer[y] = bara[v[j]].nome[0];
		y++;
		buffer[y] = bara[v[j]].nome[1];
		y++;*/
		j++;
		if(j == 2){
			send(client[0].porta, buffer, strlen(buffer), 0);
			memset(&buffer, 0, sizeof(buffer));
		}else if(j == 5){
			send(client[1].porta, buffer, strlen(buffer), 0);
			memset(&buffer, 0, sizeof(buffer));
		}else if(j == 8){
			send(client[2].porta, buffer, strlen(buffer), 0);
			memset(&buffer, 0, sizeof(buffer));
		}else if(j == 11){
			send(client[3].porta, buffer, strlen(buffer), 0);
			memset(&buffer, 0, sizeof(buffer));
		}
	}
}