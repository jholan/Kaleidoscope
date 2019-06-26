#include "Game/Game/GameState/LoadState.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
LoadState::LoadState()
{

}


LoadState::~LoadState()
{

}


void LoadState::Initialize(Game* owner)
{
	SetOwner(owner);
	SetName("Load State");
}


void LoadState::Destroy()
{
	SetOwner(nullptr);
	SetName("");
}



// -----------------------------------------------------------------
// Update
// -----------------------------------------------------------------
void LoadState::Update(float deltaSeconds)
{
	// Load All Database Files

}


void LoadState::Render() const
{

}
