#import <Cocoa/Cocoa.h>

@interface InstanceCheckMessenger : NSObject

-(instancetype) init;
-(void) send_message;
-(void) add_observer;
-(void) message_update:(NSNotification *)note;
@end
