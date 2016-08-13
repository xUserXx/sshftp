#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <sys/types.h>
#include <errno.h>






int main(int argc,char*argv){

    unsigned long tamanho=0, bytes=0 ;     //sera usado para contar bytes e tamanho no hora do envio ou recebimento

    char op[1],nome[12],senha[6],endereco[15];
     
    char *bufenvio= NULL;                  // buffer de envio para o servidor
    
    char buffer[1024];    		// tamanho do buffer de recebimento do servidor sera de 1 mb
    
    int meusocket;
    int newsocket;                       // socket do servidor
    int conexao;
    
    
    struct sockaddr_in servidor;    // strutura do servidor
    struct sockaddr_in cliente;	   //strutura do cliente
    struct hostent *meuip;		//para obter meu local
    struct hostent *servip;		//para obter de destino
   
    

    printf("conectar ao servidor--->>> ");
    fgets(endereco,15,stdin);

    //nao sei se precisarei, mas sei la alguma altenticacao ou restriçao por ip que o servidor faça tendeu
    meuip=gethostbyname("localhost"); 
					    
    servip=gethostbyname(endereco);
	if(servip==NULL){
	    printf("servidor nao encontrado ou desconhecido\n");
	    exit(1);
	}
    
    meusocket=socket(AF_INET,SOCK_STREAM,0);
	if(meusocket<0){
	    printf("erro na criacao do socket");
	    exit(2);
	}

    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(21);
    servidor.sin_addr.s_addr = ("endereco");  // colaremos ja o IP aqui????
    memset(&(servidor.sin_zero), '\0', 8);

    conexao=connect(meusocket,(struct sockaddr_in*)&servidor,sizeof(servidor));
    
   if(conexao<0){
	printf("erro ao se conectar");
	close(meusocket);
	exit(3);
    }
  

  fputs(resposta());     /* aqui vira a resposta do servidor tipo "seja bem vindo" e tera as opcoes
			    login e cadastro. algo do tipo
			    ****************seja bem vindo ao ftp************
			    *                                               *
			    *                    l-login                     *
			    *		         c-cadastro		    *
                            ******************** END*************************

			    */					    

    
    op=getchar();
    switch(op)
    {
	case 'l':
	    login();
	    break;
	case   'c':
	    cadastrar();
	default:
	    exit(1);
    }

}


   /* Obs na resposta que o servidor mandara so havera duas opcoes para cada funçao,  Erro
       ou a mensagem positiva para cumprir a funçao;*/

 void login(){
    char  msgrecebida[16]="SEJA BEM VINDO";          //nao tenho certeza se usarei isso aqui;
    printf("**********CLIENTE FTP**********\n\n\n");
    printf("informe o usuario ");
    fgets(nome,12,stdin);
    
    tamanho=strlen(nome);                               //tamanho da string do nome
    bufenvio=(char*)malloc(tamanho);			//alocando no buffer o nome
    strcpy(bufenvio,nome);
    send(meusocket,bufenvio,strlen(bufenvio),0);		// enviando para o servidor
    free(bufenvio);					//limpando o buffer

    resposta();                                       //resposta do servidor
    if(strcmp(resposta(),"SENHA")==0)
    
    

    printf("informe a senha ");
    fgets(senha,6,stdin);

    tamanho=strlen(senha);				// tamanho da senha
    bufenvio=(char*)malloc(senha);			// alocando no buffer a senha
    strcpy(bufenvio,senha);
    send(meusocket,bufenvio,strlen(senha),0);		//enviando a senha para o servidor
    free(bufenvio);					//limpando o buffer

    resposta();
    fputs(resposta());                           //mostra na tela o que o servidor mandou
    
    if(strcmp(resposta(),msgrecebida)==0){                   // duvida se comparo assim
	//if(resposta()=="SEJA BEM VINDO");                         OU ASSIM

	    printf("usuario tal conectado ao servidor");
	
	
	 
    }
    else
	printf("nome do usuario ou senha erradas");
	close(meusocket);
	exit(4);

//  Aqui viria as opcoes que o cliente faria tipo download upload ou ver arquivos

}


void cadastrar(){
    
    char menrecebida[31]="CADASTRO EFETUADO COM SUCESSO";    // nao tenho certeza se usarei
    do{
    printf("**********CADASTRO FTP**********\n\n\n");
    printf("informe o usuario ");
    fgets(nome,12,stdin);

    tamanho=strlen(nome);                               //tamanho da string do nome
    bufenvio=(char*)malloc(tamanho);			//alocando no buffer o nome
    strcpy(bufenvio,nome);
    send(meusocket,bufenvio,strlen(bufenvio),0);		// enviando para o servidor
    free(bufenvio);					//limpando o buffer


    printf("informe a senha ");
    fgets(senha,6,stdin);

    tamanho=strlen(senha);				// tamanho da senha
    bufenvio=(char*)malloc(senha);			// alocando no buffer a senha
    strcpy(bufenvio,senha);
    send(meusocket,bufenvio,strlen(senha),0);		//enviando a senha para o servidor
    free(bufenvio);					//limpando o buffer


    resposta();                           //respota do servidor
    fputs(resposta());                  //amostra na tela do usuario o que o servidor mandou
	
    }while(strcmp(resposta(),menrecebida)==0);               //ficar no cadastro ate receber a resṕosta certa
    //ou while(resposta()=="CADASTRO EFETUADO COM SUCESSO"); // to na duvida se faço assim ou com strcmp;

    //apos isso volta para o menu para poder fazer o login
    
}



char*resposta(){


    memset(buffer,0,1024);              //limpar o buffer
    bytes=recv(sock,buffer,1024,0);     // recebendo dados provavelmente char que esta dentro do buffer
    if(!bytes){
	close(meusocket);
	printf("erro");
    }
    return buffer;
    
}





	 /*   Acho que pode ser legal os dados para o cliente ja esta predefinido como porta e ip de conexao
    para evitar q ele fique tentando acessar outros ips e de erro no programa ou vai que ele se esquece dos dados
    entendeu. penso em clica no executavel abre a janela e pronto login senha
    entao cara meu pensamento aqui é no login o a pessoa se conecta rapidamente para validar os dados
    envia seus dados e apos uma checagem la no servidor recebera uma mensagem
    se receber mensagem x tipo usuario ou senha errados ele desconecta. caso contrario receberia seja bem vindo
    usuario tal. Apos isso as opcoes estaria liberadas entendeu;

    Obs coloque suas variaveis bem intuitivas namoral vamos deixar bem simples nossa linguagem



    */

    




