#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>


int main()
{
	char server_message[256]="You have received the message from the server, Alligator!!" ;

	//create the socket
	int server_socket;
	server_socket=socket(AF_INET, SOCK_STREAM, 0);


	//define the server  address
	struct sockaddr_in my_server_addr;
	my_server_addr.sin_family=AF_INET;
	my_server_addr.sin_port=htons(9002);
	my_server_addr.sin_addr.s_addr=INADDR_ANY;



	//bind the socket to our IP and port
	bind(server_socket, (struct sockaddr *) &my_server_addr,sizeof(my_server_addr)); /* bind() behaves similarly with connect() */

	//listen for connections 
	listen(server_socket,5); /* 5 is the backlog which is how many can be waiting for this particular socket at one point it time, in this case should be at least 1 */

	//create an integer to hold the client socket
	int client_socket;

	client_socket=accept(server_socket,NULL, NULL); //1st NULL is a structure of the address of the client, but in this case is local and does not matter

	//send the message 
	send(client_socket, server_message, sizeof(server_message),0);

	//close the socket
	close(server_socket);
        

	return 0;
}
