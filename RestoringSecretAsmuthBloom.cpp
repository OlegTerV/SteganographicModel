#include "RestoringSecretAsmuthBloom.h"
#include "functions.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <stdlib.h>		
#include <math.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h> 
#include <ctime>
#include "ap/ap.hpp"
#include <chrono>
#include <random>
#include <algorithm>
#include <msclr\marshal_cppstd.h>  

using namespace System;
using namespace System::Windows::Forms;

System::Void Project1::RestoringSecretAsmuthBloom::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	std::ofstream out("logs.txt");
    ap_int<2048> p = converter(msclr::interop::marshal_as<std::string>(textBox1->Text));

    std::string doli = msclr::interop::marshal_as<std::string>(textBox3->Text);
	int kolkey = 0;
	for (int i = 0; i < doli.length(); i++) {
		if (doli[i] == '\n') {
			kolkey++;
		}
	}
	if (kolkey >0) {
		kolkey++;
	}
	
	ap_int<2048>* d_i = new ap_int<2048>[kolkey + 1]; //массив для долей
	ap_int<2048>* k_i = new ap_int<2048>[kolkey + 1]; //массив для долей

	std::string value;
	int counter = 1;
	for (int i = 0; i < doli.length(); i++) {
		if ((doli[i] != ' ') && (doli[i] != '\n') && (doli[i] != '\0') && (doli[i] != '\r')) {
			value.push_back(doli[i]);
		}
		if (doli[i] == ' ') {
			d_i[counter] = converter(value);
			out << "val: " << value << "   conv: " << converter(value);
			value.clear();
		}
		if ((doli[i] == '\r')|| ((i+1) == doli.length())) {
			k_i[counter] = converter(value);
			out << "	val: " << value << "   conv: " << converter(value) << "\r\n";
			value.clear();
			counter++;
		}
	}
	
	ap_int<2048> mmal = 1;
	for (int i = 1; i <= kolkey; i++) {
		mmal = mmal * d_i[i];
	}
	ap_int<2048>* mm = new ap_int<2048>[kolkey + 1];
	for (int i = 1; i <= kolkey; i++) {
		mm[i] = (mmal - (mmal % d_i[i])) / d_i[i];
	}

	ap_int<2048> a0, a1, x0, y0, x1, y1, ai, xi, yi;
	ap_int<2048> b0;
	ap_int<2048> b1;
	ap_int<2048> zero = 0;
	ap_int<2048>* mminus1 = new ap_int<2048>[kolkey + 1];
	for (int i = 1; i <= kolkey; i++) {
		b0 = mm[i];
		b1 = d_i[i];
		a0 = mm[i];
		a1 = d_i[i];
		ai = 1;
		x0 = 1;
		y0 = 0;
		x1 = 0;
		y1 = 1;
		xi = 0;
		yi = 0;
		while (ai != zero) {
			ai = a0 % a1;
			xi = x0 - x1 * (a0 / a1);
			yi = y0 - y1 * (a0 / a1);
			a0 = a1;
			a1 = ai;
			x0 = x1;
			x1 = xi;
			y0 = y1;
			y1 = yi;
		}
		while (x0 < zero) {
			x0 = x0 + b1;
		}
		mminus1[i] = x0;
	}

	ap_int<2048> x = 0;
	for (int i = 1; i <= kolkey; i++) {
		x = mminus1[i] * k_i[i] * mm[i] + x;
	}
	ap_int<2048> secret_value = ((x % mmal) % p);
	//std::string secret = std::string(secret_value);
	std::string secret = converter_secret_to_text(secret_value);
	textBox4->Text= gcnew String(secret.c_str());
    


	delete[] mm;
	delete[] mminus1;
	delete[] d_i;
	delete[] k_i;
	return System::Void();
}
