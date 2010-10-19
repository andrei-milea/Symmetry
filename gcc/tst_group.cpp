#include "group.h"
#include "intmodn.h"
#include "permutation.h"
#include "std_ex.h"
#include "group_lattice.h"


#include <iostream>

int main()
{

	cPermElem<3> s3({1,2});
	cPermElem<3> s4({1,2,3});
	cGroupElem< cPermElem<3>, Multiplication> elem3(s3);
	cGroupElem< cPermElem<3>, Multiplication> elem4(s4);
	std::vector< cGroupElem<cPermElem<3>, Multiplication> >  generators1;
	generators1.push_back(elem3);
	generators1.push_back(elem4);
	S3 g2(generators1);

	cGrpLattice<S3> S3_lattice(g2);


	return 0;	
};

