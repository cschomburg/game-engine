#include <SDL/SDL.h>

#include "Application.h"

int main(int argc, char *argv[])
{
	return Application::instance()->execute();
}
