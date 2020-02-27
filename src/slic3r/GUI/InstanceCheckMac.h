#import <Cocoa/Cocoa.h>

@interface InstanceCheckMesseger : NSObject

-(instancetype) init;
-(void) send_message;
-(void) register_for_messages;
- (void)message_update:(NSNotification *)note;
@end