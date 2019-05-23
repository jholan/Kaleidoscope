#pragma once



class Game
{
public:
	// Composition
	Game() {};
	~Game() {};

	void Initialize();
	void Destroy();


	// Update
	void Update(float deltaSeconds);
	void Render() const;



private:
};