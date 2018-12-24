#pragma once

#include <iostream>
#include <vector>

template<class T> class Signal
{
public:
	typedef std::vector<T> Samples; //определ€ем вектор значений как тип Samples


protected:
	std::size_t smpFreq;    // частота дискретизации
	std::size_t qntBit;      // "глубина звучани€"
	std::size_t length;    // длина сигнала
	Samples     samples;   // сэмплы 

public:
	//конструкторы

	//по умолчанию
	Signal()
		: smpFreq(0), qntBit(0), length(0)
	{
		samples.clear();
	}
	Signal(std::size_t smpFreq, std::size_t qntBit, std::size_t length)
		: smpFreq(smpFreq), qntBit(qntBit), length(length)
	{
		samples.resize(length);
	}
	//конструктор копировани€
	Signal(const Signal<T> &signal)
	{
		smpFreq = signal.smpFreq;
		qntBit = signal.qntBit;
		length = signal.length;
		samples = signal.samples;
	}
	//конструктор присваивани€
	Signal<T> &operator=(const Signal<T> &signal)
	{
		smpFreq = signal.smpFreq;
		qntBit = signal.qntBit;
		length = signal.length;
		samples = signal.samples;
		return (*this);
	}
	//деструктор
	~Signal() {}

	void chnangeProperties(std::size_t smpFreq_, std::size_t qntBit_, std::size_t length_)
	{
		smpFreq = smpFreq_;
		qntBit = qntBit_;
		length = length_;
		samples.resize(length_);
	}

	T operator[](std::size_t n) const
	{
		return samples[n];
	}
	T &operator[](std::size_t n)
	{
		return samples[n];
	}
	//методы, возвращающие характеристики объекта
	std::size_t signFreq() const//возвращает частоту дискретизации
	{
		return smpFreq;
	}
	std::size_t signBit() const//возвращает "глубину" звучани€
	{
		return qntBit;
	}
	std::size_t signLength() const//возвращает длину сигнала
	{
		return length;
	}
	Samples signSamples() const//возвращает сэмплы
	{
		return samples;
	}

};

