#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>  //this header contains a function for converting network  addresses



int main(int argc, char* argv[]) //argc is the number of command line arguments , argv is the array that contains these arguments. Element [0] is the name of the program so you should be looking for [1]... to get the actual command line arguments
{
	//grab the address of the server and store it in a pointer(=string). The address of the server will be an argument of the program
	char * server_address;
	server_address=argv[1];

	//create a client socket
	int client_socket;
	client_socket=socket(AF_INET, SOCK_STREAM, 0);

	//connect the client socket to the address
	struct sockaddr_in remote_address;
	remote_address.sin_family=AF_INET;
	remote_address.sin_port=htons(80);
	inet_aton(server_address, &remote_address.sin_addr.s_addr); // inet_aton() is a function provided by the header <arpa/inet.h> and it converts the string with the address to a format understood by the struct remote_address.sin_addr.s_addr


       connect(client_socket, (struct sockaddr * ) &remote_address, sizeof(remote_address));

       //create two variables to hold the request and response

       char request[]="GET / HTTP/1.1 \r\n\r\n";
       // GET is the method  and  / at the resource is like requesting a website without specifying a certain web page
       
       char response[4096];

       //send
       send(client_socket, request, sizeof(request),0);

       //receive the response
       recv(client_socket,&response, sizeof(response),0);

       printf("The response from the server is : \n %s\n", response);

       //close the client socket
       close(client_socket);


	return 0;
}


