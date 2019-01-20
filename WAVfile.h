#pragma once

#include "audio.h"
#include <fstream>

/*���cc, ����������� �� ������ "audio". � ������ ������ �������� ��������������
WAVE ����� � ��������� (��� ������������� ����� �������� ������, ������������
������������� ������ ��������)*/

class WAVfile : public Audio < double >
{
public:

	// ��������� WAVE ���������
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

	// ������������

	//�� ���������
	WAVfile();
	//����������������� 
	WAVfile(std::size_t spFreq, std::size_t qBit, std::size_t length);
	//����������� ����������� 
	WAVfile(const WAVfile &audio);
	// �������� ������������
	WAVfile &operator=(const WAVfile &audio);
	//����������
	~WAVfile();

	//��������� ������� �������� ������������� ����������
	int open(const std::string &filename);//������� ���������
	int save(const std::string &filename);//��������� ��������� 
}; 
