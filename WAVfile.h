#pragma once

#include "audio.h"
#include <fstream>

/*клаcc, наследуемый от класса "audio". В данном случае является представлением
WAVE файла в программе (при необходимости можно добавить классы, организующие
представления других форматов)*/

class WAVfile : public Audio < double >
{
public:

	// Структура WAVE заголовка
	typedef struct {
		unsigned int   id;       // "fmt "
		unsigned int   bytes;    // fmt chunk bytes
		unsigned short formatID; // format ID
		unsigned short channels; // channel number
		unsigned int   rate;     // sampling rate
		unsigned int   velocity; // data velocity
		unsigned short blocksize;// block size
		unsigned short bits;     // quantization bit number
	} fmtChunk;
	// WAVE data chunk
	typedef struct {
		unsigned int id;       // "data"
		unsigned int bytes;    // signal data bytes
	} dataChunk;
	// WAVE file(RIFF) header
	typedef struct {
		unsigned int riffID; // "riff"
		unsigned int size_8; // file size-8
		unsigned int wavID;  // "WAVE"
		fmtChunk fmtchunk;
		dataChunk datachunk;
	} WaveFileHeader;

	std::string filename;

public:

	// конструкторы

	//по умолчанию
	WAVfile();
	//параметризованный 
	WAVfile(std::size_t spFreq, std::size_t qBit, std::size_t length);
	//конструктор копирования 
	WAVfile(const WAVfile &audio);
	// оператор присваивания
	WAVfile &operator=(const WAVfile &audio);
	//деструктор
	~WAVfile();

	//созздание сложных обьектов представления аудиофайла
	int open(const std::string &filename);//открыть аудиофайл
	int save(const std::string &filename);//сохранить аудиофайл 
}; 
