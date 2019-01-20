#include "audio.h"
#include "Filter.h"
#include <iostream>
#include <vector>


int Audio<double>::filtering( long double Fs, AudioFilter::Type FilterType, AudioFilter::weightFunc windFunc) {
	switch (FilterType) {
	case(AudioFilter::LPF): correntFilter = new AudioFilter::LPFfilter(smpFreq, Fs, FilterType, windFunc); break;
	case(AudioFilter::HPF): correntFilter = new AudioFilter::HPFfilter(smpFreq, Fs, FilterType, windFunc); break;
	default:
		std::cerr << "This type don't supported" << std::endl;
		return 0;
	}

	if (correntFilter->filtering(&samples)) {
		std::cerr << "Filtration succesfully completed" << std::endl;
		return 1;
	}
	else {
		std::cerr << "Impossible to complete filtration" << std::endl;
		return 0;
	}

	delete[] correntFilter;
}