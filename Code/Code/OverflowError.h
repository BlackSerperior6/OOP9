#pragma once
#include "WrongSizeError.h"
class OverflowError : public WrongSizeError
{
public:
	OverflowError() { msg += "collection can't have more than 30 elements"; }
};

