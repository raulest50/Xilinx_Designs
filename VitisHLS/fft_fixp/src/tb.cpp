
#include <iostream>
#include <fstream>

#include "top.h"


int main(){


	//static data_in xn[FFT_LENGTH];
	static data_out xk[FFT_LENGTH];



	Dh1(test_signal, xk);

	std::ofstream fout("C:\\Users\\raule\\OneDrive\\Desktop\\Vitis_HLS_WS\\fft_fixp\\src\\fft.dat");

	for (int j = 0; j< FFT_LENGTH; j++){
		fout << xk[j];
		printf("[%d] : %f + i %f \n", j, xk[j].real().to_float(), xk[j].imag().to_float());
	}

	return 0;
}
