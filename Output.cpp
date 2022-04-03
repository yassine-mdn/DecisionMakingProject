//
// Created by yassine on 02/04/2022.
//

#include <iostream>
#include "Output.h"
using namespace std;

void Output::help()
{
	cout << "helps give pointers to the best decision using different strategies\n\n"
			"DMP [-h] [-v] [-i][filename] [-o][filename] [-W] [-L] [-H][coefficient] [-S] [-M] [-g]\n\n"
			"-h\tShows help page\n"
			"-g\tAll data is inputed by the user in the terminal in its raw form\n"
			"-i\tTakes input file name\n\tall input files should be put in the input folder and be of the csv format\n"
			"-W\tUses WALD's criteria\n"
			"-L\tUses Laplace's criteria\n"
			"-H\tUses Hurwiez's criteria. Must give coefficient\n"
			"-S\tUses Savage's criteria\n"
			"-M\tUses MiniMax and MaxiMax criteria\n";
}


