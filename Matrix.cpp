#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
#include <omp.h>
#include <vector>

using namespace std;

int main() {

	double start_time = omp_get_wtime();
	const int n = 10000;

	std::vector< std::vector<int> >A(n, std::vector<int>(n));
	int x[n];
	int y[n];
	int sum[n] = { 0 };


	omp_set_num_threads(4);
#pragma omp parallel for schedule(dynamic)
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i][j] = rand() % 10;
		}
		y[i] = rand() % 10;
		x[i] = rand() % 10;
	}
#pragma omp parallel for schedule(dynamic)
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			sum[i] += A[i][j] * x[j];
		}
		y[i] = y[i] + sum[i];
	}

	printf("Time = %f",omp_get_wtime() - start_time);

	return 0;
}