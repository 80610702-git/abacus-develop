#ifndef EPSILON0_PWSCF_H
#define EPSILON0_PWSCF_H

#include "wavefunc.h"
#include "../src_parallel/parallel_global.h"
//#if defined __FFTW2
//#include "../src_parallel/fftw.h"
//#elif defined __FFTW3
//#include "../src_parallel/fftw3.h"
//#endif

class Epsilon0_pwscf
{

public:
        
		 Epsilon0_pwscf();
		 ~Epsilon0_pwscf();
		 
		 bool epsilon;
		 double intersmear;
		 double intrasmear;
		 double domega;
		 int nomega;
		 double shift;
		 bool metalcalc;
		 double degauss;
		 
		 void Init();
		 void Cal_epsilon0();
		 void Delete();
		 double wgrid(int iw);
		 double focc(int ib, int ik);
		 void Cal_dipole(int ik);
		 
		 double **epsr;
		 double **epsi;
		 
private:
		 
		 bool init_finish;
		 complex<double> ***dipole_aux;
		 complex<double> ***dipole;
		 
};

extern Epsilon0_pwscf epsilon0_pwscf;

#endif		 