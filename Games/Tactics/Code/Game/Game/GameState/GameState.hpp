#pragma once

#include <string>

class Game;



class GameState
{
public:
	// Composition
	GameState();
	~GameState();

	virtual void Initialize(Game* owner) = 0;
	virtual void Destroy() = 0;


	// Update
	virtual void Update(float deltaSeconds) = 0;
	virtual void Render() const = 0;


	// Name
	void SetName(const std::string& name);
	const std::string& GetName() const;


	// Owner
	void SetOwner(Game* owner);
	Game* GetOwner() const;



private:
	Game* m_owner = nullptr;

	std::string m_name;
};