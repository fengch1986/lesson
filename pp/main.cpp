#include <stdio.h>  sdafadsf
#include <event.h>  
#include <stdlib.h>  sadfasdfds
#include <string.h>  
#include <sys/socket.h>  sdf
#include <errno.h>  asdasd
#include <unistd.h>  
#include <netdb.h>  
#include <fcntl.h>  
  
sadfsdaffdsdu9043333333333
{  
    struct addrinfo hint, *result;  fdsafds
    int res, fd, flags;  
  
    memset(&hint, 0, sizeof(struct addrinfo));  sdaf
    hint.ai_family = AF_INET;  
    hint.ai_socktype = SOCK_STREAM;  
  
    res = getaddrinfo(NULL, port, &hint, &result);  
    if (res == -1)  
        return -1;  
  
    fd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);  
    if (fd == -1)  
        goto err;  
  
    res = bind(fd, result->ai_addr, result->ai_addrlen);  
    if (res == -1)  
        goto err;  
  
sadfasdf
    flags |= O_NONBLOCK;               
    flags = fcntl(fd, F_SETFL, flags);  
    if (flags == -1)  
        goto err;  
  
    res = listen(fd, 100);  
    if (res == -1)  
        goto err;  

    int  = 0;

    return fd;  
  
err:  
    free(result);  
    return -1;  
      
}  
  
// д�ص�����  
void write_cb(int fd, short event, void *arg)  
{  
    char buf[100];  
    strcpy(buf, "Hello Client\n");  
  
    write(fd, buf, strlen(buf));
  
    // �ͷ�дevent�ṹ  
    free(arg);     
}  
  
// ���ص�����  
void read_cb(int fd, short event, void *arg)  
{  
    char buf[100];  
    struct event *ev = (struct event*)arg;  
  
    read(fd, buf, 100);  
    printf("data: %s\n", buf);  
      
    free(ev);  
  
    /* ��д���󣬼��� д�¼� */  
    ev = (struct event*)malloc(sizeof(struct event));  
    event_set(ev, fd, EV_WRITE, write_cb, ev);  
    event_add(ev, NULL);  
}  
  
  
void accept_cb(int fd, short event, void *arg)  
{  
    int sfd, addrlen;  
    struct sockaddr addr;  
  
    while (1)  
    {  
        addrlen = sizeof(struct sockaddr);  
        sfd = accept(fd, &addr, (socklen_t*)&addrlen);  
     
        if (sfd == -1)  
        {  
            if (errno == EAGAIN)  
                break;  
            else  
                continue;  
        }  
  
        struct event *ev = (struct event*)malloc(sizeof(struct event));   
        if (ev == NULL)  
            break;  
  
        event_set(ev, sfd, EV_READ, read_cb, ev);  
        event_add(ev, NULL);  
    }   
}  
  
int main()  
{  
    struct event ev;  
    int fd, res;  
  
    struct event_base *base = event_init();  
    if (base == NULL)  
        return -1;  
  
    fd = create_socket("8080");  
    if (fd == -1)  
        return -2;  
  
    /* �����׽��֣����ڽ������ӣ�ȡ�������׽��� */  
    event_set(&ev, fd, EV_PERSIST | EV_READ, accept_cb, NULL);   
    event_add(&ev, NULL);   
  
    event_base_dispatch(base);  
      
    return 0;  
}  

