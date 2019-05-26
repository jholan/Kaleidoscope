#include "Engine/Rendering/Window.hpp"

#include "Engine/Core/WindowsLean.hpp"



// -----------------------------------------------------------------
// WndProc
// -----------------------------------------------------------------
LRESULT CALLBACK WndProcDispatch(HWND hwnd, UINT messageCode, WPARAM wparam, LPARAM lparam)
{
	// Loop all of our windows, if their hwnd matches the hwnd we got run their wnd proc
	const std::vector<Window*>& allWindows = Window::GetAllWindows();
	for (int i = 0; i < (int)allWindows.size(); ++i)
	{
		Window* window = allWindows[i];

		if (hwnd == window->GetHandle())
		{
			window->RunWndProc(messageCode, (ulonglong)wparam, (longlong)lparam);
			break;
		}
	}

	return DefWindowProc(hwnd, messageCode, wparam, lparam);
}



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
Window::Window()
{

}


Window::~Window()
{
	
}


void Window::Initialize(const std::string& name, int width, int height)
{
	// Cache values
	m_name = name;
	m_dimensions = ivec2(width, height);

	// Create the windows window
	CreateWindowsWindow();

	// Add a reference to the list of windows for proper callback processing
	s_allWindows.push_back(this);
}


void Window::CreateWindowsWindow()
{
	// Window style flags
	// If we want full screen support these flags will change
	const DWORD windowStyleFlags = WS_CAPTION | WS_BORDER | WS_THICKFRAME | WS_SYSMENU | WS_OVERLAPPED;
	const DWORD windowStyleExFlags = WS_EX_APPWINDOW;


	// Define a window style/class
	WNDCLASSEX windowClassDescription;
	memset(&windowClassDescription, 0, sizeof(windowClassDescription));
	windowClassDescription.cbSize = sizeof(windowClassDescription);
	windowClassDescription.style = CS_OWNDC; // Redraw on move, request own Display Context
	windowClassDescription.lpfnWndProc = WndProcDispatch; // Register our Windows message-handling function
	windowClassDescription.hInstance = GetModuleHandle(NULL);
	windowClassDescription.hIcon = NULL;
	windowClassDescription.hCursor = NULL;
	windowClassDescription.lpszClassName = TEXT("Simple Window Class");
	RegisterClassEx(&windowClassDescription);


	// Get desktop rect
	RECT desktopRect;
	HWND desktopWindowHandle = GetDesktopWindow();
	GetClientRect(desktopWindowHandle, &desktopRect);
	float desktopWidth = (float)(desktopRect.right - desktopRect.left);
	float desktopHeight = (float)(desktopRect.bottom - desktopRect.top);


	// Get client rect
	float clientWidth = (float)m_dimensions.x;
	float clientHeight = (float)m_dimensions.y;

	float remainingWidth = desktopWidth - clientWidth;
	float remainingHeight = desktopHeight - clientHeight;

	float leftPadding = remainingWidth * 0.5f;
	float topPadding = remainingHeight * 0.5f;

	RECT clientRect;
	clientRect.left = (int)leftPadding;
	clientRect.right = clientRect.left + (int)clientWidth;
	clientRect.top = (int)topPadding;
	clientRect.bottom = clientRect.top + (int)clientHeight;


	// Get window rect
	RECT windowRect = clientRect; // Start with client rect and then adjust
	AdjustWindowRectEx(&windowRect, windowStyleFlags, FALSE, windowStyleExFlags);


	// Convert name to wide chars
	WCHAR windowTitle[1024];
	MultiByteToWideChar(GetACP(), 0, m_name.c_str(), -1, windowTitle, (int)m_name.size() + 1);


	// FINALLY CREATE THIS P.O.S.
	HWND hwnd = CreateWindowEx(
								windowStyleExFlags,
								windowClassDescription.lpszClassName,
								windowTitle,
								windowStyleFlags,
								windowRect.left,
								windowRect.top,
								windowRect.right - windowRect.left,
								windowRect.bottom - windowRect.top,
								NULL,
								NULL,
								GetModuleHandle(NULL),
								NULL
								);
	m_handle = (void*)hwnd;


	// Show the window and make it the front most window
	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);


	// Set the cursor to the default arrow
	HCURSOR cursor = LoadCursor(NULL, IDC_ARROW);
	SetCursor(cursor);
}


void Window::Initialize(const std::string& name, int height, int aspectW, int aspectH)
{
	// NOTE: We are using stupid aspect here which could result in float error
	//			if window size isn't exact change this
	float aspect = (float)aspectW / (float)aspectH;
	int width = (int)(height * aspect);

	Initialize(name, width, height);
}


void Window::Destroy()
{
	RemoveAllCallbacks();
	RemoveSelfFromWindowList();
}


void Window::RemoveAllCallbacks()
{
	// Clean up all callbacks
	for (int i = 0; i < (int)m_callbacks.size(); ++i)
	{
		delete m_callbacks[i];
		m_callbacks[i] = nullptr;
	}
	m_callbacks.clear();
}


void Window::RemoveSelfFromWindowList()
{
	for (int i = 0; i < (int)s_allWindows.size(); ++i)
	{
		if (s_allWindows[i] == this)
		{
			s_allWindows.erase(s_allWindows.begin() + i);
		}
	}
}



// -----------------------------------------------------------------
// Window specific WndProc
// -----------------------------------------------------------------
bool Window::RunWndProc(uint messageCode, ulonglong wparam, longlong lparam)
{
	for (int i = 0; i < (int)m_callbacks.size(); ++i)
	{
		m_callbacks[i]->Call(messageCode, wparam, lparam);
	}


	return false;
}



// -----------------------------------------------------------------
// Callbacks -> Window.ii.hpp
// -----------------------------------------------------------------




// -----------------------------------------------------------------
// Handle
// -----------------------------------------------------------------
void* Window::GetHandle() const
{
	return m_handle;
}



// -----------------------------------------------------------------
// Queries
// -----------------------------------------------------------------
float Window::GetAspect() const
{
	float aspect = (float)m_dimensions.x / (float)m_dimensions.y;
	return aspect;
}


ivec2 Window::GetDimensions() const
{
	return m_dimensions;
}


ivec2 Window::GetCenter() const
{
	vec2 floatCenter = vec2((float)m_dimensions.x, (float)m_dimensions.y) * 0.5f;
	ivec2 center = ivec2((int)floatCenter.x, (int)floatCenter.y);
	return center;
}



// -----------------------------------------------------------------
// Name
// -----------------------------------------------------------------
void Window::SetName(const std::string& name)
{
	// Cache new name
	m_name = name;

	// Do windows things
	WCHAR windowTitle[1024];
	MultiByteToWideChar(GetACP(), 0, m_name.c_str(), -1, windowTitle, (int)m_name.size() + 1);
	SetWindowText((HWND)m_handle, windowTitle);
}



// -----------------------------------------------------------------
// Statics
// -----------------------------------------------------------------
const std::vector<Window*>& Window::GetAllWindows()
{
	return s_allWindows;
}


std::vector<Window*> Window::s_allWindows;