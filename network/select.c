#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define MAX_CLIENTS 256
#define PORT 8081
#define BUFF_SIZE 4096

typedef enum {
	STATE_NEW,
	STATE_CONNECTED,
	STATE_DISCONNECTED
} state_e;

typedef struct {
	int fd;
	state_e state;
	char buffer[4096];
} clientstate_t;

clientstate_t clientStates[MAX_CLIENTS];


void int_clients() {
	for (int i = 0; i < MAX_CLIENTS; i++){
		clientStates[i].fd = -1;
		clientStates[i].state = STATE_NEW;
		memset(&clientStates[i].buffer, '\0', BUFF_SIZE);
	}
}

int find_free_slot(){
	for(int i=0; i < MAX_CLIENTS; i++){
		if (clientStates[i].fd == -1){
			return i;
		}
	}
	return -1;
}

int main () {
	int listen_fd, conn_fd, nfds, freeSlot;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_len = sizeof(client_addr);
	fd_set read_fds, write_fds;

	int_clients();

	if((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);

	// bind
	if(bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
		perror("bind");
		exit(EXIT_FAILURE);
	}

	// listen
	if(listen(listen_fd, 10) == -1){
		perror("listen");
		exit(EXIT_FAILURE);
	}

	printf("Server listening on port %d\n", PORT);

	while(1){
		// Clear the FD sets
		FD_ZERO(&read_fds);
		FD_ZERO(&write_fds);

		//add listening socket to the read set
		FD_SET(listen_fd, &read_fds);
		nfds = listen_fd + 1;

		//add active connections to the read set
		for (int i = 0; i < MAX_CLIENTS; i++){
			if(clientStates[i].fd != -1){
				FD_SET(clientStates[i].fd, &read_fds);
				if(clientStates[i].fd >= nfds) nfds = clientStates[i].fd +1;
			}
		}

		// Wait for an activity on one of the sockets
		if(select(nfds, &read_fds, &write_fds, NULL, NULL) == -1){
			perror("select");
			exit(EXIT_FAILURE);
		}

		// Check for new connections
		if(FD_ISSET(listen_fd, &read_fds)){
			if((conn_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_len)) == -1){
				perror("accept");
				continue;
			}
		}

		printf("New connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

		//Find a free slot for the new connection
		freeSlot = find_free_slot();
		if(freeSlot == -1){
			printf("Server full closing new connection\n");
			close(conn_fd);
		} else {
			clientStates[freeSlot].fd = conn_fd;
			clientStates[freeSlot].state = STATE_CONNECTED;
		}

		for (int i = 0; i < MAX_CLIENTS; i++){
			if(clientStates[i].fd != -1 && FD_ISSET(clientStates[i].fd, &read_fds)){

				ssize_t bytes_read = read(clientStates[i].fd, &clientStates[i].buffer, sizeof(clientStates[i].buffer));

				if(bytes_read <=0) {
					close(clientStates[i].fd);
					clientStates[i].fd = -1;
					clientStates[i].state = STATE_DISCONNECTED;
					printf("Client disconnected on error\n");
				} else {
					printf("Received data from client: %s\n", clientStates[i].buffer);
				}
			}
		}
	}

	return 0;
}