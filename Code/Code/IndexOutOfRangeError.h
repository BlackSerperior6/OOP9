#pragma once
#include "WrongIndexError.h"

class IndexOutOfRangeError :public WrongIndexError
{
public:
	IndexOutOfRangeError() { msg += "index is more than the size of the collection"; }

	~IndexOutOfRangeError() {}
};

