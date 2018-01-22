#ifndef SICT_ERRORMESSAGE_H
#define SICT_ERRORMESSAGE_H
#include<iostream>


namespace sict {
	class ErrorMessage {

	private:
		char* ptrMessage;
	public:
		explicit ErrorMessage(const char* errorMessage = nullptr);
		ErrorMessage(const ErrorMessage& em) = delete;
		ErrorMessage& operator=(const ErrorMessage& em) = delete;
		virtual ~ErrorMessage();
		void clear();
		bool isClear() const;
		void message(const char* str);
		const char* message()const;
	};
	std::ostream& operator<<(std::ostream&, const ErrorMessage& other);
}
#endif


