#import <Foundation/Foundation.h>
#import <WF/WF.h>

int main(int argc, const char * argv[]) {

    @autoreleasepool {
        struct HTTPHeader* hdr = malloc(sizeof(struct HTTPHeader));
        hdr->version = @"HTTP/1.1";
        hdr->status_code = 200;
        hdr->request_type = @"GET";
        hdr->header_fields = @{ @"Content-Type": @"text/x-c" };
        
        NSURL* url = [[NSURL alloc] initWithString:@"https://cvs-award.mtxserv.com/cvs/kernel/src/sys/stack_protector.c"];
        HTTPObject* obj = [[HTTPObject new] initWithHeader:hdr :url];
        NSLog(@"%@", [obj getBody]);
        
        free(hdr);
    }
    return 0;
}
