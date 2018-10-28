#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct jogadores{
	int porta;
	char *mao;
	char equipe[1];
	int id;
}jogador;

typedef struct baralho{
	char *nome;
	int valor;
}cartas;

void criaBaralho(struct baralho *bara, struct jogadores *client);

void embaralhar(struct baralho *bara, struct jogadores *client);

void enviaMengagem(char *mensagem, struct jogadores client);

void broadcast(char *mensagem, struct jogadores *client);

void atualizaMesa(char *mesa, char carta, int id);

void jogarCarta(char *mesa, struct jogadores *client, int vez);

int pegaValorCarta(char *mesa, struct baralho *bara, int posicao);

int vencedorTurno(char *mesa, struct jogadores *client, int vez, struct baralho *bara);

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
	if ((bind(listen_sock, (struct sockaddr *)&server_address,
	          sizeof(server_address))) < 0) {
		printf("could not bind socket\n");
		return 1;
	}
	int wait_size = 5;
	listen(listen_sock, wait_size);
	struct sockaddr_in client_address;
	int client_address_len = 0, placar_A = 0, placar_B = 0, n, id = 0, jogada = 0, vez = 0;
	jogador clientes[4];
	cartas baralho[40];
	char buffer[100], mesa[9], *mensagem, vencedor_turno[3];
	memset(buffer, 0 , sizeof(buffer));
	while (true) {
		// open a new socket to transmit data per connection
		int i, flag, conta = 0, contb = 0;
		for(i=0; i<4; i++){
			clientes[i].porta = accept(listen_sock, (struct sockaddr *)&client_address,&client_address_len);
			clientes[i].id = i;
			strcpy(buffer, "Conectou");
			send(clientes[i].porta, buffer, strlen(buffer), 0);
			memset(buffer, 0 , sizeof(buffer));
		}
		char q[20];
		strcpy(q, "Todo mundo conectado");
		strcpy(buffer, q);
		send(clientes[0].porta, buffer, strlen(buffer), 0);
		send(clientes[1].porta, buffer, strlen(buffer), 0);
		send(clientes[2].porta, buffer, strlen(buffer), 0);
		send(clientes[3].porta, buffer, strlen(buffer), 0);
		memset(buffer, 0, sizeof(buffer));
		criaBaralho(baralho, clientes);
		while(placar_A < 12 || placar_B<12){
			embaralhar(baralho, clientes);
			for(i=0; i<3; i++){
				vencedor_turno[i] = vencedorTurno(mesa, clientes, vez, baralho);
				if(clientes[vencedor_turno[i]].equipe[0] == 'a'){
					conta++;
				}else{
					contb++;
				}
				if((i==2)){
					if(conta==2){
						placar_A++;
						flag=1;
					}else if(contb == 2){
						placar_B++;
						flag=1;
					}
				}	
			}
			if(flag==1){
				mensagem[0] = vencedor_turno[1];
				strcat(mensagem, "Venceu o turno\n\0");
				broadcast(mensagem, clientes);
				vez = vencedor_turno[1];
			}else{
				mensagem[0] = vencedor_turno[2];
				strcat(mensagem, "Venceu o turno\n\0");
				broadcast(mensagem, clientes);
				vez = vencedor_turno[2];
			}
			conta = 0;
			contb = 0;	
		}
		
		printf("client connected with ip address: %s\n",
		       inet_ntoa(client_address.sin_addr));
	}
	close(listen_sock);
	return 0;
}

void criaBaralho(struct baralho *barai, struct jogadores *client ){
	char *q;
	q = "\noi";
	send(client[0].porta, q, strlen(q), 0);
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
}
void enviaMengagem(char *mensagem, struct jogadores client){
	send(client.porta, mensagem, strlen(mensagem), 0);
	memset(mensagem, 0, sizeof(mensagem));
}
void embaralhar(struct baralho *bara, struct jogadores *client){
	char *q;
	q = "\nalo";
	send(client[0].porta, q, strlen(q), 0);
	int contador = 0;
	int v[12], i = 0, y = 0, j = 0;
	char buffer[6];
	srand(time(NULL));
	for(contador = 0; contador < 12; contador++){
        v[i] = rand()%40;        
        for(j = 0; j < contador; j++){
            if(v[j] == v[i]){
                v[i] = rand()%40;
                j = 0;
            }
        }
	}
	j = 0;
	while(j<12){
		if(j<3){
			strcat(client[0].mao, bara[v[j]].nome);
		}else if(j >= 3 && j < 6){
			strcat(client[1].mao, bara[v[j]].nome);
		}else if(j >= 6 && j < 9){
			strcat(client[2].mao, bara[v[j]].nome);
		}else{
			strcat(client[3].mao, bara[v[j]].nome);
		}
		j++;
	}
	enviaMengagem(client[0].mao, client[0]);
	enviaMengagem(client[1].mao, client[1]);
	enviaMengagem(client[2].mao, client[2]);
	enviaMengagem(client[3].mao, client[3]);
}

void broadcast(char *mensagem, struct jogadores *client){
	int i;
	for (i = 0; i<4; i++){
		send(client[i].porta, mensagem, strlen(mensagem), 0);	
	}
}
void atualizaMesa(char *mesa, char carta, int id){
	mesa[0] = id;
	strcat(mesa, carta);
}

void jogarCarta(char *mesa, struct jogadores *client, int vez){
	int n, id;
	char *mensagem, buffer[100];
	while ((n = recv(client[vez].porta, buffer, 100, 0)) > 0){
		mensagem = "\n";
		id = client[vez].id;
		strcat(mensagem, "O ");
		mensagem[3] = id;
		strcat(mensagem, "Jogou a carta ");
		strcat(mensagem, buffer);
		strcat(mensagem, "\n");
		broadcast(mensagem, client);
		atualizaMesa(mesa, buffer, id);
		memset(mensagem, 0, sizeof(mensagem));
		memset(buffer, 0, sizeof(buffer));
		break;
	}
}

int pegaValorCarta(char *mesa, struct baralho *bara, int posicao){
	int k, maior;
	char *nome;
	nome[1] = mesa[posicao];
	nome[2] = mesa[posicao+1];
	for(k=0; k<40; k++){
		if(nome == bara[k].nome){
			maior = bara[k].valor;
		}
	}
	return maior;
}

int vencedorTurno(char *mesa, struct jogadores *client, int vez, struct baralho *bara){
	char ordem_jogada[4], valores[4];
	int i, aux1, aux2, id1, id2, id_vencedor;
	for(i=0; i<4; i++){
		ordem_jogada[i] = vez;
		jogarCarta(mesa, client, vez);
		broadcast(mesa, client);
		if(vez == 3){
			vez = 0;
		}else{
			vez++;
		}	
	}
	valores[0] = pegaValorCarta(mesa, bara, 1);
	valores[1] = pegaValorCarta(mesa, bara, 3);
	valores[2] = pegaValorCarta(mesa, bara, 5);
	valores[3] = pegaValorCarta(mesa, bara, 7);
	if(valores[0] > valores[1]){
		aux1 = valores[0];
		id1 = ordem_jogada[0];
	}else{
		aux1 = valores[1];
		id1 = ordem_jogada[1];
	}
	if(valores[2] > valores[3]){
		aux2 = valores[2];
		id2 = ordem_jogada[2];
	}else{
		aux2 = valores[3];
		id2 = ordem_jogada[3];
	}
	if(aux1>aux2){
		id_vencedor=id1;
	}else{
		id_vencedor=id2;
	}
	return id_vencedor;
}