#include <stdio.h>
#include <WF/CHTTP.h>

int main(int argc, const char * argv[])
{
    struct HTTPState* state = malloc(sizeof(struct HTTPState));
    state->domain = HTTP_IPV4(5, 39, 62, 5);

    return 0;
}
