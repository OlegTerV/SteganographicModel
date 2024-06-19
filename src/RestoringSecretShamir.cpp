#include "RestoringSecretShamir.h"
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

System::Void Project1::RestoringSecretShamir::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	std::ofstream out("logs.txt");
	ap_int<2048> p = converter(msclr::interop::marshal_as<std::string>(textBox1->Text));
	ap_int<2048> k = converter(msclr::interop::marshal_as<std::string>(textBox5->Text));
	std::string doli = msclr::interop::marshal_as<std::string>(textBox3->Text);
	int kolkey = 0;
	for (int i = 0; i < doli.length(); i++) {
		if (doli[i] == '\n') {
			kolkey++;
		}
	}
	if (kolkey > 0) {
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
		if ((doli[i] == '\r') || ((i + 1) == doli.length())) {
			k_i[counter] = converter(value);
			out << "	val: " << value << "   conv: " << converter(value) << "\r\n";
			value.clear();
			counter++;
		}
	}

	k = k + 1;

	ap_int<2048> secret = 0;

	for (int i = 1; i <= kolkey; i++) {

		ap_int<2048> mult = k_i[i];
		for (int j = 1; j <= kolkey; j++) {
			if (d_i[i] == d_i[j]) { continue; }
			ap_int<2048> numerator = subtraction(0, d_i[j], p);

			ap_int<2048> denominator = subtraction(d_i[i], d_i[j], p);

			ap_int<2048> division = (numerator * get_reverse(denominator, p)) % p;//частное
			mult = (mult * division) % p;
		}
		secret = secret + mult;
	}
	secret = secret % p;
	std::string text_secret = converter_secret_to_text(secret);
	textBox4->Text = gcnew String(text_secret.c_str());
	
	return System::Void();
}

