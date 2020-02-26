#import "RemovableDriveManager.hpp"


@implementation IInstanceCheckMessager

-(instancetype) init
{
	self = [super init];
	if(self)
	{        
	}
	return self;
}

-(void)send_message
{
	[[NSDistributedNotificationCenter defaultCenter] postNotificationName:@"OtherPrusaSlicerTerminating" object:nil];
}

-(void)register_for_message
{
	[[NSDistributedNotificationCenter defaultCenter] addObserver:self selector:@selector(someNotificationUpdate:) name:@"OtherPrusaSlicerTerminating" object:nil];
}

-(void)message_update:(NSNotification *)note
{
	NSLog(@"got message");
}
/*
[[NSDistributedNotificationCenter defaultCenter] postNotificationName:@"HelloFromProcessOne" object:nil]
[[NSDistributedNotificationCenter defaultCenter] postNotificationName:@"HelloFromProcessOne" object:nil userInfo:[NSDictionary dictionaryWithObject:@"some info here" forKey:@"data"]]

[[NSDistributedNotificationCenter defaultCenter] addObserver:self selector:@selector(someNotificationUpdate:) name:@"HelloFromProcessOne" object:nil]
*/

namespace Slic3r {
InstanceCheckMac::InstanceCheckMac(){
	m_mssngr = [[InstanceCheckMessager alloc] init];
}
InstanceCheckMac::~InstanceCheckMac(){
	if(m_mssngr)
	{
		[m_mssngr release];
	}
}
void InstanceCheckMac::send_message(const td::string msg)
{
	if(m_mssngr)
	{
		[m_mssngr send_message];
	}
}
void InstanceCheckMac::register_for_messages()
{
	f(m_mssngr)
	{
		[m_mssngr register_for_messages];
	}
}//namespace Slicer