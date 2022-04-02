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
	static void lawd(Matrice& m);
	static void laplace(Matrice& m);
	static void hurwicz(float alpha, Matrice& m);
	static void savage(Matrice& m);
	static void minimax(Matrice& m);
	static void maximax(Matrice& m);

 private:

};

#endif //DECISIONMAKINGPROJECT__RESOLUTION_H_
