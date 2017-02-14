

#include "Application.h"

#define _DEBUGMODE 1;	//	0=Non-debug mode, 1=Debug mode

int main( void )
{
	Application &app = Application::GetInstance();
	app.Init();
	app.Run();
	app.Exit();
}