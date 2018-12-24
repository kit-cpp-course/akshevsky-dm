#pragma once


#include <vector>

namespace AudioFilter {
	//������� ����� ������ ��� ���� ����� �������
	class Filter {
	public:
		virtual ~Filter() {};
		//����������, ���������� ����� ������� ���������� ��� ���� ����������� �������
		virtual void filtering(std::vector<double> *x) = 0;
	};

	/*�����, ����������� �� ������ Filter, �������� �����������
	������������� ���������� ������� ������ ������ � �������� ����������
	��������������� ������� �����������
	�� ������� ��������� ����� test.wav � ���������������� out.wav �� ����� ���������,
	��� ������ �������� ��������������� ���� � ���� �������� ������������,
	����� ���� ���� ����� ������������
	*/

	class KIHfilter : public Filter {
		const int N = 10; //����� �������
		long double Fd; //������� ������������� ������� ������
		long double Fs; //������� ������ �����������
		long double Fx; //������� ������ ���������

		long double H[10] = { 0 }; //���������� �������������� �������
		long double H_id[10] = { 0 };  //��������� ���������� ��������������
		long double W[10] = { 0 };  //������� �������
	public:
		KIHfilter(long double Fd, long double Fs, long double Fx)
			: Fd(Fd), Fs(Fs), Fx(Fx) {};
		void SetProperties();//����� �������������� �������
		void NormProperties();//����������
		void filtering(std::vector<double> *x);
	};
}

