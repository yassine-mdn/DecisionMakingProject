#include <iostream>
#include <windows.h>
#include <unistd.h>
#include "Matrice.h"
#include "Output.h"
#include "Resolution.h"

int main(int argc, char* argv[])
{

	Matrice* m = nullptr;
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-h") == 0)
			Output::help();
		else if (strcmp(argv[i], "-g") == 0)
			m = new Matrice();
		else if (strcmp(argv[i], "-i") == 0)
			m = new Matrice(argv[i + 1]);
	}
	if (m != nullptr)
	{
		for (int i = 0; i < argc; ++i)
		{
			if (strcmp(argv[i], "-W") == 0)
				Resolution::wald(*m);
			else if (strcmp(argv[i], "-H") == 0)
				Resolution::laplace(*m);
			else if (strcmp(argv[i], "-S") == 0)
				Resolution::savage(*m);
			else if (strcmp(argv[i], "-M") == 0)
			{
				Resolution::maximax(*m);
				Resolution::minimax(*m);
			}
		}
	}
	else
	{
		std::cout << "Error try typing DMP -h for more information" << std::endl;
	}

	sleep(10);
	return 0;
}
