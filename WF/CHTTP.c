#include "CHTTP.h"

http_t http_socket(struct CHTTPState* state)
{
    if (state == NULL) return -1;
    
    state->sock = socket(state->domain, SOCK_STREAM, AF_INET);
    puts("CHTTP: checking socket..");
    
    if (state->sock == -1)
    {
        perror("socket");
        return errno;
    }
   
    state->addr = (struct sockaddr_in*)malloc(sizeof(struct sockaddr));
    state->addr->sin_family = AF_INET;
    state->addr->sin_port = htons(8080);
    state->addr_len = sizeof(state->addr);
    
    if (connect(state->sock, (struct sockaddr*)state->addr, state->addr_len) == -1)
    {
        perror("connect");
        close(state->sock);
        return errno;
    }
    
    puts("CHTTP: connected.");
    
    state->status = 0;
    state->connected = 1;
    
    return state->sock;
}

void http_clean(struct CHTTPState* state)
{
    if (state != NULL)
    {
        state->status = close(state->sock);
        if (state->status == -1)
        {
            perror("close");
            
            free(state->addr);
        
            state->addr_len = 0;
            state->connected = 0;
            
            printf("%s %p\n", "CHTTP: cleaned up CHTTPState at: ", state);
        }
    }
}

ssize_t http_send(http_t sock, uint8_t* buf, size_t len)
{
    if (len < 1) return 0;
    
    if (buf != NULL)
    {
        ssize_t err = send(sock, buf, len, 0);
        if (err == -1)
        {
            perror("send");
            return errno;
        }
        
        return err;
    }
    
    return ENOBUFS;
}

ssize_t http_recv(http_t sock, uint8_t* buf, size_t len)
{
    if (len < 1) return 0;
    
    if (buf != NULL)
    {
        ssize_t err = recv(sock, buf, len, 0);
        if (err == -1)
        {
            perror("recv");
            return errno;
        }
        
        return err;
    }
    
    return ENOBUFS;
}
