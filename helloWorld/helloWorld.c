#include <stdio.h>
#include <omp.h>
	
int main(){
	int myid, nthreads;
	
	omp_set_num_threads(5);

	#pragma omp parallel private(myid) shared(nthreads)
	{

		myid = omp_get_thread_num();
		nthreads = omp_get_num_threads();

		printf("%d of %d - hello world!\n", myid, nthreads);
			
		

	}
	return 0;
}
