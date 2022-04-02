#include <iostream>
#include <windows.h>
#include <unistd.h>
#include "Matrice.h"
#include "Output.h"

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		std::cout << "Error try typing DMP -h for more information" << std::endl;
	}
	else
	{
		Matrice* m = nullptr;
		for (int i = 0; i < argc; i++)
		{
			if (strcmp(argv[i], "-h") == 0)
				Output::help();
			else if (strcmp(argv[i], "-i") == 0)
				m = new Matrice(argv[i+1]);
			else if (strcmp(argv[i], "-o") == 0){}

			else if (strcmp(argv[i], "-W") == 0){}

			else if (strcmp(argv[i], "-H") == 0){}

			else if (strcmp(argv[i], "-S") == 0){}

			else if (strcmp(argv[i], "-M") == 0){}

			else if (strcmp(argv[i], "-g") == 0)
			m = new Matrice();

		}
		m->print_matrice();
	}
	sleep(10);
	return 0;
}
