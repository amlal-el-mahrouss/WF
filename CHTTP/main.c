#include <stdio.h>
#include <WF/CHTTP.h>

int main(int argc, const char * argv[])
{
    struct CHTTPState* state = malloc(sizeof(struct CHTTPState));
    state->domain = HTTP_IPV4(5, 39, 62, 5);
    http_socket(state);

    return 0;
}
