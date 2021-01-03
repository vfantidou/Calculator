#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


//global vars			
char msg[1024];			
int clientCount = 0;		
int sock_ids[10];		

typedef struct {		
	char name[50];		
	int sock;
}Client;

void client_handler(void *sock){
	Client newclient;		
	newclient.sock=*(int*)sock;
	char *token;
	int i=0;	
	char *calc[3];
	int x=0,y=0,result=0;

	recvfrom(newclient.sock,newclient.name,50,0,NULL,NULL); 
	printf("%s is online\n",newclient.name);

	while(1){
				
		if(strcmp(msg,"exit")==0){			
			printf("%s Left the room\n",newclient.name);
			clientCount--;
			break;
		}
		else{
			recvfrom(newclient.sock,msg,1024,0,NULL,NULL);	
		}
		printf("%s send: %s\n",newclient.name,msg);
		//token= (char*)malloc(10*sizeof(strlen(msg)));
		 //o server spaei to string 

//---------ifs.c-------------------------
		
		token=strtok(msg," ");
		do{
			printf("token: %s\n",token);
			calc[i]=token;		
			token=strtok(NULL," ");
			i++;
		}while(token!=NULL);
		i=0;
		
		x=atoi(calc[0]);
		y=atoi(calc[2]);
		printf("sto 0:%d \nsto 2:%d\n",x,y);
		
		if(strcmp(calc[1],"+")==0){
			result = x+y;
		}
		else if(strcmp(calc[1],"-")==0){ //ta dipla "" einai gia string enw ta ' ' gia ena char mono
			result = x-y;
		}
		else if(strcmp(calc[1],"*")==0){
			result = x*y;
		}
		else if(strcmp(calc[1],"/")==0){
			result = x/y;
		}
		printf("result:%d\n",result);
		send(newclient.sock, &result, sizeof(int), 0);
		
		free(token);
		
	}
}

int main(int argc,char *argv[]){

	int psock,sock,ret,i,pid; 		
	struct sockaddr_in addr; //internet socket
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=htonl(INADDR_ANY);//all interfaces
	addr.sin_port=htons(1111);
	psock=socket(AF_INET,SOCK_STREAM,0);
	bind(psock,(struct sockaddr *)&addr,sizeof(addr));	
	listen(psock,10);
		
	printf("\nwaiting for new connection...\n");
	
	while(1){

		sock = accept(psock,NULL,NULL);
		strcpy(msg,"");
		printf("connection established...\n");
		sock_ids[clientCount] = sock;		
		clientCount++;				
		pid = fork();
		if(pid==0){
			printf("client is in..%d \n",sock);
			client_handler(&sock);
			
		}
	}	

	close(sock);	
	printf("\nconnection closed\n");
	close(psock);
        
return 0;

}
