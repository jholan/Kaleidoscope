#pragma once



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



private:
	bool m_isQuitting = false;
};