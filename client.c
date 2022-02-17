#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
	while (1) {
		int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		
		if (sockfd == -1) {
			perror("cannot create socket");
			return 1;
		}

		struct sockaddr_in sa;
		memset(&sa, 0, sizeof sa);

		sa.sin_family = AF_INET;
		sa.sin_port = htons(3456);
		int res = inet_pton(AF_INET, "127.0.0.1", &sa.sin_addr);

		if (connect(sockfd, (struct sockaddr *)&sa, sizeof sa) == -1) {
			perror("connect failed");
			return 1;
		}

		printf("Connected, press any key to continue...");
		getchar();
		close(sockfd);
	}
}
