//
// Created by yassine on 02/04/2022.
//

#ifndef DECISIONMAKINGPROJECT__MATRICE_H_
#define DECISIONMAKINGPROJECT__MATRICE_H_

#include <iostream>
#include <vector>
#include <string>

class Matrice
{
 public:
	Matrice();
	virtual ~Matrice();
	const std::vector<std::vector<float>>& GetMatriceDeBase() const;
	void initialize_matrice(int x , int y);
	void initialize_matrice(const std::string& path);
	void print_matrice();
 private:
	std::vector<std::vector<float>> matriceDeBase_;
};

#endif //DECISIONMAKINGPROJECT__MATRICE_H_
