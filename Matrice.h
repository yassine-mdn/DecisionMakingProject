//
// Created by yassine on 02/04/2022.
//

#ifndef DECISIONMAKINGPROJECT__MATRICE_H_
#define DECISIONMAKINGPROJECT__MATRICE_H_

#include <iostream>
#include <vector>
#include <string>


/*
 *	Permet de créer notre matrice
 *
 * 	Cette classe contient un std::vector<std::vector<float>> qui est utiliser pour stocker notre matrice
 * 	Le but de notre classe est de permetre de générer cette matrice soit avec les input de l'utilisateur ou bien un fichier csv
 *
 * */
class Matrice
{
 public:
	Matrice();
	Matrice(const std::string& path);
	virtual ~Matrice();			//Destructeur
	const std::vector<std::vector<float>>& GetMatriceDeBase() const;
	void print_matrice();
 private:
	std::vector<std::vector<float>> matriceDeBase_;
};

#endif //DECISIONMAKINGPROJECT__MATRICE_H_
