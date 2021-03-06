#pragma once

#include <string>
#include <vector>

#include "Engine/Math/Vectors.hpp"

class WindowMessageCallback_Base;

typedef void (*WindowMessage_Callback)(uint messageCode, ulonglong wparam, longlong lparam);



class Window
{
public:
	// Composition
	Window();
	~Window();

	void Initialize(const std::string& name, int width, int height);
	void Initialize(const std::string& name, int height, int aspectW, int aspectH); // Aspect is separated to avoid float error
		void CreateWindowsWindow();
	void Destroy();
		void RemoveAllCallbacks();
		void RemoveSelfFromWindowList();


	// WndProc
	bool RunWndProc(uint messageCode, ulonglong wparam, longlong lparam); // return == was the message was consumed


	// Callbacks
	// C Functions
	inline void RegisterCallback(WindowMessage_Callback callback);
	inline void UnregisterCallback(WindowMessage_Callback callback);

	// Member Functions
	template<typename T, typename DummyCallback>
	void RegisterMemberCallback(T* user, DummyCallback callback);

	template<typename T, typename DummyCallback>
	void UnregisterMemberCallback(T* user, DummyCallback callback);
	

	// Handle
	void* GetHandle() const; // Safely castable to HWND


	// Queries
	float GetAspect() const;
	ivec2 GetDimensions() const;
	ivec2 GetCenter() const;


	// Name
	void SetName(const std::string& name);



public:
	// Statics
	static const std::vector<Window*>& GetAllWindows(); // Only designed to be used in the wnd proc dispatch



private:
	void*		m_handle;

	std::string m_name;
	ivec2		m_dimensions;

	std::vector<WindowMessageCallback_Base*> m_callbacks;



private:
	static std::vector<Window*> s_allWindows;
};




#include "Engine/Rendering/Window.ii.hpp"