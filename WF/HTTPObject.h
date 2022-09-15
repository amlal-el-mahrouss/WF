#import <Foundation/Foundation.h>

typedef struct HTTPHeader
{
    NSInteger status_code;
    
    NSString* _Nonnull  version;
    NSString* _Nonnull request_type;
    NSDictionary<NSString*, NSString*>* _Nonnull header_fields;
} HTTPHeader;

typedef struct HTTP
{
    struct HTTPHeader* h_hdr;
    NSString* h_body;
} HTTP;

NS_ASSUME_NONNULL_BEGIN

@interface HTTPObject : NSObject
@property struct HTTPHeader* h_hdr;
@property NSString* h_text;

-(id) initWithHeader:(struct HTTPHeader*)hdr :(NSURL*)url;
-(struct HTTPHeader*) getHeader;

-(NSString*) getBody;
@end

@interface HTTPObjectFactory : NSObject
+(NSString*) sendWithHeader:(HTTPObject*)hdr :(NSURL*)url;
@end

NS_ASSUME_NONNULL_END

#ifdef __WF_DEBUG__
#define WebLog(STR) NSLog("\n%@", STR)
#else
#define WebLog(STR)
#endif
