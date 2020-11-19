#pragma once
#include <MCore.h>

class Sample : public MCore
{
public:
	virtual bool Frame() override;
	virtual bool Render() override;
};