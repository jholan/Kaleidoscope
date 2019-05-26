#pragma once

#include "Engine/Core/Types.hpp"



class App
{
public:
	// Composition
	App() {};
	~App() {};

	void Initialize();
	void Destroy();


	// Update
	void RunInternalLoop();
		void RunFrame();
			void RunMessagePump();
			void Update();
			void Render() const;


	// Quit
	void Quit();
	bool IsQuitting() const;


	// Window Callbacks
	void HandleXOut(uint msg, ulonglong wparam, longlong lparam);



private:
	bool m_isQuitting = false;
};