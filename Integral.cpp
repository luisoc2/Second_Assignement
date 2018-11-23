#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <omp.h>

using namespace std;

int main() {

	double start_time = omp_get_wtime();
	int n = 100000000;
	double deltaX = 1.0 / n;
	double Area = 0.0;
	double x[] = { 0.0 , 0.0 };
	double f[] = { 4.0 , 0.0 };

	omp_set_num_threads(8);
	#pragma omp parallel for reduction (+:Area) private (x,f)
	for (int i = 1; i <= n; i++)
	{
		x[1] = float(i) * deltaX;
		f[1] = 4.0 / (1.0 + x[1] * x[1]);
		Area += 0.5 * (f[1] + f[0]) * deltaX;
		x[0] = x[1];
		f[0] = f[1];
	}

	cout.precision(14);
	cout << "Area = " << Area << "\n Time = " << (omp_get_wtime() - start_time);
	cin.get();

	return 0;
}