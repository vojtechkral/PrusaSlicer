#ifndef slic3r_InstanceCheck_hpp_
#define slic3r_InstanceCheck_hpp_

#if _WIN32
#include <windows.h>
#endif

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
#if _WIN32
#else
	void bring_this_instance_forward() const;
	static void sig_handler(int signo);
#endif
private:
	InstanceCheck();
	void create_listener_window() const;
#if _WIN32
	void send_message(const HWND hwnd) const;
#else
	int get_lock() const;
	std::string get_pid_string_by_name(std::string procName) const;
	void send_message(const int pid) const;

#endif
	
};


} // namespace Slic3r
#endif // slic3r_InstanceCheck_hpp_