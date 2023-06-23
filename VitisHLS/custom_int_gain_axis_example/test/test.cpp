

#include <stdio.h>
#include <hls_stream.h>

#define N 1024

void top_entity(hls::stream<int> &Ain, hls::stream<int> &Aout);


int main(){

	hls::stream<int> Ain;
	hls::stream<int> Aout;

	for(int n=0; n < N; n++){
		Ain << n;
	}

	top_entity(Ain, Aout);

	for(int n=0; n < N; n++){
		int vout = Aout.read();
		printf("[%d] : %d \n", n, vout);
	}


	return 0;
}
