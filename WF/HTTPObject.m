#import "HTTPObject.h"

@implementation HTTPObject
-(id) initWithHeader:(struct HTTPHeader*)hdr :(NSURL*)url
{
    if ([super init])
    {
        self->_h_hdr = hdr;
        self->_h_text = [HTTPObjectFactory sendWithHeader:self :url];
        
        return self;
    }

    return nil;
}

-(struct HTTPHeader*) getHeader
{
    return self->_h_hdr;
}

-(NSString*) getBody
{
    return self->_h_text;
}

@end

@implementation HTTPObjectFactory
+(NSString*) sendWithHeader:(HTTPObject*)hdr :(NSURL*)url
{
    if (hdr == nil) return nil;
    if (url == nil) return nil;
    
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc] init];
    [request setHTTPMethod:[hdr h_hdr]->request_type];
    [request setURL:url];
    
    NSError* error = nil;
    NSHTTPURLResponse *responseCode = nil;
    NSData *oResponseData = [NSURLConnection sendSynchronousRequest:request returningResponse:&responseCode error:&error];

    if([responseCode statusCode] == ([hdr h_hdr]->status_code)){
        return [[NSString alloc] initWithData:oResponseData encoding:NSUTF8StringEncoding];
    }
    
    NSLog(@"Error getting %@, HTTP status code %li", url, [responseCode statusCode]);
    return nil;
}

@end
