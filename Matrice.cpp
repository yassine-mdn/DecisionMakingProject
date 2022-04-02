//
// Created by yassine on 02/04/2022.
//

#include "Matrice.h"
#include <fstream>
#include <sstream>

Matrice::~Matrice()
{

}
const std::vector<std::vector<float>>& Matrice::GetMatriceDeBase() const
{
	return matriceDeBase_;
}
Matrice::Matrice()
{
}
void Matrice::print_matrice()
{

	for (int i = 0; i < matriceDeBase_.size(); ++i)
	{
		for (int j = 0; j < matriceDeBase_.at(i).size(); ++j)
		{
			std::cout << matriceDeBase_.at(i).at(j) << " ";
		}
		std::cout << std::endl;
	}

}
void Matrice::initialize_matrice(int x, int y)
{
	for (int i = 0; i < x; ++i)
	{
		std::vector<float> tempVect;
		for (int j = 0; j < y; ++j)
		{
			std::cout << "tapper l\'element" << i << ":" << j << "\n";
			float valueTyped{};
			std::cin >> valueTyped;
			tempVect.push_back(valueTyped);
		}
		matriceDeBase_.push_back(tempVect);
	}

}
void Matrice::initialize_matrice(const std::string& path)
{
	std::fstream file;
	file.open(path,std::ios::in);
	if (!file.is_open()){
		std::cout<<"file name or path invalid\n";
		return;
	}
	while(file){
		std::string line;
		if(!getline(file,line)) break;

		std::istringstream ss(line);
		std::vector<float > rows;

		while(ss){
			std::string s;
			if(!getline(ss, s, ',')) break;
			rows.push_back(std::stof(s));
		}
		matriceDeBase_.push_back(rows);
	}
}
