#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
using namespace std;
const int maxn = 500;

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
    struct sockaddr_in clnt_addr = {0};
    memset(&clnt_addr,0,sizeof(clnt_addr ));
    clnt_addr.sin_family = AF_INET;
    //clnt_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    clnt_addr.sin_addr.s_addr = inet_addr("119.23.255.60");
    clnt_addr.sin_port = htons(12314);

    char bufsend[maxn] = {0};
    char bufrecv[maxn] = {0};

    int serv_sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    connect(serv_sock,(struct sockaddr*)&clnt_addr,sizeof(clnt_addr));
    pthread_t tmp = 0;
    pthread_create(&tmp,NULL,wr,(void*)&serv_sock);

    while(1)
    {
        printf("\ninput a string:");
        scanf("%s",bufsend);
        write(serv_sock,bufsend,sizeof(bufsend));
        memset(bufsend,0,sizeof(bufsend));
    }
    close(serv_sock);
    return 0;
}
