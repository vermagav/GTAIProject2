#include "_config.h"

// Output message function
void outputMessage(outputMessageType type, std::string message)
{
	if(type == OUTPUT_DEBUG && FLAG_OUTOUT_DEBUG)
	{
		std::cout<<message;
		std::cout<<"\n";
	}

	if(type == OUTPUT_PRINT && FLAG_OUTPUT_PRINT)
	{
		std::cout<<message;
		std::cout<<"\n";
	}
}