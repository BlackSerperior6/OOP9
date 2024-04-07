#pragma once
#include "WrongSizeError.h"

class EmptyColletionError : public WrongSizeError
{
public:

	EmptyColletionError() { msg += "collection is empty"; }
};

