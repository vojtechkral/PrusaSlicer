#ifndef slic3r_InstanceCheck_hpp_
#define slic3r_InstanceCheck_hpp_

//windows
#include <windows.h>
#include <string>


namespace Slic3r {

class InstanceCheck
{
public:
	static InstanceCheck& instance_check()
	{
		static InstanceCheck instance;
		return instance;
	}
	InstanceCheck(InstanceCheck const&) = delete;
	void operator=(InstanceCheck const&) = delete;
	~InstanceCheck();
	//checks for other instances of prusaslicer. If found, sends message and returns true. If not found, creates invisible window for listening and returns false
	bool check_with_message() const;
	void handle_message(const std::string message) const;
private:
	InstanceCheck();
	void create_listener_window() const;
	void send_message(const HWND hwnd) const;
	
};


} // namespace Slic3r
#endif // slic3r_InstanceCheck_hpp_