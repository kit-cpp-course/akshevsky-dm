
#define _USE_MATH_DEFINES

#include "Filter.h"
#include <cmath>

using std::vector;

namespace AudioFilter {

	void KIHfilter::SetProperties() {
		double Fc = (Fs + Fx) / (2 * Fd);

		for (int i = 0; i<N; i++)
		{
			if (i == 0) H_id[i] = 2 * M_PI*Fc;
			else H_id[i] = sinl(2 * M_PI*Fc*i) / (M_PI*i);
			// весовая функция Блекмена
			W[i] = 0.42 - 0.5 * cosl((2 * M_PI*i) / (N - 1)) + 0.08 * cosl((4 * M_PI*i) / (N - 1));
			H[i] = H_id[i] * W[i];
		}
	}

	void KIHfilter::NormProperties() {
		double SUM = 0;
		for (int i = 0; i<N; i++) SUM += H[i];
		for (int i = 0; i<N; i++) H[i] /= SUM; //сумма коэффициентов равна 1 
	}

	void KIHfilter::filtering(std::vector<double> *x) {
		vector<double> &in = *x;
		vector<double> out(in.size());

		SetProperties();
		NormProperties();
		//свертка импульсно-временной характеристики с оконной функцией
		for (int i = 0; i < in.size(); i++) {
			out[i] = 0;
			for (int j = 0; j < N - 1; j++)
				if ((i - j) >= 0)
				{
					out[i] += H[j] * in[i - j];
				}
		}
		for (unsigned int i = 0; i < in.size(); i++) {
			in[i] = out[i];
		}
	}
}
