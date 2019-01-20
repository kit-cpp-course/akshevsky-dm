
#include "WAVfile.h"
#include <fstream>


WAVfile::WAVfile()
	: Audio(0, 0, 0){}

WAVfile::WAVfile(std::size_t smpFreq, std::size_t qntBit, std::size_t length)
	: Audio(smpFreq, qntBit, length) {}

WAVfile::WAVfile(const WAVfile &audio) {
	smpFreq = audio.smpFreq;
	qntBit = audio.qntBit;
	length = audio.length;
	samples = audio.samples;
	filename = audio.filename;
}
WAVfile& WAVfile::operator=(const WAVfile &audio) {
	smpFreq = audio.smpFreq;
	qntBit = audio.qntBit;
	length = audio.length;
	samples = audio.samples;
	filename = audio.filename;
	return (*this);
}
WAVfile::~WAVfile() {}

int WAVfile::open(const std::string &filename) {
	short data;
	WaveFileHeader header;
	std::ifstream inputAudio;
	inputAudio.open(filename, std::ios::in | std::ios::binary);
	if (!inputAudio) {
		std::cerr << "audio file not exist" << std::endl;
		return 0;
	}
	// установить имя  файла
	this->filename = filename;
	// прочиатать заголовок файла
	inputAudio.read(reinterpret_cast<char*>(&header), sizeof(header));

	// информация из заголовка
	smpFreq = header.fmtchunk.rate;
	qntBit = header.fmtchunk.bits;
	length = (header.size_8 - 36) / 2;
	samples.resize(length);

	//если битрейт 8 бит то выдаем ошибку
	if (qntBit == 8) {
		std::cerr << "this function handles only 16 bits wav file" << std::endl;
		return 0;
	}

	// считываем сырые данные после заголовка
	for (std::size_t n = 0; n < samples.size(); ++n) {
		inputAudio.read(reinterpret_cast<char*>(&data), sizeof(short));
		samples[n] = data;
	}
	std::cerr << "File succesfully load" << std::endl;
	return 1;
}
int WAVfile::save(const std::string &filename) {
	std::ofstream outputAudio;
	outputAudio.open(filename, std::ios::out | std::ios::binary);
	if (!outputAudio) {
		std::cout << "Exception at: " << __FUNCTION__ << std::endl;
		return 0;
	}

	//обьявляем элементы заголовка WAF файла
	char riff_chunk_ID[4];
	long riff_chunk_size;
	char riff_form_type[4];
	char fmt_chunk_ID[4];
	long fmt_chunk_size;
	short fmt_wave_format_type;
	short fmt_channel;
	long fmt_samples_per_sec;
	long fmt_bytes_per_sec;
	short fmt_block_size;
	short fmt_quantizationBitRate_per_sample;
	char data_chunk_ID[4];
	long data_chunk_size;
	short data;

	riff_chunk_ID[0] = 'R';
	riff_chunk_ID[1] = 'I';
	riff_chunk_ID[2] = 'F';
	riff_chunk_ID[3] = 'F';

	riff_form_type[0] = 'W';
	riff_form_type[1] = 'A';
	riff_form_type[2] = 'V';
	riff_form_type[3] = 'E';

	fmt_chunk_ID[0] = 'f';
	fmt_chunk_ID[1] = 'm';
	fmt_chunk_ID[2] = 't';
	fmt_chunk_ID[3] = ' ';

	fmt_chunk_size = 16;
	fmt_wave_format_type = 1;

	fmt_samples_per_sec = smpFreq;
	fmt_quantizationBitRate_per_sample = qntBit;

	data_chunk_ID[0] = 'd';
	data_chunk_ID[1] = 'a';
	data_chunk_ID[2] = 't';
	data_chunk_ID[3] = 'a';

	riff_chunk_size = 36 + length * 2;
	fmt_channel = 2;
	fmt_bytes_per_sec = smpFreq * qntBit / 8;
	fmt_block_size = qntBit / 8;
	data_chunk_size = length * 2;

	// записываем заголовок
	outputAudio.write(riff_chunk_ID, 4);
	outputAudio.write(reinterpret_cast<char*>(&riff_chunk_size), 4);
	outputAudio.write(riff_form_type, 4);
	outputAudio.write(fmt_chunk_ID, 4);
	outputAudio.write(reinterpret_cast<char*>(&fmt_chunk_size), 4);
	outputAudio.write(reinterpret_cast<char*>(&fmt_wave_format_type), 2);
	outputAudio.write(reinterpret_cast<char*>(&fmt_channel), 2);
	outputAudio.write(reinterpret_cast<char*>(&fmt_samples_per_sec), 4);
	outputAudio.write(reinterpret_cast<char*>(&fmt_bytes_per_sec), 4);
	outputAudio.write(reinterpret_cast<char*>(&fmt_block_size), 2);
	outputAudio.write(reinterpret_cast<char*>(&fmt_quantizationBitRate_per_sample), 2);
	outputAudio.write(data_chunk_ID, 4);
	outputAudio.write(reinterpret_cast<char*>(&data_chunk_size), 4);

	// записываем данные 
	for (std::size_t n = 0; n<length; ++n) {
		data = static_cast<short>(samples[n]);
		outputAudio.write(reinterpret_cast<char*>(&data), sizeof(short));
	}

	std::cerr << "File succesfully save" << std::endl;
	return 1;
}