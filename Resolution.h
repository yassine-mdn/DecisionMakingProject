//
// Created by yassine on 02/04/2022.
//

#ifndef DECISIONMAKINGPROJECT__RESOLUTION_H_
#define DECISIONMAKINGPROJECT__RESOLUTION_H_

#include <vector>
#include "Matrice.h"

class Resolution
{
 public:
	static void wald(Matrice& m,bool verbose,std::string path);
	static void laplace(Matrice& m,bool verbose,std::string path);
	static void hurwicz(float alpha, Matrice& m,bool verbose,std::string path);
	static void savage(Matrice& m,bool verbose,std::string path);
	static void minimax(Matrice& m,bool verbose,std::string path);
	static void maximax(Matrice& m,bool verbose,std::string path);

 private:

};

#endif //DECISIONMAKINGPROJECT__RESOLUTION_H_
