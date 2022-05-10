//
// Created by yassine on 02/04/2022.
//

#include "Matrice.h"
#include "Output.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

Matrice::~Matrice()
= default;

const std::vector<std::vector<float>>& Matrice::GetMatriceDeBase() const
{
	return matriceDeBase_;
}

Matrice::Matrice()
{
	cout << "give the number of feasible strategies:\n";
	int x{};		//pour initialiser x à zero
	cin >> x;
	vector<float> actions;
	for (int i = 0; i < x; ++i)
	{
		cout << "give the number of Actions for strategy:" << i + 1 << "\n";
		float temp{};
		cin >> temp;
		actions.push_back(temp);
	}

	cout << "give the number of possible scenarios:\n";
	cin >> x;
	vector<float> scenarios;
	for (int i = 0; i < x; ++i)
	{
		cout << "give the possible demande in the case of scenario number :" << i + 1 << "\n";
		float temp{};
		cin >> temp;
		scenarios.push_back(temp);
	}

	cout << "Does the selling price depend on the current scenarios ? y/n\n";
	char c;
	cin >> c;
	vector<float>sellingPrice; //used a vector because the if statement gonna limit the scope of any variable declared inside it
	if (c == 'y')
	{
		sellingPrice.reserve(scenarios.size());		//reserve un vecteur de la meme taille que le vecteur scenarios
		for (int i = 0; i < scenarios.size(); ++i)
		{
			cout << "give the possible selling price in the case of scenario number :" << i + 1 << "\n";
			float temp{};
			cin >> temp;
			sellingPrice.push_back(temp);
		}
	}
	else
	{
		cout << "give the Fixed selling price :\n";
		float temp{};
		cin >> temp;
		sellingPrice.push_back(temp);
	}

	cout << "Did the gouvernement grant you a subsidy ? y/n\n";
	cin >> c;
	unordered_map<int, float> subsidys;			//comme les hashTable en java
	if (c == 'y')
	{
		cout << "give the max value of the first  interval :\n";
		int key{ 1 };
		cin >> key;
		while (key != -1)
		{
			cout << "give the pourcentage of the subsidy (float value) :\n";
			float temp{};
			cin >> temp;
			subsidys[key] = temp;
			cout << "give the max value of the next interval (-1 to mark the last interval):\n";
			cin >> key;
		}
		cout << "give the pourcentage of the subsidy (float value) :\n";
		float temp{};
		cin >> temp;
		subsidys[key] = temp;

	}
	else
		subsidys[-1] = 0;

	cout << "Does the Buying price varie with the quantity ? y/n\n";
	cin >> c;
	unordered_map<int, float> buyingPrice;
	if (c == 'y')
	{
		cout << "give the max value of the first interval :\n";
		int key{ 1 };
		cin >> key;
		while (key != -1)
		{
			cout << "Type the asking price :\n";
			float temp{};
			cin >> temp;
			buyingPrice[key] = temp;
			cout << "give the max value of the next interval (-1 to mark the last interval):\n";
			cin >> key;
		}
		cout << "Type the asking price :\n";
		float temp{};
		cin >> temp;
		buyingPrice[key] = temp;
	}
	else
	{
		cout << "Type the asking price :\n";
		float temp{};
		cin >> temp;
		buyingPrice[-1] = temp;
	}

	cout << "Are there any extra fixed expenses ? y/n\n";
	cin >> c;
	float extraExpenses{};
	if (c == 'y')
	{
		cout << "give the total value of all extra fixed expenses :\n";
		cin >> extraExpenses;
	}

	for (float& action: actions)
	{
		std::vector<float> tempVect;
		for (int j = 0; j < scenarios.size(); ++j)
		{
			float val{};
			float buyPrice{ 0 };	//le prix d'achat pout l'intervalle choisi
			float subsidy{ 0 };		//subvention pour l'intervale choisi
			float stock = action < scenarios.at(j) ? action : scenarios.at(j); 	//le min entre la demande et la quantité qui peut etre acheter

			for (const auto& item: buyingPrice)
			{
				if (stock <= (float) item.first || item.first == -1)
				{
					buyPrice = item.second;
					continue;
				}
			}

			for (const auto& item: subsidys)
			{
				if (stock <= (float) item.first || item.first == -1)
				{
					subsidy = item.second;
					continue;
				}
			}
			if (scenarios.size() == sellingPrice.size())
				val = ((action * buyPrice * subsidy) + stock * sellingPrice.at(j)) - (action * buyPrice + extraExpenses);
			else	//pour le cas ou on a un prix fixe
				val = ((action * buyPrice * subsidy) + stock * sellingPrice.at(0)) - (action * buyPrice + extraExpenses);

			tempVect.push_back(val);
		}
		matriceDeBase_.push_back(tempVect);
	}

}

Matrice::Matrice(const std::string& path)
{
	std::fstream file;
	std::string fullPath = "Testing/Input/";	//TODO:When in release configuration change input folder
	fullPath.append(path);
	file.open(fullPath, std::ios::in);		//ouvre le fichier et ecrase son contenu
	if (!file.is_open())
	{
		std::cout << "file name or path invalid\n";
		return;
	}
	while (file)
	{
		std::string line;
		if (!getline(file, line)) break;	//sasure que on n'est pas a la fin du fichier

		std::istringstream ss(line);		//lit toute un ligne du fichier
		std::vector<float> rows;

		while (ss)
		{
			std::string s;
			if (!getline(ss, s, ',')) break;
			rows.push_back(std::stof(s));
		}
		matriceDeBase_.push_back(rows);
	}
}

void Matrice::print_matrice()
{
	Output::pretty_matrix_print(matriceDeBase_);
}

