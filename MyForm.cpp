#include "MyForm.h"
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

sf::Image container;
sf::Image container_red;

//¬страивает данные в пиксели. 
int coding_Asmuth_Bloom(ap_int<2048> message, int start, int count_of_pieces, int number_of_part) {
	int rows = container.getSize().x;
	int columns = container.getSize().y;

	int columns_of_block = rows / count_of_pieces; //кол-во колонок в блоке
	int help_value = start;
	int message_length = length_of_bit(message);

	message_length += (3 - message_length % 3) % 3;
	////////////////////////////////////////////////////запись длины сообщени€////////////////////////////////////////////////////
	std::vector<int> length_message(9);
	length_message = binary_form_length_of_value(message_length);
	//1 (int)pixel (красный = 0 на конце всегда)
	sf::Color pix = container.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
	int help_color = change(pix.r, length_message[0]);
	pix.r = help_color;
	help_color = change((int)pix.g, length_message[1]);
	pix.g = help_color;
	help_color = change((int)pix.b, length_message[2]);
	pix.b = help_color;
	container.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

	//2 (int)pixel
	help_value++;
	pix = container.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
	help_color = change((int)pix.r, length_message[3]);
	pix.r = help_color;
	help_color = change((int)pix.g, length_message[4]);
	pix.g = help_color;
	help_color = change((int)pix.b, length_message[5]);
	pix.b = help_color;
	container.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

	//3 (int)pixel
	help_value++;
	pix = container.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
	help_color = change((int)pix.r, length_message[6]);
	pix.r = help_color;
	help_color = change((int)pix.g, length_message[7]);
	pix.g = help_color;
	help_color = change((int)pix.b, length_message[8]);
	pix.b = help_color;
	container.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

	////////////////////////////////////////////////////запись длины сообщени€////////////////////////////////////////////////////
	help_value = start + 3;

	ap_int<2048> ten_power = 1;
	for (int i = 0; i < message_length; i++) {
		ten_power *= 10;
	}
	int dop_flag = 0;
	std::vector<int> num_for_first(3);
	if (message_length % 3 == 1) {
		num_for_first[0] = 0;
		num_for_first[1] = 0;
		num_for_first[2] = (int)(message / (ten_power / 10));
		ten_power /= 10;
		message = message % ten_power;
		dop_flag++;
		message_length -= 1;
	}
	if (message_length % 3 == 2) {
		num_for_first[0] = 0;
		num_for_first[1] = (int)(message / (ten_power / 10));
		num_for_first[2] = (int)(message / (ten_power / 100)) % 10;
		ten_power /= 100;
		message = message % ten_power;
		dop_flag++;
		message_length = -2;
	}
	if (dop_flag == 1) {
		pix = container.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
		help_color = change((int)pix.r, num_for_first[0]);
		pix.r = help_color;
		help_color = change((int)pix.g, num_for_first[1]);
		pix.g = help_color;
		help_color = change((int)pix.b, num_for_first[2]);
		pix.b = help_color;
		container.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);
		help_value++;
	}

	while (message_length > 0) {
		std::vector<int> num(3);
		num[0] = int(message / (ten_power / 10));
		num[1] = int((message / (ten_power / 100)) % 10);
		num[2] = int((message / (ten_power / 1000)) % 10);
		ten_power /= 1000;
		message = message % ten_power;
		sf::Color pix = container.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
		int help_color = change((int)pix.r, num[0]);
		pix.r = help_color;
		help_color = change((int)pix.g, num[1]);
		pix.g = help_color;
		help_color = change((int)pix.b, num[2]);
		pix.b = help_color;
		container.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);
		help_value++;
		message_length -= 3;
	}
	return help_value;
}
//ѕиксели, в которые были встроены данные красит красным цветом
int coding_red_Asmuth_Bloom(ap_int<2048> message, int start, int count_of_pieces, int number_of_part) {
	int rows = container_red.getSize().x;
	int columns = container_red.getSize().y;

	int columns_of_block = rows / count_of_pieces; //кол-во колонок в блоке
	int help_value = start;
	int message_length = length_of_bit(message);

	message_length += (3 - message_length % 3) % 3;
	////////////////////////////////////////////////////запись длины сообщени€////////////////////////////////////////////////////
	std::vector<int> length_message(9);
	length_message = binary_form_length_of_value(message_length);
	//1 (int)pixel (красный = 0 на конце всегда)
	sf::Color pix = container_red.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
	pix.r = 255;
	pix.g = 0;
	pix.b = 0;
	container_red.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

	//2 (int)pixel
	help_value++;
	pix = container_red.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
	pix.r = 255;
	pix.g = 0;
	pix.b = 0;
	container_red.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

	//3 (int)pixel
	help_value++;
	pix = container_red.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
	pix.r = 255;
	pix.g = 0;
	pix.b = 0;
	container_red.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

	////////////////////////////////////////////////////запись длины сообщени€////////////////////////////////////////////////////
	help_value = start + 3;

	ap_int<2048> ten_power = 1;
	for (int i = 0; i < message_length; i++) {
		ten_power *= 10;
	}
	int dop_flag = 0;
	std::vector<int> num_for_first(3);
	if (message_length % 3 == 1) {
		num_for_first[0] = 0;
		num_for_first[1] = 0;
		num_for_first[2] = (int)(message / (ten_power / 10));
		ten_power /= 10;
		message = message % ten_power;
		dop_flag++;
		message_length -= 1;
	}
	if (message_length % 3 == 2) {
		num_for_first[0] = 0;
		num_for_first[1] = (int)(message / (ten_power / 10));
		num_for_first[2] = (int)(message / (ten_power / 100)) % 10;
		ten_power /= 100;
		message = message % ten_power;
		dop_flag++;
		message_length = -2;
	}
	if (dop_flag == 1) {
		pix = container_red.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
		pix.r = 255;
		pix.g = 0;
		pix.b = 0;
		container_red.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);
		help_value++;
	}

	while (message_length > 0) {
		std::vector<int> num(3);
		num[0] = int(message / (ten_power / 10));
		num[1] = int((message / (ten_power / 100)) % 10);
		num[2] = int((message / (ten_power / 1000)) % 10);
		ten_power /= 1000;
		message = message % ten_power;
		sf::Color pix = container_red.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
		pix.r = 255;
		pix.g = 0;
		pix.b = 0;
		container_red.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);
		help_value++;
		message_length -= 3;
	}
	return help_value;
}
//ѕиксели, в которые была встроена сигнатура красит зеленым цветом
int coding_sinature_Asmuth_Bloom(ap_int<2048> message, int start, int count_of_pieces, int number_of_part) {
	int rows = container.getSize().x;
	int columns = container.getSize().y;

	int columns_of_block = rows / count_of_pieces; //кол-во колонок в блоке

	////////////////////////////////////////////////////запись длины сообщени€////////////////////////////////////////////////////
	int help_value = start;

	for (int i = 0; i < 3; i++) {
		sf::Color pix = container.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
		int help_color = change((int)pix.r, 1);
		pix.r = help_color;
		help_color = change((int)pix.g, 1);
		pix.g = help_color;
		help_color = change((int)pix.b, 1);
		pix.b = help_color;
		container.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

		pix = container_red.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
		pix.r = 0;
		pix.g = 255;
		pix.b = 0;
		container_red.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

		help_value++;

		pix = container.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
		help_color = change((int)pix.r, 1);
		pix.r = help_color;
		help_color = change((int)pix.g, 0);
		pix.g = help_color;
		help_color = change((int)pix.b, 1);
		pix.b = help_color;
		container.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

		pix = container_red.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
		pix.r = 0;
		pix.g = 255;
		pix.b = 0;
		container_red.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

		help_value++;


		pix = container.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
		help_color = change((int)pix.r, 0);
		pix.r = help_color;
		help_color = change((int)pix.g, 1);
		pix.g = help_color;
		help_color = change((int)pix.b, 0);
		pix.b = help_color;
		container.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

		pix = container_red.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
		pix.r = 0;
		pix.g = 255;
		pix.b = 0;
		container_red.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

		help_value++;
	}

	return help_value;
}

