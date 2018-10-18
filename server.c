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
}jogador;

typedef struct baralho{
	char nome[2];
	int valor;
}baralho;

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
	jogador cliente[4];
	baralho baralho;
	int id = 0;
	if ((cliente[id].porta =
					 accept(listen_sock, (struct sockaddr *)&client_address,
									&client_address_len)) < 0) {
		printf("could not open a socket to accept data\n");
		return 1;
	}
	printf("client connected with ip address: %s\n",
				 inet_ntoa(client_address.sin_addr));
	while (true) {
		int n = 0;
		int len = 0, maxlen = 100;
		char buffer[100];

		while ((n = recv(cliente[id].porta, buffer, maxlen, 0)) > 0) {
			printf("%d",n);
			maxlen -= n;
			len += n;
      printf("recebido: '%s'\n", buffer);

			// echo received content back
			send(cliente[id].porta, buffer, len, 0);
			memset(buffer, 0 , sizeof(buffer));
		}
		close(cliente[id].porta);
	}

	close(listen_sock);
	return 0;
}
