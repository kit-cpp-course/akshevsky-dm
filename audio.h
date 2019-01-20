#pragma once

#include "Filter.h"
#include <iostream>
#include <vector>

/* ласс, представл€ющий собой обощенное представление аудиосигнала*/
template<class T> class Audio
{
public:
	typedef std::vector<T> Samples; //определ€ем вектор значений как тип Samples


protected:
	std::size_t smpFreq;     // частота дискретизации
	std::size_t qntBit;      // "глубина звучани€"
	std::size_t length;      // длина сигнала
	Samples     samples;     // сэмплы 
	AudioFilter::Filter* correntFilter; //фильтр,которому делегируетс€ функци€ фильтровани€

public:
	//конструкторы

	//по умолчанию
	Audio()
		: smpFreq(0), qntBit(0), length(0)
	{
		samples.clear();
	}
	//параметризованный конструктор 
	Audio(std::size_t smpFreq, std::size_t qntBit, std::size_t length)
		: smpFreq(smpFreq), qntBit(qntBit), length(length)
	{
		samples.resize(length);
	}

	//конструктор копировани€
	Audio(const Audio<T> &signal){
		smpFreq = signal.smpFreq;
		qntBit = signal.qntBit;
		length = signal.length;
		samples = signal.samples;
	}
	//конструктор присваивани€
	Audio<T> &operator=(const Audio<T> &signal) {
		smpFreq = signal.smpFreq;
		qntBit = signal.qntBit;
		length = signal.length;
		samples = signal.samples;
		return (*this);
	}
	//деструктор
	~Audio() {}

	//функи€ измен€юща€ свойства аудиосигнала
	void chnangeProperties(std::size_t smpFreq_, std::size_t qntBit_, std::size_t length_) {
		smpFreq = smpFreq_;
		qntBit = qntBit_;
		length = length_;
		samples.resize(length_);
	}
	//ѕерегрузка оператора [] дл€ работы с сэмплами
	T operator[](std::size_t n) const {return samples[n];}
	T &operator[](std::size_t n) {return samples[n];}

	//методы, возвращающие характеристики объекта
	std::size_t signFreq() const{return smpFreq;} //возвращает частоту дискретизации

	std::size_t signBit() const {return qntBit;}//возвращает "глубину" звучани€

	std::size_t signLength() const {return length;}//возвращает длину сигнала

	Samples signSamples() const{return samples;}//возвращает сэмплы

    /*метод, фильрующий аудиофайл и делегирующий фильтрацию специальному классу Filter
	N - длина фильтра
	Fs - частота полосы пропускани€
	FilterType - тип фильтра 
    windFunc - оконна€ функци€ */
	
	int filtering( long double Fs, AudioFilter::Type FilterType, AudioFilter::weightFunc windFunc);
};

