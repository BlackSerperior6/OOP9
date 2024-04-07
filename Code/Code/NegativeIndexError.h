#pragma once
#include "WrongIndexError.h"

class NegativeIndexError :public WrongIndexError
{
public:
	NegativeIndexError() { msg += "index is negative"; }

	~NegativeIndexError() {}
};

