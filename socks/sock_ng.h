#define BACKLOG 5
#define TRUE    1
#define FALSE   0
int sock_create(int * sockfd, struct sockaddr_in * host, unsigned short int port){
  *sockfd = socket(PF_INET, SOCK_STREAM, 0);
   int yes = 1;

  if(sockfd < 0){
    fatal("Creating a socket");
  }
  if(setsockopt(*sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0){
    fatal("on sock_create() calling setsockopt()");
  }

  host->sin_family = AF_INET;
  host->sin_port = htons(port);
  host->sin_addr.s_addr = htonl(INADDR_ANY);
  memset(&(host->sin_zero), '\0', 8);
	
  if(bind(*sockfd, (struct sockaddr *)host, sizeof(struct sockaddr_in)) < 0){
	fatal("binding");
  }

  if(listen(*sockfd, BACKLOG)){
	fatal("Listening from socket");
  }
  return sizeof(struct sockaddr_in);
}

