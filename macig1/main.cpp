#include "fundamentals.hpp"
#include "fundamentals.cpp"

#include <unistd.h> 			// fork() close()

int looper()
{
	int listening_socket = make_listener(1111);
	if(listening_socket == -1)
		return -1;
	
	int client_socket;
	
	while(true)
	{
		client_socket = accept(listening_socket, NULL, NULL);

		pid_t personal_id = fork();
		if(personal_id != 0)
		{
			close(client_socket);
			continue;
		}

		break;
	}
	
	close(listening_socket);
	return client_socket;
}

int main()
{// fix step out so it ignores a -1 in the case that looper fails
	step_out(looper()); // main() will loop on looper. step_out() will only be called in the forked process
}
