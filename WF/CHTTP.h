#pragma once

#include <sys/cdefs.h>

__BEGIN_DECLS

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef int32_t http_t;

struct CHTTPState
{
    http_t sock;
    
    uint8_t connected;
    int32_t status;
    
    uint32_t domain;
    socklen_t addr_len;
    struct sockaddr_in* addr;
};

#define HTTP_VERSION_1 "HTTP/1.1"
#define HTTP_GET "GET"
#define HTTP_POST "POST"

#define HTTP_IPV4(A, B, C, D) ((uint32_t)(sizeof(uint32_t) * A) + (uint16_t)(sizeof(uint16_t) * B) + (uint8_t)(sizeof(uint8_t) * C) + (uint8_t)(D * 1))

struct CHTTPHeader
{
    int32_t h_status;
    
    char* h_version;
    char* h_request_type;
    char* h_header_fields[];
};

typedef struct CHTTP
{
    struct CHTTPHeader* c_hdr;
    char** c_body;
} CHTTP;

// opens a new socket
http_t http_socket(struct CHTTPState* state);

// Cleans up the state of the struct, and closes the connection
void http_clean(struct CHTTPState* state);

// returns 0 if size is insufficent, the len of bytes if successful, or -1 is unsuccessful.
// returns -1, or the size inside of the int32_t
ssize_t http_recv(http_t sock, uint8_t* buf, size_t len);
// sends to the socket the buffer with the length
// returns 0 if size is insufficent, the bytes read if successful, or -1 if unsuccessful.
ssize_t http_send(http_t sock, uint8_t* buf, size_t len);

__END_DECLS
