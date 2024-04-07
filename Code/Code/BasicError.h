#pragma once

#include <iostream>
#include <string>

using namespace std;

class BasicError
{
public:
	BasicError(){}

	virtual ~BasicError() {}

	void PrintError()
	{
		cout << msg << endl;
	}

protected:
	string msg;
};

