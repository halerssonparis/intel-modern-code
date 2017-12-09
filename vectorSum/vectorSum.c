#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <omp.h>

long long int sum(int *v, long long int N){
	long long int i, sum = 0;
	int myId, nthreads, sum_local;

	//int ini, fin;
	
	//#oragna omp barrier, critical, atomic(via hardware)	
	#pragma omp parallel private(i, myId, sum_local) //ini, fin)
	{
		myId = omp_get_thread_num();
		sum_local = 0;
	
		#pragma omp single 
		{
			nthreads = omp_get_num_threads();
			//int whatever = N/nthreads;
		}	

		/*ini = myId * whatever;
		
		if (myId = nthreads-1 && fin = n) {
			fin = N;
		} else {
			fin = ini + whatever;
		}*/

		#pragma omp for reduction (+: sum)
		for(i = 0; i < N; i++)
			//nthreads - 1
			sum += v[i];

		//#pragma omp atomic
		//sum += sum_local;
	}

	return sum;
}

int main(int argc, char **argv){
	char *awnser[] = { "bad", "ok" };

	long long int i, vsum, n;
	int *v;
	double elapsed, start, end;

	if(argc != 2){
		fprintf(stderr, "Usage: %s <number of elements>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	n = atoll(argv[1]);
	printf("number of elements: %lld\n", n);

	v = (int *) malloc(n * sizeof(int));
	assert(v != NULL);

	for(i = 0; i < n; i++)
		v[i] = 1; /* Do not change it! */


	
		start = omp_get_wtime();
		vsum = sum(v, n);
		end = omp_get_wtime();

	elapsed = end - start;
	
	printf("sum value is %s\ntime: %.3f seconds\n", awnser[vsum == n], elapsed);

	free(v);

	return 0;
}
