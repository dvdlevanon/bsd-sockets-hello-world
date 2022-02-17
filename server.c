#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
	int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if (sockfd == -1) {
		perror("cannot create socket");
		return 1;
	}
	
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0) {
		perror("cannot set socket options");
		return 1;
	}

	struct sockaddr_in sa;
	memset(&sa, 0, sizeof sa);

	sa.sin_family = AF_INET;
	sa.sin_port = htons(3456);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sockfd,(struct sockaddr *)&sa, sizeof sa) == -1) {
		perror("bind failed");
		return 1;
	}

	if (listen(sockfd, 1) == -1) {
		perror("listen failed");
		return 1;
	}

	while (1) {
		printf("Waiting for client\n");
		
		int clientfd = accept(sockfd, NULL, NULL);
		
		if (clientfd == -1) {
			perror("accept failed");
			return 1;
		}
		
		printf("Client accepted [sockfd: %d] [clientfd: %d]\n", sockfd, clientfd);
		printf("Press any key to continue...");
		getchar();
		
		if (shutdown(clientfd, SHUT_RDWR) == -1) {
			perror("shutdown failed");
			return 1;
		}
		
		close(clientfd);
	} 
}
