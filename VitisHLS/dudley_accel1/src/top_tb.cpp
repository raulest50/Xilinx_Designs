#include <iostream>
#include <fstream>
#include <vector>
#include "top.h"

int main() {

    // Preparation of input sample data
    //std::fstream fin("in.dat");
	//std::fstream fin("C:\\Users\\raule\\Documents\\Xilinx_Designs\\scripts\\Matlab\\in2.dat");

	std::fstream fin("C:\\Users\\raule\\Documents\\Xilinx_Designs\\scripts\\Matlab\\Ain.dat");

    std::vector<float> vec_data;
    float num;
    int nfft = 13;
    int data_size = 1 << nfft; // Perform 32-point FFT
    for (int i = 0; i < data_size; i++) {
        fin >> num;
        vec_data.push_back(num);
    }

    // Writing FFT sample data to the stream
    fft_stream input_data, output_data;
    for (int i = 0; i < data_size; i++) {
        data_t in_data;
        in_data.data = vec_data[i];
        in_data.last = (i == data_size - 1);
        input_data.write(in_data);
    }

    // FFT Execution
    top(input_data, output_data); //, nfft);

    //std::ofstream fout("C:\\Users\\raule\\OneDrive\\Desktop\\Vitis_HLS_WS\\dudley_accel1\\src\\output.dat");
    std::ofstream fout("C:\\Users\\raule\\Documents\\Xilinx_Designs\\scripts\\Matlab\\debug_out.dat");

    // Reading FFT results from a stream
    data_t dout;
    int m = 0;
    do {
        dout = output_data.read();
        std::cout << m+1 << dout.data << "\n";
        fout << dout.data;
        m++;
    } while (!dout.last);

    fout.close();

}
