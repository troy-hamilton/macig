#include <netinet/in.h>		// struct sockaddr struct sockaddr_in
#include <sys/socket.h>		// socket() bind() listen()
#include <unistd.h>			// close()
#include <string.h>			// memset()

int make_listener(unsigned int port_number)
{
	int listening_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(listening_socket == -1)
	{
		return -1;
	}
	
	struct sockaddr_in listener_address;
	memset(&listener_address, 0, sizeof(struct sockaddr_in));
	
	listener_address.sin_family = AF_INET;
	listener_address.sin_port = htons(port_number);
	listener_address.sin_addr.s_addr = INADDR_ANY;
	
	if(bind(listening_socket, (const struct sockaddr*) &listener_address, 
		sizeof(struct sockaddr_in)) == -1)
	{
		close(listening_socket);
		return -1;
	}
	
	if(listen(listening_socket, 4096) == -1)
	{
		close(listening_socket);
		return -1;
	}
	
	return listening_socket;
}
