#include "InstanceCheck.hpp"


#include <iostream>

//onst UINT messageId =  RegisterWindowMessage(L"PrusaSlicer");
//catching message from another instance
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	TCHAR lpClassName[1000];
	GetClassName(hWnd, lpClassName, 100);
	switch (message)
	{
	case WM_COPYDATA:
	{
		COPYDATASTRUCT* copy_data_structure = { 0 };
		copy_data_structure = (COPYDATASTRUCT*)lParam;

		LPCWSTR arguments = (LPCWSTR)copy_data_structure->lpData;
		
	}
	break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}


BOOL CALLBACK EnumWindowsProc(_In_ HWND   hwnd, _In_ LPARAM lParam) {
	//checks for other instances of prusaslicer, if found brings it to front and return false to stop enumeration and quit this instance
	//search is done by classname(wxWindowNR is wxwidgets thing, so probably not unique) and name in window upper panel
	//other option would be do a mutex and check for its existence
	TCHAR wndText[1000];
	TCHAR className[1000];
	GetClassName(hwnd, className, 1000);
	GetWindowText(hwnd, wndText, 1000);
	std::wstring classNameString(className);
	std::wstring wndTextString(wndText);
	if (wndTextString.find(L"PrusaSlicer") != std::wstring::npos && classNameString == L"wxWindowNR") {
		std::wcout << L"found " << wndTextString << std::endl;
		ShowWindow(hwnd, SW_SHOWMAXIMIZED);
		SetForegroundWindow(hwnd);

		return false;
	}
	return true;
}

namespace Slic3r {
InstanceCheck::InstanceCheck() {}
InstanceCheck::~InstanceCheck(){}

bool InstanceCheck::check_with_message() const
{
	if (!EnumWindows(EnumWindowsProc, 0)) {
		printf("Another instance of PrusaSlicer is already running.\n");
		LPWSTR command_line_args = GetCommandLine();
		HWND hwndListener;
		if ((hwndListener = FindWindow(NULL, L"PrusaSlicer_listener_window")) != NULL)
		{
			send_message(hwndListener);
		}else
		{
			printf("Listener window not found - teminating without sent info.\n");
		}
		return true;
	}

	create_listener_window();

	return false;
}

void InstanceCheck::create_listener_window() const
{
	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.hInstance = reinterpret_cast<HINSTANCE>(GetModuleHandle(0));
	wndClass.lpfnWndProc = reinterpret_cast<WNDPROC>(WndProc);//this is callback
	wndClass.lpszClassName = L"PrusaSlicer_single_instance_listener_class";
	if (!RegisterClassEx(&wndClass))
	{
		DWORD err = GetLastError();
		return;
	}

	HWND hWnd = CreateWindowEx(
		0,//WS_EX_NOACTIVATE,
		L"PrusaSlicer_single_instance_listener_class",
		L"PrusaSlicer_listener_window",
		WS_OVERLAPPEDWINDOW,//WS_DISABLED, // style
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL, NULL,
		GetModuleHandle(NULL),
		NULL);
	if (hWnd == NULL)
	{
		DWORD err = GetLastError();
	}
	else
	{
		//ShowWindow(hWnd, SW_SHOWNORMAL);
		UpdateWindow(hWnd);
	}
}

void InstanceCheck::send_message(const HWND hwnd) const
{
	LPWSTR command_line_args = GetCommandLine();

	//Create a COPYDATASTRUCT to send the information
	//cbData represents the size of the information we want to send.
	//lpData represents the information we want to send.
	//dwData is an ID defined by us(this is a type of ID different than WM_COPYDATA).
	COPYDATASTRUCT data_to_send = { 0 };
	//data_to_send.dwData = messageId;
	data_to_send.cbData = (wcslen(command_line_args) + 1);
	data_to_send.lpData = command_line_args;

	SendMessage(hwnd, WM_COPYDATA, 0, (LPARAM)&data_to_send);
}

void InstanceCheck::handle_message(const std::wstring message) const
{
	std::wcout << L"Got message " << message << std::endl;
}
} // namespace Slic3r