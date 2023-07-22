

#include "top.h"


int main(){

	static data_in xn[FFT_LENGTH];
	static data_out xk[FFT_LENGTH];



	Dh1(xn, xk);

	return 0;
}
