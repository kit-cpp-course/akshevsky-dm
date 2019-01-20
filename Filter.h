#pragma once

#include <vector>

namespace AudioFilter {

	//������������ ���� �������� ���� ������� � ������� �������
	enum Type {LPF, HPF};
	enum weightFunc {Rectangular, Henning, Hamming, Blackman};

	/* ����������� ������� ����� (���������) ��� ���� ����� ������� (��� ������������� ����� ��������� 
	������, ����������� ������������� ������ �������*/
	class Filter {
	public:
		virtual ~Filter() {};
		//����������, ���������� ����� ������� ���������� ��� ���� ����������� �������
		virtual int filtering(std::vector<double> *x) = 0;
	};

	/*�����, ����������� �� ������ Filter, �������� �����������
	������������� ���������� ������� � �������� ����������
	��������������� ������� �����������
	�� ������� ��������� ����� test.wav � ���������������� out.wav �� ����� ���������,
	��� ������ �������� ��������������� ���� � ���� �������� ������������,
	����� ���� ���� ����� ������������*/

	class KIHfilter : public Filter {
		weightFunc windFunc; //������� �������
		Type FilterType;     //��� ������������� �������
	protected:
		int N = 20;               //����� ������� 
		long double Fd;      //������� �������������

		long double *H;      //���������� �������������� �������
		long double *H_id;   //��������� ���������� ��������������
		long double *W;      //������� �������
	public:
		//�����������
		KIHfilter( long double Fd, Type FilterType, weightFunc windFunc)
			:FilterType(FilterType), Fd(Fd), windFunc(windFunc),
			H(new long double[N]), H_id(new long double[N]), W(new long double[N]) {}
		//������������� 
		virtual ~ KIHfilter() {
			delete[] H;
			delete[] H_id;
			delete[] W;
		}
		int filtering(std::vector<double> *x);//����������
	protected:
		int SetWeightFunc();//������������ ������� �������
		int Normalization();//���������� �������������
		virtual int SetProperties() = 0;//��������� �������������� �������
	};

	//����� ������� ������ ������
	class LPFfilter : public KIHfilter {
		long double Fs;      //������� ������ �����������
		long double Fx = 20; //������� ������ ���������
	public:
		LPFfilter( long double Fd, long double Fs, Type FilterType, weightFunc windFunc) 
			:KIHfilter( Fd, FilterType, windFunc), Fs(Fs) {}
		int SetProperties();
	};

	//����� ������� ������� ������
	class HPFfilter : public KIHfilter {
		long double Fs;      //������� ������ �����������
		long double Fx = 50; //������� ������ ���������
	public:
		HPFfilter(long double Fd, long double Fs, Type FilterType, weightFunc windFunc)
			:KIHfilter(Fd, FilterType, windFunc), Fs(Fs) {}
		int SetProperties();
	};
}



