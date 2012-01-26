
#include "Engine.h"

int main()
{
	Engine* engine = new Engine();

	try 
	{
		engine->Go();
	}
	catch(char* e)
	{
		MessageBox(NULL, e, "Exception Occured in creating the Engine", MB_OK);
	}

	return EXIT_SUCCESS;
}