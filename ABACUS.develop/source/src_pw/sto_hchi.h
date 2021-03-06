#ifndef INCLUDE_STO_HCHI_H
#define INCLUDE_STO_HCHI_H
#include "tools.h"

//-----------------------------------------------------
// H * chi
// chi: stochastic wave functions
//
// H: the Hamiltonian matrix, which is decomposed 
// into the electron kinetic, effective potential V(r),
// and the non-local pseudopotentials.
// The effective potential = Local pseudopotential +
// Hartree potential + Exchange-correlation potential
//------------------------------------------------------

class Stochastic_Hchi
{

	public:

    // constructor and deconstructor
    Stochastic_Hchi();
    ~Stochastic_Hchi();
	void Hchi();
	

	private:

	// chi should be orthogonal to psi (generated by diaganolization methods,
	// such as CG)
	void orthogonal_to_psi();


};

#endif// Eelectrons_Hchi
