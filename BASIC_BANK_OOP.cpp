#include "clsLoginScreen.h"

int main()
{
	while (true)
	{
		if (!clsLoginScreen::ShowLoginScreen()) break;
	}
	
	system("pause>0");
}

