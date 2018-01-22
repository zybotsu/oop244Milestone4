#include <iostream>
#include <cstring>
#include "ErrorMessage.h"
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

namespace sict {
	ErrorMessage::ErrorMessage(const char * errorMessage)
	{
		if (errorMessage == nullptr)
		{
			ptrMessage = nullptr;
		}
		else
		{
			ptrMessage = new char[strlen(errorMessage) + 1];
			strcpy(ptrMessage, errorMessage);
		}
	}
	ErrorMessage::~ErrorMessage()
	{
		delete[] ptrMessage;
		ptrMessage = nullptr;
	}
	void ErrorMessage::clear()
	{
		delete this->ptrMessage;
		ptrMessage = nullptr;
	}
	bool ErrorMessage::isClear() const
	{
		if (ptrMessage == nullptr)
			return true;
		else
			return false;
	}
	void ErrorMessage::message(const char * str)
	{
		delete[] ptrMessage;

		ptrMessage = new char[strlen(str) + 1];

		strcpy(ptrMessage, str);
	}
	const char* ErrorMessage::message()const {

		return ptrMessage;
	}

	std::ostream & operator<<(std::ostream& ost, const ErrorMessage & other)
	{
		if (!other.isClear()) {
			ost << other.message();
		}
		return ost;
	}
}

