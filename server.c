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
	char nome[2];
	int valor;
}cartas;

void embaralhar(cartas *baralho, jogador *clientes){
	printf("alo");
	int contador = 0;
	int v[12];
	char buffer[6];
	while(contador < 12){
		int r = (rand() % 40);
		v[contador] = r;
		contador = contador ++;
	}
	buffer[0] = baralho[v[1]].nome[0];
	buffer[1] = baralho[v[1]].nome[1];
	buffer[2] = baralho[v[2]].nome[0];
	buffer[3] = baralho[v[2]].nome[1];
	buffer[4] = baralho[v[3]].nome[0];
	buffer[5] = baralho[v[3]].nome[1];
	printf("oi\n");
	printf("%s\n", buffer);
	send(clientes[0].porta, buffer, strlen(buffer), 0);

	buffer[0] = baralho[v[4]].nome[0];
	buffer[1] = baralho[v[4]].nome[1];
	buffer[2] = baralho[v[5]].nome[0];
	buffer[3] = baralho[v[5]].nome[1];
	buffer[4] = baralho[v[6]].nome[0];
	buffer[5] = baralho[v[6]].nome[1];
	printf("oi\n");
	printf("%s\n", buffer);
	send(clientes[1].porta, buffer, strlen(buffer), 0);

	buffer[0] = baralho[v[7]].nome[0];
	buffer[1] = baralho[v[7]].nome[1];
	buffer[2] = baralho[v[8]].nome[0];
	buffer[3] = baralho[v[8]].nome[1];
	buffer[4] = baralho[v[9]].nome[0];
	buffer[5] = baralho[v[9]].nome[1];
	printf("oi\n");
	printf("%s\n", buffer);
	send(clientes[2].porta, buffer, strlen(buffer), 0);

	buffer[0] = baralho[v[10]].nome[0];
	buffer[1] = baralho[v[10]].nome[1];
	buffer[2] = baralho[v[11]].nome[0];
	buffer[3] = baralho[v[11]].nome[1];
	buffer[4] = baralho[v[12]].nome[0];
	buffer[5] = baralho[v[12]].nome[1];
	printf("oi\n");
	printf("%s\n", buffer);
	send(clientes[3].porta, buffer, strlen(buffer), 0);
	return;
}
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
	baralho[0].nome[0]='4';
	baralho[0].nome[1]='p';
	baralho[0].valor = 40;
	baralho[1].nome[0]='7';
	baralho[1].nome[1]='c';
	baralho[1].valor = 39;
	baralho[2].nome[0]='a';
	baralho[2].nome[1]='e';
	baralho[2].valor = 38;
	baralho[3].nome[0]='7';
	baralho[3].nome[1]='o';
	baralho[3].valor = 37;

	baralho[4].nome[0]='3';
	baralho[4].nome[1]='p';
	baralho[4].valor = 36;
	baralho[5].nome[0]='3';
	baralho[5].nome[1]='c';
	baralho[5].valor = 36;
	baralho[6].nome[0]='3';
	baralho[6].nome[1]='e';
	baralho[6].valor = 36;
	baralho[7].nome[0]='3';
	baralho[7].nome[1]='o';
	baralho[7].valor = 36;

	baralho[8].nome[0]='2';
	baralho[8].nome[1]='p';
	baralho[8].valor = 35;
	baralho[9].nome[0]='2';
	baralho[9].nome[1]='c';
	baralho[9].valor = 35;
	baralho[10].nome[0]='2';
	baralho[10].nome[1]='e';
	baralho[10].valor = 35;
	baralho[11].nome[0]='2';
	baralho[11].nome[1]='o';
	baralho[11].valor = 35;


	baralho[12].nome[0]='a';
	baralho[12].nome[1]='c';
	baralho[12].valor = 34;
	baralho[13].nome[0]='a';
	baralho[13].nome[1]='o';
	baralho[13].valor = 34;
	baralho[14].nome[0]='a';
	baralho[14].nome[1]='p';
	baralho[14].valor = 34;


	baralho[15].nome[0]='k';
	baralho[15].nome[1]='p';
	baralho[15].valor = 33;
	baralho[16].nome[0]='k';
	baralho[16].nome[1]='c';
	baralho[16].valor = 33;
	baralho[17].nome[0]='k';
	baralho[17].nome[1]='e';
	baralho[17].valor = 33;
	baralho[18].nome[0]='k';
	baralho[18].nome[1]='o';
	baralho[18].valor = 33;

	baralho[19].nome[0]='j';
	baralho[19].nome[1]='p';
	baralho[19].valor = 32;
	baralho[20].nome[0]='j';
	baralho[20].nome[1]='c';
	baralho[20].valor = 32;
	baralho[21].nome[0]='j';
	baralho[21].nome[1]='e';
	baralho[21].valor = 32;
	baralho[22].nome[0]='j';
	baralho[22].nome[1]='o';
	baralho[22].valor = 32;

	baralho[23].nome[0]='q';
	baralho[23].nome[1]='p';
	baralho[23].valor = 31;
	baralho[24].nome[0]='q';
	baralho[24].nome[1]='c';
	baralho[24].valor = 31;
	baralho[25].nome[0]='q';
	baralho[25].nome[1]='e';
	baralho[25].valor = 31;
	baralho[26].nome[0]='q';
	baralho[26].nome[1]='o';
	baralho[26].valor = 31;

	baralho[27].nome[0]='7';
	baralho[27].nome[1]='p';
	baralho[27].valor = 30;
	baralho[28].nome[0]='7';
	baralho[28].nome[1]='e';
	baralho[28].valor = 30;

	baralho[29].nome[0]='6';
	baralho[29].nome[1]='p';
	baralho[29].valor = 29;
	baralho[30].nome[0]='6';
	baralho[30].nome[1]='c';
	baralho[30].valor = 29;
	baralho[31].nome[0]='6';
	baralho[31].nome[1]='e';
	baralho[31].valor = 29;
	baralho[32].nome[0]='6';
	baralho[32].nome[1]='o';
	baralho[32].valor = 29;

	baralho[33].nome[0]='5';
	baralho[33].nome[1]='p';
	baralho[33].valor = 28;
	baralho[34].nome[0]='5';
	baralho[34].nome[1]='c';
	baralho[34].valor = 28;
	baralho[35].nome[0]='5';
	baralho[35].nome[1]='e';
	baralho[35].valor = 28;
	baralho[36].nome[0]='5';
	baralho[36].nome[1]='o';
	baralho[36].valor = 28;

	baralho[37].nome[0]='4';
	baralho[37].nome[1]='c';
	baralho[37].valor = 27;
	baralho[38].nome[0]='4';
	baralho[38].nome[1]='e';
	baralho[38].valor = 27;
	baralho[39].nome[0]='4';
	baralho[39].nome[1]='o';
	baralho[39].valor = 27;

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
		memset(buffer, 0, sizeof(buffer));
		embaralhar(baralho, clientes);
		printf("olar");
		//char *pbuffer = buffer;

		printf("client connected with ip address: %s\n",
		       inet_ntoa(client_address.sin_addr));
	}
	close(listen_sock);
	return 0;
}
