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
	chrono::high_resolution_clock::time_point begin;	//переменная для времени начала
	chrono::high_resolution_clock::time_point end;		//переменная для времени конца
	chrono::duration<float> time;						// переменная для результирующего времени
	ofstream outFile;									//файл для записи
	ofstream fileR;

public:
	TimeLogger(const std::string& file_name) {
		time = std::chrono::seconds(0);
		fileR.open(file_name);
		fileR << "Container; Data_type; Operation; Number of elements; Time_value\n";
	}
	void start() {					//метод начала отсчета

		begin = std::chrono::high_resolution_clock::now();
	}

	void finish() {					//метод окончания отсчета времени и записи в файл
		ofstream outFile;			// Создание объекта для ввода
		outFile.open("logger.txt", ios::app);   // Ассоциирование его с файлом
		if (!outFile.is_open())		// проверка на корректное открытие файла
		{
			cout << "Could not open the file " << "logger.txt" << endl;
			cout << "Program terminating \n";
			exit(EXIT_FAILURE);
		}
		end = std::chrono::high_resolution_clock::now(); 	//отмечаем время окончания работы функции
		time = end - begin;			// вычисляем результирующее время
		outFile << time.count() << "\n";	// записываем в файл
		outFile.close();			// закрываем файл
	}

	void log(const string& container, const string& dtype, const string& operation, const int& elements) {
		fileR << container << ";" << dtype << ";" << operation <<
			";" << elements << ";" << time.count() << "\n";
		time = std::chrono::seconds(0);
	}

};