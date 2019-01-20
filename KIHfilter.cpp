#define _USE_MATH_DEFINES

#include "Filter.h"
#include <cmath>
#include <iostream>

using std::vector;

namespace AudioFilter {

	int KIHfilter::SetWeightFunc() {

		switch (windFunc)
		{
		case(Rectangular):
			for (int i = 0; i < N; i++) W[i] = 1; break;
		case(Henning):
			for (int i = 0; i < N; i++) W[i] = 0.5 + 0.5 * cosl((2 * M_PI*i) / N); break;
		case(Hamming):
			for (int i = 0; i < N; i++) W[i] = 0.54 + 0.46 * cosl((2 * M_PI*i) / N); break;
		case(Blackman):
			for (int i = 0; i < N; i++) W[i] = 0.42 - 0.5 * cosl((2 * M_PI*i) / (N - 1)) + 0.08 * cosl((4 * M_PI*i) / (N - 1));
		    break;
		default:
			std::cerr << "Weight Function don't exist" << std::endl;
			return 0;
		}
		return 1;
	}

	int KIHfilter::Normalization() {
		double SUM = 0;
		for (int i = 0; i<N; i++) SUM += H[i];
		for (int i = 0; i<N; i++) H[i] /= SUM; //сумма коэффициентов равна 1
		return 1;
	}

	int KIHfilter::filtering(std::vector<double> *x) {
		vector<double> &in = *x;
		vector<double> out(in.size());//буферный вектор 

		SetWeightFunc();
		SetProperties();
		Normalization();

		for (int i = 0; i < in.size(); i++) {
			out[i] = 0;
			for (int j = 0; j < N - 1; j++)
				if ((i - j) >= 0)
				{
					out[i] += H[j] * in[i - j];
				}
		}
		for (int i = 0; i < in.size(); i++) {
			in[i] = out[i];//копирование значений из буферного вектора
		}
		return 1;
	}

	int LPFfilter::SetProperties() {
		double Fc = (Fs + Fx) / (2 * Fd);
		for (int i = 0; i < N; i++) {
			if (i == 0) H_id[i] = 2 * M_PI * Fc;
			else H_id[i] = sinl(2 * M_PI*Fc*i) / (M_PI*i);
			H[i] = H_id[i] * W[i];
		}; 
		return 1;
	}

	int HPFfilter::SetProperties() {
		double Fc = (Fs + Fx) / (2 * Fd);
		for (int i = 0; i < N; i++) {
			if (i == 0) H_id[i] = 1 - Fc * 2 * M_PI;
			else H_id[i] = -sinl(2 * M_PI*Fc*i) / (M_PI*i);
			H[i] = H_id[i] * W[i];
		}; 
		return 1;
	}
}
