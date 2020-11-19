#pragma once
#include "MStd.h"
class MBaseObject
{
public:
	virtual bool		Init() = 0;
	virtual bool		Frame() = 0;
	virtual bool		Render() = 0;
	virtual bool		Release() = 0;
public:
	MBaseObject() {}
	virtual ~MBaseObject() {}
};

