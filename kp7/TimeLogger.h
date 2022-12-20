#pragma once
#include <iostream>
#include <fstream>
//#include <list>
//#include<deque>
#include <ctime>
#include <algorithm>
#include <chrono>


using namespace std;


class TimeLogger {
private:
	chrono::high_resolution_clock::time_point begin;	//���������� ��� ������� ������
	chrono::high_resolution_clock::time_point end;		//���������� ��� ������� �����
	chrono::duration<float> time;						// ���������� ��� ��������������� �������
	ofstream outFile;									//���� ��� ������
	ofstream fileR;

public:
	TimeLogger(const std::string& file_name) {
		time = std::chrono::seconds(0);
		fileR.open(file_name);
		fileR << "Container; Data_type; Operation; Number of elements; Time_value\n";
	}
	void start() {					//����� ������ �������

		begin = std::chrono::high_resolution_clock::now();
	}

	void finish() {					//����� ��������� ������� ������� � ������ � ����
		ofstream outFile;			// �������� ������� ��� �����
		outFile.open("logger.txt", ios::app);   // �������������� ��� � ������
		if (!outFile.is_open())		// �������� �� ���������� �������� �����
		{
			cout << "Could not open the file " << "logger.txt" << endl;
			cout << "Program terminating \n";
			exit(EXIT_FAILURE);
		}
		end = std::chrono::high_resolution_clock::now(); 	//�������� ����� ��������� ������ �������
		time = end - begin;			// ��������� �������������� �����
		outFile << time.count() << "\n";	// ���������� � ����
		outFile.close();			// ��������� ����
	}

	void log(const string& container, const string& dtype, const string& operation, const int& elements) {
		fileR << container << ";" << dtype << ";" << operation <<
			";" << elements << ";" << time.count() << "\n";
		time = std::chrono::seconds(0);
	}

};