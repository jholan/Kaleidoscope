#pragma once

#include "Game/Game/GameState/GameState.hpp"



class LoadState : public GameState
{
public:
	// Composition
	LoadState();
	~LoadState();

	virtual void Initialize(Game* owner) override;
	virtual void Destroy() override;


	// Update
	virtual void Update(float deltaSeconds) override;
	virtual void Render() const override;



private:
};