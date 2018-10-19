#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
	const char* server_name = "localhost";
	const int server_port = 3000;

	struct sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;

	inet_pton(AF_INET, server_name, &server_address.sin_addr);

	server_address.sin_port = htons(server_port);

	int sock;
	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		printf("could not create socket\n");
		return 1;
	}

	// TCP is connection oriented, a reliable connection
	// **must** be established before any data is exchanged
	if (connect(sock, (struct sockaddr*)&server_address,
	            sizeof(server_address)) < 0) {
		printf("could not connect to server\n");
		return 1;
	}

	// send

	// data that will be sent to the server
	const char* data_to_send = "Bem Vindo a PUTARIA";
	send(sock, data_to_send, strlen(data_to_send), 0);
	char q[4];

	// receive

	int n = 0;
	int len = 0, maxlen = 100;
	char buffer[100];
	//char* pbuffer = buffer;

	// will remain open until the server terminates the connection
	while ((n = recv(sock, buffer, 100, 0)) > 0) {
		printf("recebido: %s\n", buffer);
		scanf("%s", q);
		send(sock, q, strlen(q), 0);
		strcpy(buffer, q);
	}

	// close the socket
	close(sock);
	return 0;
}
