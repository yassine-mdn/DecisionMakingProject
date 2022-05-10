//
// Created by yassine on 02/04/2022.
//

#include "Matrice.h"
#include "Output.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <map>

using namespace std;

//Destructeur par default
Matrice::~Matrice()
= default;

//getter pour matrice de base
const std::vector<std::vector<float>>& Matrice::GetMatriceDeBase() const
{
	return matriceDeBase_;
}


/*
 * Constructeur vide
 *
 * Permet de génerer notre matrice de gain en utilisant les inputs de l'utilisateur
 *
 * */
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
	}		//permet de stocker le nombre d'actions pour chaque strategie

	cout << "give the number of possible scenarios:\n";
	cin >> x;
	vector<float> scenarios;
	for (int i = 0; i < x; ++i)
	{
		cout << "give the possible demande in the case of scenario number :" << i + 1 << "\n";
		float temp{};
		cin >> temp;
		scenarios.push_back(temp);
	}		//stocker la demande attendue pour chaque scenario

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

	/*on utilise std::pair<int,int> pour stocker les 2 paires qui represente chaque intervale
	 *et on utilise std::map<pair<int,int>, float> pour lier chque clé(intervale) a la subvention accorder pour cet intervale
	 *-1 signifie l'infinie
	 * */
	cout << "Did the gouvernement grant you a subsidy ? y/n\n";
	cin >> c;
	map<pair<int,int>, float> subsidys;
	if (c == 'y')
	{
		cout << "give the min value of the first interval :\n";
		int min_intervale{ -1 };
		cin >> min_intervale;
		cout << "give the min value of the first interval :\n";
		int max_intervale{ -1 };
		cin >> max_intervale;
		while (min_intervale != -1 && max_intervale !=-1)
		{
			cout << "give the pourcentage of the subsidy (float value (O.?)) :\n";
			float temp{};
			cin >> temp;
			subsidys[make_pair(min_intervale,max_intervale)] = temp;
			cout << "give the min value of the next interval (-1 to quit) :\n";
			cin >> min_intervale;
			if (min_intervale != -1)
			{
				cout << "give the max value of the next interval (-1 for +infinity) :\n";
				cin >> max_intervale;
			}
		}
	}
	else
		subsidys[make_pair(-1,-1)] = 0;	// si il n'y a pas de subventsion on les met a zero

	cout << "Does the Buying price varie with the quantity ? y/n\n";
	cin >> c;

	/*on utilise std::pair<int,int> pour stocker les 2 paires qui represente chaque intervale
	 *et on utilise std::map<pair<int,int>, float> pour lier chaque clé(intervale) au prix d'achat pour cet intervale
	 *-1 signifie l'infinie pour la borne max et nous permet aussi de quitter notre boucle
	 * */
	map<pair<int,int>, float> buyingPrice;
	if (c == 'y')
	{
		cout << "give the min value of the first interval :\n";
		int min_intervale{ -1 };
		cin >> min_intervale;
		cout << "give the min value of the first interval :\n";
		int max_intervale{ -1 };
		cin >> max_intervale;
		while (min_intervale != -1 && max_intervale !=-1)
		{
			cout << "Type the asking price :\n";
			float temp{};
			cin >> temp;
			buyingPrice[make_pair(min_intervale,max_intervale)] = temp;
			cout << "give the min value of the next interval (-1 to quit) :\n";
			cin >> min_intervale;
			if (min_intervale != -1)
			{
				cout << "give the max value of the next interval (-1 for +infinity) :\n";
				cin >> max_intervale;
			}
		}
	}
	else
	{
		cout << "Type the asking price :\n";
		float temp{};
		cin >> temp;
		buyingPrice[make_pair(-1,-1)] = temp;
	}	// si le prix est fixe on prend l'intervalle ]-infini,+infini[

	//toute nos charges fixe
	cout << "Are there any extra fixed expenses ? y/n\n";
	cin >> c;
	float extraExpenses{};
	if (c == 'y')
	{
		cout << "give the total value of all extra fixed expenses :\n";
		cin >> extraExpenses;
	}

	/*
	 * Le coeur de notre constructeur permet de generer notre matrice de base
	 * */
	for (float& action: actions)		//on Loupes 3la les lignes
	{
		std::vector<float> tempVect;		//vecteur temporaire crée uniqument pour stocker val corespendante a chaque colone
		for (int j = 0; j < scenarios.size(); ++j)	//iterer surs les colones
		{
			float val{ 0 };			//Valeur de notre case
			float buyPrice{ 0 };	//le prix d'achat pout l'intervalle choisi
			float subsidy{ 0 };		//subvention pour l'intervale choisi
			float stock = action < scenarios.at(j) ? action : scenarios.at(j); 	//le min entre la demande et la quantité qui peut etre acheter

			for (const auto& item: buyingPrice)
			{
				if ((stock >= (float) item.first.first && stock <= (float) item.first.second )|| item.first.second == -1)
				{
					buyPrice = item.second;
					continue;
				}	//si la valeur de stock se trouve dans notre intervale ou bien l'internavle n'as pas de borne sup on assigne le prix d'achat
			}		//for each permet d'iterer sur notre map de prix d'achat

			for (const auto& item: subsidys)
			{
				if ((stock >= (float) item.first.first && stock <= (float) item.first.second )|| item.first.second == -1)
				{
					subsidy = item.second;
					continue;
				}	//si la valeur de stock se trouve dans notre intervale ou bien l'internavle n'as pas de borne sup on assigne la subvention corespendante
			}		//for each permet d'iterer sur notre map de subvention

			///(action * buyPrice * subsidy) represente permet de calculer notre subvention
			///(stock * sellingPrice.at(?))	represente notre chiffre d'affaire
			///(action * buyPrice + extraExpenses) represente nos charges d'achat & fixe
			if (scenarios.size() == sellingPrice.size())
				val = ((action * buyPrice * subsidy) + stock * sellingPrice.at(j)) - (action * buyPrice + extraExpenses);
			else	//pour le cas ou on a un prix fixe
				val = ((action * buyPrice * subsidy) + stock * sellingPrice.at(0)) - (action * buyPrice + extraExpenses);

			tempVect.push_back(val);
		}
		matriceDeBase_.push_back(tempVect);
	}

}


