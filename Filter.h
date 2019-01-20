#pragma once

#include <vector>

namespace AudioFilter {

	//перечисления длля описания типа фильтра и оконной функции
	enum Type {LPF, HPF};
	enum weightFunc {Rectangular, Henning, Hamming, Blackman};

	/* Абстрактный базовый класс (интерфейс) для всех типов фильтра (при необходимости можно добавлять 
	модули, реализующие концептуально другие фильтры*/
	class Filter {
	public:
		virtual ~Filter() {};
		//фильтрация, являющаяся общим методом интерфейса для всех наследуемых классов
		virtual int filtering(std::vector<double> *x) = 0;
	};

	/*класс, наследуемый от класса Filter, является реализацией
	пропускающего частотного фильтра с конечной импульсной
	характеристикой методом взвешивания
	На примере исходного файла test.wav и отфильтровонного out.wav мы можем наблюдать,
	как фильтр обрезает высокочастотные шумы в виде визжания электрогитар,
	общий звук стал более приглушенным*/

	class KIHfilter : public Filter {
		weightFunc windFunc; //оконная функция
		Type FilterType;     //тип пропускающего фильтра
	protected:
		int N = 20;               //длина фильтра 
		long double Fd;      //частота дискретизации

		long double *H;      //Импульсная характеристика фильтра
		long double *H_id;   //Идеальная импульсная характеристика
		long double *W;      //Весовая функция
	public:
		//конструктор
		KIHfilter( long double Fd, Type FilterType, weightFunc windFunc)
			:FilterType(FilterType), Fd(Fd), windFunc(windFunc),
			H(new long double[N]), H_id(new long double[N]), W(new long double[N]) {}
		//деконструктор 
		virtual ~ KIHfilter() {
			delete[] H;
			delete[] H_id;
			delete[] W;
		}
		int filtering(std::vector<double> *x);//фильтрация
	protected:
		int SetWeightFunc();//сформировать оконную функцию
		int Normalization();//нормировка характеристик
		virtual int SetProperties() = 0;//вычислить характеристику фильтра
	};

	//класс фильтра нижних частот
	class LPFfilter : public KIHfilter {
		long double Fs;      //Частота полосы пропускания
		long double Fx = 20; //Частота полосы затухания
	public:
		LPFfilter( long double Fd, long double Fs, Type FilterType, weightFunc windFunc) 
			:KIHfilter( Fd, FilterType, windFunc), Fs(Fs) {}
		int SetProperties();
	};

	//класс фильтра верхних частот
	class HPFfilter : public KIHfilter {
		long double Fs;      //Частота полосы пропускания
		long double Fx = 50; //Частота полосы затухания
	public:
		HPFfilter(long double Fd, long double Fs, Type FilterType, weightFunc windFunc)
			:KIHfilter(Fd, FilterType, windFunc), Fs(Fs) {}
		int SetProperties();
	};
}