System::Void Project1::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	OpenFileDialog^ open_dialog = gcnew OpenFileDialog; //создание диалогового окна дл€ выбора файла
	open_dialog->Filter = "Image Files(*.BMP;*.JPG;*.GIF;*.PNG)|*.BMP;*.JPG;*.GIF;*.PNG|All files (*.*)|*.*";
	if (open_dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		pictureBox1->Refresh();
		pictureBox1->Image = gcnew Bitmap(open_dialog->FileName);
		//container.loadFromFile("C:\\");
		container.loadFromFile(msclr::interop::marshal_as<std::string>(open_dialog->FileName)); 
		container_red.loadFromFile(msclr::interop::marshal_as<std::string>(open_dialog->FileName));
	}

	return System::Void();
}

System::Void Project1::MyForm::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
	srand(time(NULL));
	textBox2->Text = "¬ процессе...";
	std::string m_text = msclr::interop::marshal_as<std::string>(textBox1->Text);
	ap_int<2048> m = convert_secret(m_text);

	ap_int<2048> p;
	//m = convert_secret(m_text);
	//m = converter(m_text);
	int kold = Convert::ToInt32(numericUpDown1->Value);
	int kolkey = Convert::ToInt32(numericUpDown2->Value);

	int length_of_cod = (length_of_bit(binary_form_of_value(p))+8)*2* kold;
	
	if (length_of_cod > container.getSize().x * container.getSize().y) {
		textBox2->Text = "Ќе удалось закодировать доли!";
		button3->Enabled = false;

	}

	else {
		while (true) {//вычисл€ем p
			p = random(m + 1, m * 2);
			if (ferma(p) == true) {
				break;
			}
		}

		ap_int<2048> timet = 1;
		ap_int<2048> timet2 = p;
		ap_int<2048> mp = p * rand();
		ap_int<2048> b = 9;
		ap_int<2048>* dd = new ap_int<2048>[kold + 1];
		//cout << "Ќачинаетс€ вычисление d: ";
		int nabor = 1;

		while (true) {
			for (int i = 1; i <= kold; i++) {

				while (true) {
					if (ferma(b) == true) {
						break;
					}
					b = random(mp + 1, mp * 3);
				}

				dd[i] = b;
				mp = dd[i];
				b = 9;
			}
			nabor++;
			for (int a = (kold - kolkey + 2); a <= kold; a++) {
				timet2 = timet2 * dd[a];
			}

			for (int a = 1; a <= kolkey; a++) {
				timet = timet * dd[a];
			}
			if (timet > timet2) {
				break;
			}
			timet = 1;
			timet2 = p;
			mp = p;
			b = 9;
		}

		//cout << endl;
		int r = rand();
		//cout << "rand_num' =  " << rr << endl;
		ap_int<2048> Ms = m + r * p * rand();
		ap_int<2048>* doli = new ap_int<2048>[kold + 1]; //массив дл€ долей
		for (int i = 1; i <= kold; i++) {
			doli[i] = Ms % dd[i];
		}

		ap_int<2048> long_dolya_bits = -1;
		ap_int<2048> most_long_dolya_bits = -1;
		for (int i = 1; i <= kold; i++) {
			//length_of_cod = length_of_bit(binary_form_of_value(dd[i])) + length_of_bit(binary_form_of_value(doli[i])) + length_of_cod;
			long_dolya_bits = length_of_bit(binary_form_of_value(dd[i])) + length_of_bit(binary_form_of_value(doli[i]));
			if (most_long_dolya_bits < long_dolya_bits) {
				most_long_dolya_bits = long_dolya_bits;
			}
		}
		most_long_dolya_bits = most_long_dolya_bits + 8 + 8 + 9 * 3;
		ap_int<2048> most_long_dolya_pixels = most_long_dolya_bits / 3;
		if ((most_long_dolya_bits % 3) != 0) {
			most_long_dolya_pixels++;
		}
		std::string message;
		int next_pixel = 0;
		int next_pixel_red = 0;
		int koef_rand = 0;
		ap_int<2048> crc = 0;
		int counter = 0;
		for (int i = 1; i <= kold; i++) {
			koef_rand = (int)random(0, container.getSize().x / kold * container.getSize().y - most_long_dolya_pixels - 1);

			next_pixel = coding_sinature_Asmuth_Bloom(0 , koef_rand, kold, counter);
			next_pixel_red = coding_sinature_Asmuth_Bloom(0 , koef_rand, kold, counter);

			crc = crc_code(dd[i]);
			ap_int<2048> message = binary_form_of_value(dd[i]) * 100000000 + crc;
			next_pixel = coding_Asmuth_Bloom(message, next_pixel, kold, counter);
			next_pixel_red = coding_red_Asmuth_Bloom(message, next_pixel_red, kold, counter);


			crc = crc_code(doli[i]);
			message = binary_form_of_value(doli[i]) * 100000000 + crc;
			coding_Asmuth_Bloom(message, next_pixel, kold, counter);
			coding_red_Asmuth_Bloom(message, next_pixel_red, kold, counter);
			counter++;
		}
		container.saveToFile("picture_with_message.png");
		container_red.saveToFile("picture_with_message_red_AB.png");

		std::string text_p = std::string(p);
		textBox2->Text = " артинка успешно сохранена!";
		textBox3->Text = gcnew String(text_p.c_str());
		button3->Enabled = true;
		delete[] dd;
		delete[] doli;
	}
	return System::Void();
}

System::Void Project1::MyForm::button3_Click(System::Object^ sender, System::EventArgs^ e)
{
	SaveFileDialog^ open_dialog = gcnew SaveFileDialog;
	open_dialog->Filter = "PNG Image|*.png";
	if (open_dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		container.saveToFile(msclr::interop::marshal_as<std::string>(open_dialog->FileName));
	}
	return System::Void();
}
