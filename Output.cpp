//
// Created by yassine on 02/04/2022.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include "Output.h"
using namespace std;


/*
 * Permet d'aficher un page help qui montre comment utiliser tous nos arguments de commande
 *
 * */
void Output::help()
{
	cout << "helps give pointers to the best decision using different strategies\n\n"
			"DMP [-h] [-g] [-i][filename] [-v] [-o][filename] [-W] [-L] [-H][coefficient] [-S] [-M] [-g]\n\n"
			"-h\tShows help page\n"
			"-g\tAll data is inputted by the user in the terminal in its raw form\n"
			"-i\tTakes input file name\n\tall input files should be put in the input folder and be of the csv format\n"
			"-v\tVerbose output to the terminal\n"
			"-o\tOutputs results in to desired file in the output folder\n\tif the file already exist in the folder in will get overwritten\n"
			"-A\tUse all criterias\n"
			"-W\tUses WALD's criteria\n\tMust give Hurwiez's coefficient"
			"-L\tUses Laplace's criteria\n"
			"-H\tUses Hurwiez's criteria. Must give coefficient\n"
			"-S\tUses Savage's criteria\n"
			"-M\tUses MiniMax and MaxiMax criteria\n";
}

/*
 * imprime dans au terminale une matrice avec un subtext si demander
 *
 * @param m reference constante vers notre vecteur de vecteur
 * @param text sub-text a imprimer apprait notre vecteur , "" par defalut
 * */
void Output::pretty_matrix_print(vector<std::vector<float>>& m, std::string text)
{
	size_t maxColLen[m.at(0).size()];	//nombre de char max que prendra chaque colone de notre matrice
	for (int i = 0; i < m.at(0).size(); ++i)
	{
		maxColLen[i] = 0;
	}
	for (int i = 0; i < m.size(); ++i)
	{
		for (int j = 0; j < m.at(i).size(); ++j)
		{
			const size_t num_length{ number_of_digits(m[i][j]) };
			if (num_length > maxColLen[j] )
				maxColLen[j] = num_length;
		}
	}

	cout<<text<<endl;

	for (auto& j: m)
	{
		for (int i = 0; i < j.size(); ++i)
		{
			cout << (i == 0 ? "\n| " : "") << setw((int)maxColLen[i]) << j[i] << (i == j.size() - 1 ? " |" : " ");
		}
	}
	cout << "\n";

}

/*
 * imprime dans au terminale un vecteur avec un subtext si demander
 *
 * @param v reference constante vers notre vecteur
 * @param text sub-text a imprimer apprait notre vecteur , " " par defalut
 * */
void Output::pretty_vector_print(vector<float>& v, std::string text)
{
	size_t maxColLen;
	for (int i = 0; i < v.size(); ++i)
	{
		size_t maxLen{};

		const size_t num_length{ number_of_digits(v.at(i)) };
		if (num_length > maxLen)
			maxLen = num_length;
		maxColLen = maxLen;

	}

	cout<<text<<endl;

	for (int i = 0; i < v.size(); ++i)
	{
		cout << "\n" << i + 1 << " - | " << setw((int)maxColLen) << v[i] << " |";
	}

	cout << "\n";
}

/*
 * imprime dans le fichier une matrice avec un titre et a subtext si demander
 *
 * @param m reference constante vers notre vecteur de vecteur
 * @param path le chemain du fichier
 * @param title titre du vecteur à imprimer apparait avant le vecteur , " " par default
 * @param text sub-text a imprimer apprait notre vecteur , " " par defalut
 * */
void Output::output_matrix_to_file(vector<std::vector<float>>& m, std::string path, std::string title, std::string text)
{
	fstream my_file;
	my_file.open(path, ios_base::app);
	my_file <<"\n\n";
	size_t maxColLen[m.at(0).size()];	//nombre de char max que prendra chaque colone de notre matrice
	for (int i = 0; i < m.at(0).size(); ++i)
	{
		maxColLen[i] = 0;
	}
	for (int i = 0; i < m.size(); ++i)
	{
		for (int j = 0; j < m.at(i).size(); ++j)
		{
			const size_t num_length{ number_of_digits(m[i][j]) };
			if (num_length > maxColLen[j] )
				maxColLen[j] = num_length;
		}
	}

	my_file<<"\n###"<<title<<endl;

	for (auto& j: m)
	{
		for (int i = 0; i < j.size(); ++i)
		{
			my_file << (i == 0 ? "\n\t| " : "") << setw((int)maxColLen[i]) << j[i] << (i == j.size() - 1 ? " |" : " ");
		}
	}

	my_file << "\n";
	my_file<<text;
	my_file << "\n";
	my_file.close();

}

/*
 * imprime dans le fichier un vecteur avec un titre et a subtext si demander
 *
 * @param v reference constante vers notre vecteur
 * @param path le chemain du fichier
 * @param title titre du vecteur à imprimer apparait avant le vecteur , " " par default
 * @param text sub-text a imprimer apprait notre vecteur , " " par defalut
 * */
void Output::output_vector_to_file(vector<float>& v, std::string path, std::string title, std::string text)
{
	fstream my_file;
	my_file.open(path, ios::app);

	size_t maxColLen;
	for (int i = 0; i < v.size(); ++i)
	{
		size_t maxLen{};

		const size_t num_length{ number_of_digits(v.at(i)) };
		if (num_length > maxLen)
			maxLen = num_length;
		maxColLen = maxLen;

	}

	my_file<<"\n###"<<title<<endl;

	for (int i = 0; i < v.size(); ++i)
	{
		my_file << "\n\t" << i + 1 << " - | " << setw((int)maxColLen) << v[i] << " |";
	}

	my_file << "\n";
	my_file<<text;
	my_file << "\n";
	my_file.close();

}

/*
 * Ecrase le contenu du fichier s'il existe et l'initialise
 *
 * @param path le chemain du fichier
 * */
void Output::intialize_file(std::string path)
{
	fstream my_file;
	my_file.open(path, ios::out);
	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);
	my_file << "\n\n##"<<path<<"\n####"<<(now->tm_year + 1900) << '-'
					 << (now->tm_mon + 1) << '-'
					 <<  now->tm_mday << '|'
					 << now->tm_hour <<':'
					 << now->tm_min
					 << "\n";			//permet d'avoir le temp avec format YYYY-MM-DD|hh:mm
	my_file.close();
}

/*
 * Rend le nombre de charactére qui compose un réel donné
 *
 * @param n le nombre réel d'ou en veut savoir la taille
 * @return nombre de charactére de n
 *
 * */
size_t Output::number_of_digits(float n)
{
	ostringstream str;
	str << n;
	return str.str().size();
}



