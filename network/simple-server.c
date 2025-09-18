#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>

typedef enum{
	PROTO_HELLO,
} proto_type_e;

typedef struct {
	proto_type_e type;
	unsigned short len;
} proto_hdr_t;

void handle_client(int fd) {
	char buf[4096] = {0};
	read(fd, buf, sizeof(proto_hdr_t) + sizeof(int));

	proto_hdr_t *hdr = buf;
	hdr->type = ntohl(hdr->type);
	hdr->len = ntohs(hdr->len);

	int *data = &hdr[1];
	*data = ntohl(*data);

	if(hdr->type != PROTO_HELLO){
		printf("Protocol mismatch failing");
		return;
	}

	if(*data != 1){
		printf("Protocol version mismatch, failing\n");
		return;
	}

	printf("Server connected, protocal v1.\n");
}

int main() {
	struct sockaddr_in serverInfo = {0};
	struct sockaddr_in clientInfo = {0};
	int clientSize = 0;

	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr.s_addr = 0;
	serverInfo.sin_port = htons(5555);

	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd == -1){
		perror("socket");
		return -1;
	}

	// bind
	if (bind(fd, (struct sockaddr*)&serverInfo, sizeof(serverInfo))==-1){
		perror("bind");
		close(fd);
		return -1;
	};

	// listen
	if(listen(fd,0) == -1){
		perror("listen");
		close(fd);
		return -1;
	}

	while(1) {
		// accept
		int cfd = accept(fd, (struct sockaddr*)&clientInfo, &clientSize);
		if(cfd == -1){
			perror("accept");
			close(fd);
			return -1;
		}

		handle_client(cfd);

		close(cfd);
	}
}