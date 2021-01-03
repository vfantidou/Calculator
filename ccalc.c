#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>

 	

int main(int argc,char *argv[]){
	int i,result;
	int sock = 0;		
	int terminate = 0;
	char msg[1024],name[50];
	struct sockaddr_in addr;	
					
	addr.sin_family=AF_INET;		//ola ayta einai socket initialization 
	inet_aton("127.0.0.1",&addr.sin_addr); //localhost
	addr.sin_port=htons(argv[1]);  //sto port poy dinei o xrhsths ./c 1010
	sock=socket(AF_INET,SOCK_STREAM,0); 
	connect(sock,(struct sockaddr *)&addr,sizeof(addr));
	printf("connected, pls give name\n");			//epeidh exeis polloys client o kathenas tha dinei to onoma toy gia na toys ksexvrizei

	fgets(name,50,stdin);		 
	msg[strlen(name)-1]='\0';
	send(sock,name,strlen(name)+1,0);
	
	while(1){
		fgets(msg,1024,stdin);		 //gia eisagwgh apo to plhktrologio
		msg[strlen(msg)-1]='\0';
		if (strcmp(msg, "exit") == 0) {
			printf("Client logged out\n");
			send(sock, msg, strlen(msg) + 1, 0);	
			break;
        	}
		else{
			send(sock, msg, strlen(msg) + 1, 0);//stelneis to string me thn morfh 1 + 1 px me kena kai sthn mesh symvolo
			recv(sock, &result, sizeof(int), 0);// pairneis to result apo ton server
			printf("result: %d\n",result); 
		}
		
	}
	close(sock);

return 0;
}
