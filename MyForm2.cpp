#include "MyForm2.h"
#include "functions.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <stdlib.h>		
#include <math.h>
#include <string>
#include <cstdlib>
#include <time.h> 
#include <ctime>
#include "ap/ap.hpp"
#include <chrono>
#include <random>
#include <algorithm>
#include <msclr\marshal_cppstd.h>  
sf::Image container2;

//Декодирует данные из изображения, начиная с пикселя №start 
std::pair <int, ap_int<2048>> decoding_parts(int start, int count_of_pieces, int number_of_part) {
	int columns = container2.getSize().y;
	int rows = container2.getSize().x;
	int columns_of_block = rows / count_of_pieces;
	ap_int<2048> code_message = 0;
	int length_of_message = 0;
	std::vector<int> length_message_binary_form(9);
	int index = 0;
	int i = start;
	int stop_flag = container2.getSize().x / count_of_pieces * container2.getSize().y - 1;
	//for (int i = start; i < start + 3; i++) {
	while ((i < start + 3) && (i < stop_flag)) {
		sf::Color pix = container2.getPixel(((i % columns_of_block) + columns_of_block * number_of_part), (i / columns_of_block));
		length_message_binary_form[index] = binary_form((int)pix.r)[7];
		index++;
		length_message_binary_form[index] = binary_form((int)pix.g)[7];
		index++;
		length_message_binary_form[index] = binary_form((int)pix.b)[7];
		index++;
		i++;
	}
	length_of_message = two_to_ten(length_message_binary_form);//получаем длину сообщения - количество бит
	length_of_message += (3 - length_of_message % 3) % 3;

	int count_of_pixels = length_of_message / 3;
	std::vector<int> message_binary_form(length_of_message);
	index = 0;
	//for (int i = start + 3; i < (start + count_of_pixels + 3); i++) {
	i = start + 3;
	while ((i < (start + count_of_pixels + 3)) && (i < stop_flag)) {
		sf::Color pix = container2.getPixel((i % columns_of_block) + columns_of_block * number_of_part, i / columns_of_block);
		message_binary_form[index] = binary_form((int)pix.r)[7];
		index++;
		message_binary_form[index] = binary_form((int)pix.g)[7];
		index++;
		message_binary_form[index] = binary_form((int)pix.b)[7];
		index++;
		i++;
	}

	for (int j = 0; j < length_of_message; j++) {
		code_message = code_message * 10 + message_binary_form[j];
	}

	return std::pair<int, ap_int<2048>>(start + count_of_pixels + 3, code_message);
}
//Декодирует сигнатуру из изображения
int decoding_signature(int start, int count_of_pieces, int number_of_part) {
	int columns = container2.getSize().y;
	int rows = container2.getSize().x;
	int stop_flag = container2.getSize().x / count_of_pieces * container2.getSize().y - 1;
	int columns_of_block = rows / count_of_pieces;
	int i = start;
	int flag1 = 0;
	int flag3 = 0;
	int num = 0;
	while ((flag3 != 3) && (i < stop_flag)) {
		sf::Color pix = container2.getPixel(((i % columns_of_block) + columns_of_block * number_of_part), (i / columns_of_block));
		num = binary_form((int)pix.r)[7] * 100;
		num += binary_form((int)pix.g)[7] * 10;
		num += binary_form((int)pix.b)[7];

		int num_chek = num;

		if (num == 111) {
			flag1 = 1;
		}
		else if ((num == 101) && (flag1 == 1)) {
			flag1 = 2;
		}
		else if ((num == 10) && (flag1 == 2)) {
			flag1 = 3;
		}
		else { flag1 = 0; flag3 = 0; }

		if (flag1 == 3) {
			flag3++;
			flag1 = 0;
		}
		i++;
	}

	return i;
}

System::Void Project1::MyForm2::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	OpenFileDialog^ open_dialog = gcnew OpenFileDialog; //создание диалогового окна для выбора файла
	open_dialog->Filter = "Image Files(*.BMP;*.JPG;*.GIF;*.PNG)|*.BMP;*.JPG;*.GIF;*.PNG|All files (*.*)|*.*";
	if (open_dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		pictureBox1->Image = gcnew Bitmap(open_dialog->FileName);
		container2.loadFromFile(msclr::interop::marshal_as<std::string>(open_dialog->FileName));

	}
	return System::Void();
}

System::Void Project1::MyForm2::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
	int n = Convert::ToInt32(numericUpDown1->Value);

	ap_int<2048>* d_i = new ap_int<2048>[n + 1]; //массив для долей
	ap_int<2048>* k_i = new ap_int<2048>[n + 1]; //массив для долей
	int next_pixel = 0;

	//Console::WriteLine("DECODE");

	for (int i = 0; i < n; i++) {
		std::pair<int, ap_int<2048>>aa;

		next_pixel = decoding_signature(0, n, i);
		//Console::WriteLine("Пиксель после сигнатуры: ");  Console::WriteLine(next_pixel);

		aa = decoding_parts(next_pixel, n, i);
		d_i[i + 1] = aa.second;
		//Console::WriteLine("Пиксель 1 числа: ");  Console::WriteLine(aa.first);

		aa = decoding_parts(aa.first, n, i);
		k_i[i + 1] = aa.second;

	}
	textBox2->Clear();
	ap_int<2048> crc = 0;
	ap_int<2048> crc_challenge = 0;
	int flag = 0;
	for (int i = 0; i < n; i++) {
		if (i != 0) {
			textBox2->Text += "\r\n";
		}


		crc = d_i[i + 1] % 100000000;
		d_i[i + 1] = d_i[i + 1] / 100000000;//доля без CRC
		d_i[i + 1] = to_dec(d_i[i + 1]);
		crc_challenge = crc_code(d_i[i + 1]);
		//crc_challenge = to_dec(crc_challenge);
		if (crc == crc_challenge) {
			flag++;
		}


		crc = k_i[i + 1] % 100000000;
		k_i[i + 1] = k_i[i + 1] / 100000000;//доля без CRC
		k_i[i + 1] = to_dec(k_i[i + 1]);
		crc_challenge = crc_code(k_i[i + 1]);
		//crc_challenge = to_dec(crc_challenge);
		if (crc == crc_challenge) {
			flag++;
		}
		//Console::WriteLine("1 число: "); Console::WriteLine((int)d_i[i + 1]);
		//Console::WriteLine("2 число: "); Console::WriteLine((int)k_i[i + 1]);

		std::string text_p = std::string(d_i[i + 1]);
		textBox2->Text += gcnew String(text_p.c_str());
		textBox2->Text += " ";

		text_p = std::string(k_i[i + 1]);
		textBox2->Text += gcnew String(text_p.c_str());

		if ((flag == 2) && (d_i[i + 1] != 0) && (k_i[i + 1] != 0)) {
			textBox2->Text += " (OK)";
		}
		else {
			textBox2->Text += " (BREAK)";
		}
		flag = 0;
	}

	return System::Void();
}