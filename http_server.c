#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main()
{
	//open a file
	FILE * html_data;
	html_data= fopen("index.html","r"); // "r" means read-mode, "w" means write-mode
	char response_data[1024]; //this is the string which will be used to store the webpage

	fgets(response_data,1024, html_data); // read data from the html_data object to the string response_data
	
	
	//implement socket technology
	char http_header[2048]="HTTP/1.1 200 OK\r\n\n\n" ;
	
	strcat(http_header,response_data); //concatenated all the data from response_data in the http_header string var, that is why it was made so large in the first place

	//create a server socket
	int server_socket;
	server_socket= socket(AF_INET, SOCK_STREAM,0);
	

	//define the address
	struct sockaddr_in my_server_address;
	my_server_address.sin_family=AF_INET;
	my_server_address.sin_port=htons(9001);  //htons() function converts the integer properly for the struct need
	my_server_address.sin_addr.s_addr= INADDR_ANY;

	//bind the socket
	bind(server_socket, (struct sockaddr *) &my_server_address, sizeof(my_server_address));

	//listen for connections
	listen(server_socket, 5);

	//create a variable for the client socket which will get accepted
	int client_socket;

	//create a while loop to infinitely listen and serve the requests
	while(1)
	{
		client_socket=accept(server_socket, NULL, NULL);
		send(client_socket,http_header, sizeof(http_header),0);

		printf(http_header);
		close(client_socket);

	}






	return 0;
}
