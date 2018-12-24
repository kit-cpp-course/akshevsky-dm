#pragma once


#include <vector>

namespace AudioFilter {
	//базовый класс фильтр для всех типов фильтра
	class Filter {
	public:
		virtual ~Filter() {};
		//фильтрация, являющаяся общим методом интерфейса для всех наследуемых классов
		virtual void filtering(std::vector<double> *x) = 0;
	};

	/*класс, наследуемый от класса Filter, является реализацией
	пропускающего частотного фильтра нижних частот с конечной импульсной
	характеристикой методом взвешивания
	На примере исходного файла test.wav и отфильтровонного out.wav мы можем наблюдать,
	как фильтр обрезает высокочастотные шумы в виде визжания электрогитар,
	общий звук стал более приглушенным
	*/

	class KIHfilter : public Filter {
		const int N = 10; //Длина фильтра
		long double Fd; //Частота дискретизации входных данных
		long double Fs; //Частота полосы пропускания
		long double Fx; //Частота полосы затухания

		long double H[10] = { 0 }; //Импульсная характеристика фильтра
		long double H_id[10] = { 0 };  //Идеальная импульсная характеристика
		long double W[10] = { 0 };  //Весовая функция
	public:
		KIHfilter(long double Fd, long double Fs, long double Fx)
			: Fd(Fd), Fs(Fs), Fx(Fx) {};
		void SetProperties();//рачет характеристики фильтра
		void NormProperties();//нормировка
		void filtering(std::vector<double> *x);
	};
}

