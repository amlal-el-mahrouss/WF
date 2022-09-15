#include "CHTTP.h"

http_t http_socket(struct HTTPState* state)
{
    if (state == NULL) return -1;
    
    state->sock = socket(state->domain, SOCK_STREAM, PF_INET);
    if (state->sock == -1) return errno;
   
    if (connect(state->sock, state->addr, state->addr_len) == -1)
    {
        close(state->sock);
        return errno;
    }
    
    state->status = 0;
    state->connected = 1;
    
    return state->sock;
}

void http_clean(struct HTTPState* state)
{
    if (state != NULL)
    {
        close(state->sock);
        free(state->addr);
        
        state->status = 0xFFFF;
        state->addr_len = 0;
        state->connected = 0;
        
        printf("%s %p\n", "Cleaned up HTTPState at: ", state);
    }
}

ssize_t http_send(http_t sock, uint8_t* buf, size_t len)
{
    if (len < 1) return 0;
    
    if (buf != NULL)
        return send(sock, buf, len, 0);
    
    return ENOBUFS;
}

ssize_t http_recv(http_t sock, uint8_t* buf, size_t len)
{
    if (len < 1) return 0;
    
    if (buf != NULL)
        return recv(sock, buf, len, 0);
    
    return ENOBUFS;
}
