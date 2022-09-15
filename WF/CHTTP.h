#pragma once

#include <sys/cdefs.h>

__BEGIN_DECLS

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

typedef int32_t http_t;

struct HTTPState
{
    http_t sock;
    
    uint32_t domain;
    struct sockaddr* addr;
    socklen_t addr_len;
    
    uint8_t connected;
    int32_t status;
};

// opens a new socket
http_t http_socket(struct HTTPState* state);

// Cleans up the state of the struct, and closes the connection
void http_clean(struct HTTPState* state);

// returns 0 if size is insufficent, the len of bytes if successful, or -1 is unsuccessful.
// returns -1, or the size inside of the int32_t
ssize_t http_recv(http_t sock, uint8_t* buf, size_t len);
// sends to the socket the buffer with the length
// returns 0 if size is insufficent, the bytes read if successful, or -1 if unsuccessful.
ssize_t http_send(http_t sock, uint8_t* buf, size_t len);

#define HTTP_VERSION_1 "HTTP/1.1"
#define HTTP_GET "GET"
#define HTTP_POST "POST"

struct CHTTP_IPV4 { uint32_t a; uint16_t b; uint8_t c, d; };

#define HTTP_IPV4(A, B, C, D) ((uint32_t)(16777216 * A) + (uint32_t)(65536 * B) + (uint32_t)(256 * C) + (uint32_t)(D * 1))

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

__END_DECLS
