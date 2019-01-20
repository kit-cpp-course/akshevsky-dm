#pragma once

#include "Filter.h"
#include <iostream>
#include <vector>

/*�����, �������������� ����� ��������� ������������� ������������*/
template<class T> class Audio
{
public:
	typedef std::vector<T> Samples; //���������� ������ �������� ��� ��� Samples


protected:
	std::size_t smpFreq;     // ������� �������������
	std::size_t qntBit;      // "������� ��������"
	std::size_t length;      // ����� �������
	Samples     samples;     // ������ 
	AudioFilter::Filter* correntFilter; //������,�������� ������������ ������� ������������

public:
	//������������

	//�� ���������
	Audio()
		: smpFreq(0), qntBit(0), length(0)
	{
		samples.clear();
	}
	//����������������� ����������� 
	Audio(std::size_t smpFreq, std::size_t qntBit, std::size_t length)
		: smpFreq(smpFreq), qntBit(qntBit), length(length)
	{
		samples.resize(length);
	}

	//����������� �����������
	Audio(const Audio<T> &signal){
		smpFreq = signal.smpFreq;
		qntBit = signal.qntBit;
		length = signal.length;
		samples = signal.samples;
	}
	//����������� ������������
	Audio<T> &operator=(const Audio<T> &signal) {
		smpFreq = signal.smpFreq;
		qntBit = signal.qntBit;
		length = signal.length;
		samples = signal.samples;
		return (*this);
	}
	//����������
	~Audio() {}

	//������ ���������� �������� ������������
	void chnangeProperties(std::size_t smpFreq_, std::size_t qntBit_, std::size_t length_) {
		smpFreq = smpFreq_;
		qntBit = qntBit_;
		length = length_;
		samples.resize(length_);
	}
	//���������� ��������� [] ��� ������ � ��������
	T operator[](std::size_t n) const {return samples[n];}
	T &operator[](std::size_t n) {return samples[n];}

	//������, ������������ �������������� �������
	std::size_t signFreq() const{return smpFreq;} //���������� ������� �������������

	std::size_t signBit() const {return qntBit;}//���������� "�������" ��������

	std::size_t signLength() const {return length;}//���������� ����� �������

	Samples signSamples() const{return samples;}//���������� ������

    /*�����, ���������� ��������� � ������������ ���������� ������������ ������ Filter
	N - ����� �������
	Fs - ������� ������ �����������
	FilterType - ��� ������� 
    windFunc - ������� ������� */
	
	int filtering( long double Fs, AudioFilter::Type FilterType, AudioFilter::weightFunc windFunc);
};

