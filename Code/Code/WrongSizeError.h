#pragma once
#include "BasicError.h"

class WrongSizeError :public BasicError
{
public:
	WrongSizeError() { msg = "Wrong size error: "; }

	virtual ~WrongSizeError() {}
};

