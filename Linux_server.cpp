#include <bits/stdc++.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;
const int maxn = 200;
void* wr(void *arg)
{
    char buffer[maxn]={0};
    int sock = *(int*)arg;
    while(1)
    {
        read(sock,buffer,maxn);
        if(strlen(buffer))
        {
            printf("receive a string: %s\n",buffer);
            memset(buffer,0,sizeof(buffer));
        }
    }
}

int main()
{

    int serv_sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    //serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(12314);
    bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    struct sockaddr_in clnt_addr;
    char buffer[200]="";
    listen(serv_sock,20);
    socklen_t tmp = sizeof(clnt_addr);
    int clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr,&tmp);
    pthread_t id = 0;
    pthread_create(&id,NULL,wr,(void*)&clnt_sock);

    while(1)
    {
        printf("\ninput a string:");
        scanf("%s",buffer);
        write(clnt_sock,buffer,maxn);
        memset(buffer,0,sizeof(buffer));
    }
    close(clnt_sock);
    close(serv_sock);
    return 0;
}
