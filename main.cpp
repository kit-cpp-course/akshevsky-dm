#include "WAVfile.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream> 

using std::vector;
using namespace AudioFilter;

int main(int argc, char *argv[]) {
	if (argc == 1) {
		std::cerr << "Enter input and output files and  filtration type " << std::endl;
		return 0;
	}
	int params[3];
	for (int i = 1; i < 4; i++) {
		std::stringstream convert(argv[i]);
		if (!(convert >> params[i]))         // ������ �����������
			return 0;                        // ���� ����������� ������ �������, �� �������
	}
	WAVfile audio;
	audio.open;
	audio.filtering(params[1], (Type)params[2], (weightFunc)params[3]);
	audio.save(argv[5]);
	return 1;
}