/*
 * Constructeur avec parametre
 *
 * Permet de génerer notre matrice de gain en utilisant un fichier qui contient deja une matrice de gains
 * ajouter pour des raisons de debugage et facilité les tests
 *
 * @param path represente le chemin vers notre fichier d'entrer
 *
 * */
Matrice::Matrice(const std::string& path)
{
	std::fstream file;
	std::string fullPath = "Testing/Input/";	//TODO:When in release configuration change input folder
	fullPath.append(path);
	file.open(fullPath, std::ios::in);		//ouvre le fichier
	if (!file.is_open())		//on s'assure qu'on peut ouvrir le fichier
	{
		std::cout << "file name or path invalid\n";
		exit(EXIT_SUCCESS);
	}
	while (file)
	{
		std::string line;
		if (!getline(file, line)) break;	//sasure que on n'est pas a la fin du fichier

		std::istringstream ss(line);		//lit toute un ligne du fichier et la stocke dans un istringstream
		std::vector<float> rows;				//vecteur qui represente nos lignes

		while (ss)					//tant que on est pa a la fin de notre istringstream
		{
			std::string s;
			if (!getline(ss, s, ',')) break;		//on lit les sub-string contenue dans notre chaine qui sont delimiter avec ','
			rows.push_back(std::stof(s));
		}
		matriceDeBase_.push_back(rows);
	}
}

/*
 * imprime notre matrice
 * */
void Matrice::print_matrice()
{
	Output::pretty_matrix_print(matriceDeBase_);
}

