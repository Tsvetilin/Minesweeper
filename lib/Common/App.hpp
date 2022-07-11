#include <iostream>

class App {
protected:
	std::istream& inputStream;
	std::ostream& outputStream;

public:
	App(std::istream& is, std::ostream& os) : inputStream(is), outputStream(os)
	{
	}

	virtual void run() = 0;
};