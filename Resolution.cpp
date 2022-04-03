//
// Created by yassine on 02/04/2022.
//

#include "Resolution.h"
#include "Output.h"
#include <algorithm>
#include <numeric>

void Resolution::wald(Matrice& m, bool verbose, std::string path)
{
	std::vector<float> min;
	min.reserve(m.GetMatriceDeBase().size());

	for (const auto& i: m.GetMatriceDeBase())
	{
		min.push_back(*std::min_element(i.begin(), i.end()));
	}

	std::string text = "d'apres le critere de WAld on choisi la startegie : ";
	text.append(std::to_string(std::max_element(min.begin(), min.end()) - min.begin() + 1));

	if (verbose)
		Output::pretty_vector_print(min, text);
	if (path.compare("Testing/Output/"))
	{
		Output::output_vector_to_file(min, path, "Critere de WALD", text);
	}
	else
	{
		std::cout << text << std::endl;
	}
}

void Resolution::laplace(Matrice& m, bool verbose, std::string path)
{
	std::vector<float> average;
	average.reserve(m.GetMatriceDeBase().size());

	for (const auto& i: m.GetMatriceDeBase())
	{
		average.push_back(std::accumulate(i.begin(), i.end(), 0.0f) / (float)i.size());
	}

	std::string text = "d'apres le critere de Laplace on choisi la startegie : ";
	text.append(std::to_string(std::max_element(average.begin(), average.end()) - average.begin() + 1));

	if (verbose)
		Output::pretty_vector_print(average, text);
	if (path.compare("Testing/Output/"))
	{
		Output::output_vector_to_file(average, path, "Critere de Laplace", text);
	}
	else
	{
		std::cout << text << std::endl;
	}
}

void Resolution::hurwicz(float alpha, Matrice& m, bool verbose, std::string path)
{
	std::vector<float> min;
	std::vector<float> max;
	min.reserve(m.GetMatriceDeBase().size());
	max.reserve(m.GetMatriceDeBase().size());

	for (const auto& i: m.GetMatriceDeBase())
	{
		min.push_back(*std::min_element(i.begin(), i.end()));
		max.push_back(*std::max_element(i.begin(), i.end()));
	}

	std::vector<float> hurwicz;
	hurwicz.reserve(min.size());

	for (int i = 0; i < max.size(); ++i)
	{
		hurwicz.push_back((max.at(i) * alpha) + (min.at(i) * (1 - alpha)));
	}

	std::string text = "d'apres le critere de Hurwicz on choisi la startegie : ";
	text.append(std::to_string(std::max_element(hurwicz.begin(), hurwicz.end()) - hurwicz.begin() + 1));

	if (verbose)
		Output::pretty_vector_print(hurwicz, text);
	if (path.compare("Testing/Output/"))
	{
		Output::output_vector_to_file(hurwicz, path, "Critere de Hurwicz", text);
	}
	else
	{
		std::cout << text << std::endl;
	}
}

void Resolution::savage(Matrice& m, bool verbose, std::string path)
{
	std::vector<std::vector<float>> matriceRegret;

	for (const auto& i: m.GetMatriceDeBase())
		matriceRegret.push_back(i);

	for (int i = 0; i < matriceRegret.at(0).size(); ++i)
	{
		std::vector<float> max;
		max.reserve(matriceRegret.size());
		for (int j = 0; j < matriceRegret.size(); ++j)
		{
			max.push_back(matriceRegret.at(j).at(i));
		}
		for (int j = 0; j < m.GetMatriceDeBase().size(); ++j)
		{
			matriceRegret[j][i] = *(std::max_element(max.begin(), max.end())) - m.GetMatriceDeBase().at(j).at(i);
		}

	}

	std::vector<float> max;
	max.reserve(matriceRegret.size());

	for (const auto& i: matriceRegret)
	{
		max.push_back(*std::max_element(i.begin(), i.end()));
	}

	std::string text = "d'apres le critere de Savage on choisi la startegie : ";
	text.append(std::to_string(std::min_element(max.begin(), max.end()) - max.begin() + 1));

	if (verbose)
	{
		Output::pretty_matrix_print(matriceRegret, "matrice de regret");
		Output::pretty_vector_print(max, text);
	}
	if (path.compare("Testing/Output/"))
	{
		Output::output_matrix_to_file(matriceRegret, path, "Critere de Savage");
		Output::output_vector_to_file(max, path, "", text);
	}
	else
	{
		std::cout << text << std::endl;
	}
}

void Resolution::minimax(Matrice& m, bool verbose, std::string path)
{
	std::vector<float> max;
	max.reserve(m.GetMatriceDeBase().size());

	for (const auto& i: m.GetMatriceDeBase())
	{
		max.push_back(*std::max_element(i.begin(), i.end()));
	}

	std::string text = "d'apres le critere de MiniMax on choisi la startegie : ";
	text.append(std::to_string(std::min_element(max.begin(), max.end()) - max.begin() + 1));

	if (verbose)
		Output::pretty_vector_print(max, text);
	if (path.compare("Testing/Output/"))
	{
		Output::output_vector_to_file(max, path, "Critere de MiniMax", text);
	}
	else
	{
		std::cout << text << std::endl;
	}
}

void Resolution::maximax(Matrice& m, bool verbose, std::string path)
{
	std::vector<float> max;
	max.reserve(m.GetMatriceDeBase().size());

	for (const auto& i: m.GetMatriceDeBase())
	{
		max.push_back(*std::max_element(i.begin(), i.end()));
	}

	std::string text = "d'apres le critere de MiniMax on choisi la startegie : ";
	text.append(std::to_string(std::max_element(max.begin(), max.end()) - max.begin() + 1));

	if (verbose)
		Output::pretty_vector_print(max, text);
	if (path.compare("Testing/Output/"))
	{
		Output::output_vector_to_file(max, path, "Critere de MiniMax", text);
	}
	else
	{
		std::cout << text << std::endl;
	}
}
