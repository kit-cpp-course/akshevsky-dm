#include "Filter.h"
#include "audio.h"
#include <iostream>
#include <vector>


using std::vector;
using namespace AudioFilter;

int main(void) {
	Audio audio;
	audio.open("test.wav");

	vector<double> data;
	data.reserve(audio.signLength());
	for (unsigned int i = 0; i < audio.signLength(); i++) {
		data.push_back(audio[i]);
	}
	KIHfilter flt(44100, 20, 50);
	flt.filtering(&data);

	for (unsigned int i = 0; i < audio.signLength(); i++) {
		audio[i] = data[i];
	}
	audio.save("out.wav");
}