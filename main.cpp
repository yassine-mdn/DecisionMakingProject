#include <iostream>
#include <windows.h>
#include "Matrice.h"
#include "Output.h"
#include "Resolution.h"

int main(int argc, char* argv[])
{

	Matrice* m = nullptr;
	bool verbose{ false};
	std::string outputPath = "Testing/Output/";
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-h") == 0)
			Output::help();
		else if (strcmp(argv[i], "-g") == 0)
			m = new Matrice();
		else if (strcmp(argv[i], "-i") == 0)
			m = new Matrice(argv[i + 1]);
		else if (strcmp(argv[i], "-v") == 0)
			verbose = true;
		else if (strcmp(argv[i], "-o") == 0)
		{
			outputPath.append(argv[i + 1]);
			Output::intialize_file(outputPath);
		}
	}
	if (m != nullptr)
	{
		for (int i = 0; i < argc; ++i)
		{
			if (strcmp(argv[i], "-W") == 0)
				Resolution::wald(*m,verbose,outputPath);
			else if (strcmp(argv[i], "-L") == 0)
				Resolution::laplace(*m,verbose,outputPath);
			else if (strcmp(argv[i], "-S") == 0)
				Resolution::savage(*m,verbose,outputPath);
			else if (strcmp(argv[i], "-M") == 0)
			{
				Resolution::maximax(*m,verbose,outputPath);
				Resolution::minimax(*m,verbose,outputPath);
			}
			else if (strcmp(argv[i], "-H") == 0)
				Resolution::hurwicz(std::stof(argv[i+1]),*m,verbose,outputPath);
		}
		m->print_matrice();
	}
	else
	{
		std::cout << "Error try typing DMP -h for more information" << std::endl;
	}


	return 0;
}
