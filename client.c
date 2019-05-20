#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080 
#define MENSAGEM "ola mundo socket"


void sendMSGServer(void *pointer);

int main(int argc, char const *argv[])
{

    //definindo thread e mensangens
    pthread_t thread_1;
    pthread_t thread_2;

    char *msg1 = "ola, essa é a mensagem da thread 1";
    char *msg2 = "ola, essa é a mensagem da thread 2";

    for(int i =0 ; i < 5 ; i++){
        //criação de pthreads para envio de mensagens para server
        pthread_create(&thread_1, NULL, (void *) &sendMSGServer, (void *) msg1);
        pthread_create(&thread_2, NULL, (void *) &sendMSGServer, (void *) msg2);
    }
    return 0;
}


//
void sendMSGServer(void *pointer){
    //mensagem a ser enviada
    char * msg = (char*) pointer;
    //variáveis do server
    struct sockaddr_in address; 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *hello = "Essa é uma mensagem do client para o server\n"; 
    char buffer[1024] = {0}; 

    //configuração do socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){ 
        printf(" Falha na criação do socket \n"); 
        return; 
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Converte endereco para forma binaria apropriada 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0){ 
        printf("Endereço inválido\n"); 
        return; 
    } 
    // Conexão com server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){ 
        perror("Falha na conexão \n"); 
        return ; 
    } 
    //envio da mensagem para server
    send(sock , msg , strlen(msg) , 0 ); 
    printf("Menssagem enviada para server\n");

    //leitura de mensagem do servidor
    valread = read( sock , buffer, 1024); 
    printf("%s\n",buffer ); 
    return; 
}