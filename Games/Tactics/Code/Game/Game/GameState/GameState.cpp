#include "Game/Game/GameState/GameState.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
GameState::GameState() 
{

}


GameState::~GameState() 
{

}



// -----------------------------------------------------------------
// Name
// -----------------------------------------------------------------
void GameState::SetName(const std::string& name)
{
	m_name = name;
}


const std::string& GameState::GetName() const
{
	return m_name;
}



// -----------------------------------------------------------------
// Owner
// -----------------------------------------------------------------
void GameState::SetOwner(Game* owner)
{
	m_owner = owner;
}


Game* GameState::GetOwner() const
{
	return m_owner;
}
