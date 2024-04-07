#pragma once
#include "BasicError.h"

class WrongIndexError : public BasicError
{
public:
	WrongIndexError() { msg = "Error index: "; }

	virtual ~WrongIndexError() {}
};

