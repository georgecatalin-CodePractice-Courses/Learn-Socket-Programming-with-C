#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main()
{
	//create a socket
	int network_socket;
	network_socket=socket(AF_INET,SOCK_STREAM,0); //0 means the default TCP, SOCK_STREAM means the TCP type


	//specify an address for the socket
	struct sockaddr_in my_server_address;
	my_server_address.sin_family= AF_INET;
	my_server_address.sin_port=htons(9002); //htons() function is used to convert the integer to the format understood by the sockaddr_in type
	my_server_address.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY is local computer and is 0.0.0.0;  sin_addr is a structure itself

        int connection_success=connect(network_socket, (struct sockaddr *) &my_server_address, sizeof(my_server_address));
       	/* connect() returns an integer if it was successful or not and we can use this integer for error handling 0 means OK, -1 means some error */

	if ( connection_success== -1)
	{
		printf("There was an error during the connection.");

	}

	//call the recv() function in the client to receive data from the server
	char server_response[256];
	recv(network_socket, &server_response, sizeof(server_response), 0);

	//print out the server response
	printf("The server sent the data :\t %s" , server_response);


	//close the socket
	close(network_socket);

	return 0;
}	
