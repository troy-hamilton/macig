#include "fundamentals.hpp"
#include "fundamentals.cpp"

#include <unistd.h> 			// fork() close()

int main()
{
	int listening_socket = make_listener(1111);
	if(listening_socket == -1)
		return -1;
	
	while(true)
	{
		int client_socket = accept(listening_socket, NULL, NULL);

		pid_t personal_id = fork();
		if(personal_id != 0)
		{
			close(client_socket);
			continue;
		}

		break;
	}
}
