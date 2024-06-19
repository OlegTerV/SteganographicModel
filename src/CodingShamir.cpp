#include "CodingShamir.h"
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

using namespace System;
using namespace System::Windows::Forms;

sf::Image container_4;
sf::Image container_red_4;

//Встраивает данные в пиксели. 
int coding_Shamir(ap_int<2048> message, int start, int count_of_pieces, int number_of_part) {
	int rows = container_4.getSize().x;
	int columns = container_4.getSize().y;

	int columns_of_block = rows / count_of_pieces; //кол-во колонок в блоке
	int help_value = start;
	int message_length = length_of_bit(message);

	message_length += (3 - message_length % 3) % 3;
	////////////////////////////////////////////////////запись длины сообщения////////////////////////////////////////////////////
	std::vector<int> length_message(9);
	length_message = binary_form_length_of_value(message_length);
	//1 (int)pixel (красный = 0 на конце всегда)
	sf::Color pix = container_4.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
	int help_color = change(pix.r, length_message[0]);
	pix.r = help_color;
	help_color = change((int)pix.g, length_message[1]);
	pix.g = help_color;
	help_color = change((int)pix.b, length_message[2]);
	pix.b = help_color;
	container_4.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

	//2 (int)pixel
	help_value++;
	pix = container_4.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
	help_color = change((int)pix.r, length_message[3]);
	pix.r = help_color;
	help_color = change((int)pix.g, length_message[4]);
	pix.g = help_color;
	help_color = change((int)pix.b, length_message[5]);
	pix.b = help_color;
	container_4.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

	//3 (int)pixel
	help_value++;
	pix = container_4.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
	help_color = change((int)pix.r, length_message[6]);
	pix.r = help_color;
	help_color = change((int)pix.g, length_message[7]);
	pix.g = help_color;
	help_color = change((int)pix.b, length_message[8]);
	pix.b = help_color;
	container_4.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

	////////////////////////////////////////////////////запись длины сообщения////////////////////////////////////////////////////
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
		pix = container_4.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
		help_color = change((int)pix.r, num_for_first[0]);
		pix.r = help_color;
		help_color = change((int)pix.g, num_for_first[1]);
		pix.g = help_color;
		help_color = change((int)pix.b, num_for_first[2]);
		pix.b = help_color;
		container_4.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);
		help_value++;
	}

	while (message_length > 0) {
		std::vector<int> num(3);
		num[0] = int(message / (ten_power / 10));
		num[1] = int((message / (ten_power / 100)) % 10);
		num[2] = int((message / (ten_power / 1000)) % 10);
		ten_power /= 1000;
		message = message % ten_power;
		sf::Color pix = container_4.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
		int help_color = change((int)pix.r, num[0]);
		pix.r = help_color;
		help_color = change((int)pix.g, num[1]);
		pix.g = help_color;
		help_color = change((int)pix.b, num[2]);
		pix.b = help_color;
		container_4.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);
		help_value++;
		message_length -= 3;
	}
	return help_value;
}
//Пиксели, в которые были встроены данные красит красным цветом
int coding_red_Shamir(ap_int<2048> message, int start, int count_of_pieces, int number_of_part) {
	int rows = container_red_4.getSize().x;
	int columns = container_red_4.getSize().y;

	int columns_of_block = rows / count_of_pieces; //кол-во колонок в блоке
	int help_value = start;
	int message_length = length_of_bit(message);

	message_length += (3 - message_length % 3) % 3;
	////////////////////////////////////////////////////запись длины сообщения////////////////////////////////////////////////////
	std::vector<int> length_message(9);
	length_message = binary_form_length_of_value(message_length);
	//1 (int)pixel (красный = 0 на конце всегда)
	sf::Color pix = container_red_4.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
	pix.r = 255;
	pix.g = 0;
	pix.b = 0;
	container_red_4.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

	//2 (int)pixel
	help_value++;
	pix = container_red_4.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
	pix.r = 255;
	pix.g = 0;
	pix.b = 0;
	container_red_4.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

	//3 (int)pixel
	help_value++;
	pix = container_red_4.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
	pix.r = 255;
	pix.g = 0;
	pix.b = 0;
	container_red_4.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

	////////////////////////////////////////////////////запись длины сообщения////////////////////////////////////////////////////
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
		pix = container_red_4.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
		pix.r = 255;
		pix.g = 0;
		pix.b = 0;
		container_red_4.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);
		help_value++;
	}

	while (message_length > 0) {
		std::vector<int> num(3);
		num[0] = int(message / (ten_power / 10));
		num[1] = int((message / (ten_power / 100)) % 10);
		num[2] = int((message / (ten_power / 1000)) % 10);
		ten_power /= 1000;
		message = message % ten_power;
		sf::Color pix = container_red_4.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
		pix.r = 255;
		pix.g = 0;
		pix.b = 0;
		container_red_4.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);
		help_value++;
		message_length -= 3;
	}
	return help_value;
}
//Пиксели, в которые была встроена сигнатура красит зеленым цветом
int coding_signature_Shamir(ap_int<2048> message, int start, int count_of_pieces, int number_of_part) {
	int rows = container_4.getSize().x;
	int columns = container_4.getSize().y;

	int columns_of_block = rows / count_of_pieces; //кол-во колонок в блоке

	////////////////////////////////////////////////////запись длины сообщения////////////////////////////////////////////////////
	int help_value = start;

	for (int i = 0; i < 3; i++) {
		sf::Color pix = container_4.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
		int help_color = change((int)pix.r, 1);
		pix.r = help_color;
		help_color = change((int)pix.g, 1);
		pix.g = help_color;
		help_color = change((int)pix.b, 1);
		pix.b = help_color;
		container_4.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

		pix = container_red_4.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
		pix.r = 0;
		pix.g = 255;
		pix.b = 0;
		container_red_4.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

		help_value++;

		pix = container_4.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
		help_color = change((int)pix.r, 1);
		pix.r = help_color;
		help_color = change((int)pix.g, 0);
		pix.g = help_color;
		help_color = change((int)pix.b, 1);
		pix.b = help_color;
		container_4.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

		pix = container_red_4.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
		pix.r = 0;
		pix.g = 255;
		pix.b = 0;
		container_red_4.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

		help_value++;


		pix = container_4.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
		help_color = change((int)pix.r, 0);
		pix.r = help_color;
		help_color = change((int)pix.g, 1);
		pix.g = help_color;
		help_color = change((int)pix.b, 0);
		pix.b = help_color;
		container_4.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

		pix = container_red_4.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
		pix.r = 0;
		pix.g = 255;
		pix.b = 0;
		container_red_4.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

		help_value++;
	}

	return help_value;
}

System::Void Project1::CodingShamir::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	OpenFileDialog^ open_dialog = gcnew OpenFileDialog; //создание диалогового окна для выбора файла
	open_dialog->Filter = "Image Files(*.BMP;*.JPG;*.GIF;*.PNG)|*.BMP;*.JPG;*.GIF;*.PNG|All files (*.*)|*.*";
	if (open_dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		pictureBox1->Image = gcnew Bitmap(open_dialog->FileName);
		container_4.loadFromFile(msclr::interop::marshal_as<std::string>(open_dialog->FileName));
		container_red_4.loadFromFile(msclr::interop::marshal_as<std::string>(open_dialog->FileName));

	}
	return System::Void();
}

System::Void Project1::CodingShamir::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
	srand(time(NULL));
	std::string m_text = msclr::interop::marshal_as<std::string>(textBox1->Text);
	ap_int<2048> m = convert_secret(m_text);
	ap_int<2048> codes_int = m;
	ap_int<2048> p;
	int n = Convert::ToInt32(numericUpDown1->Value);
	int k = Convert::ToInt32(numericUpDown2->Value);
	//std::string codes = std::string(codes_int);
	//textBox2->Text = gcnew String(codes.c_str());

	while (true) {//вычисляем P
		p = random(m + 1, m * 3);
		if ((ferma(p) == true) && (p > n)) {
			break;
		}
	}
	ap_int<2048>* a = new ap_int<2048>[k];
	for (int i = 1; i <= k - 1; i++) {
		a[i] = random(1, p);
	}

	std::map<ap_int<2048>, ap_int<2048>> doli;
	for (int i = 1; i <= n; i++) {//i выполняет роль икса
		ap_int<2048> value = m;
		for (int j = 1; j <= k - 1; j++) {
			value = value + a[j] * power(i, j, p);
		}
		value = value % p;
		doli.insert(std::pair<int, ap_int<2048>>(i, value));
	}
	int length_of_cod = 0;
	ap_int<2048> long_dolya_bits = -1;
	ap_int<2048> most_long_dolya_bits = -1;
	for (const auto& el : doli) {
		length_of_cod = length_of_bit(binary_form_of_value(el.first)) + length_of_bit(binary_form_of_value(el.second)) + length_of_cod;
		long_dolya_bits = length_of_bit(binary_form_of_value(el.first)) + length_of_bit(binary_form_of_value(el.second));
		if (most_long_dolya_bits < long_dolya_bits) {
			most_long_dolya_bits = long_dolya_bits;
		}
	}
	most_long_dolya_bits = most_long_dolya_bits + 8 + 8 + 9 * 3;
	ap_int<2048> most_long_dolya_pixels = most_long_dolya_bits / 3;
	if ((most_long_dolya_bits % 3) != 0) {
		most_long_dolya_pixels++;
	}



	if (length_of_cod > container_4.getSize().x * container_4.getSize().y) {
		textBox2->Text = "Не удалось закодировать доли!";
	}
	else {

		std::string message;
		int next_pixel = 0;
		int next_pixel_red = 0;

		//container_4.loadFromFile("pink.png");//загружаем в него файл
		ap_int<2048> crc = 0;
		int counter = 0;
		int koef_rand = 0;
		ap_int<2048> sinature = 111101010;
		//Console::WriteLine("CODE");

		for (const auto& el : doli) {
			koef_rand = (int)random(0, container_4.getSize().x / n * container_4.getSize().y - most_long_dolya_pixels - 1);

			next_pixel = coding_signature_Shamir(sinature, koef_rand, n, counter);
			next_pixel_red = coding_signature_Shamir(sinature, koef_rand, n, counter);
			//Console::WriteLine("Пиксель после сигнатуры: "); Console::WriteLine(next_pixel);


			crc = crc_code(el.first);
			ap_int<2048> message = binary_form_of_value(el.first) * 100000000 + crc;
			next_pixel = coding_Shamir(message, next_pixel, n, counter);
			next_pixel_red = coding_red_Shamir(message, next_pixel_red, n, counter);
			//Console::WriteLine((long long unsigned int)el.second);
			//Console::WriteLine("Пиксель после 1 числа : "); Console::WriteLine(next_pixel);

			crc = crc_code(el.second);
			message = binary_form_of_value(el.second) * 100000000 + crc;
			coding_Shamir(message, next_pixel, n, counter);
			coding_red_Shamir(message, next_pixel_red, n, counter);
			counter++;
			//Console::WriteLine("1 число: "); Console::WriteLine((int)el.first);
			//Console::WriteLine("2 число: "); Console::WriteLine((int)el.second);


		}
		container_4.saveToFile("picture_with_message.png");
		container_red_4.saveToFile("RED.png");
		std::string text_p = std::string(p);
		std::string text_p2 = std::to_string((k - 1));

		textBox2->Text = "Картинка успешно сохранена!";

		textBox3->Text = gcnew String(text_p.c_str());
		textBox4->Text = gcnew String(text_p2.c_str());
		button3->Enabled = true;
		delete[] a;
	}

	return System::Void();
}

System::Void Project1::CodingShamir::button3_Click(System::Object^ sender, System::EventArgs^ e)
{
	SaveFileDialog^ open_dialog = gcnew SaveFileDialog;
	open_dialog->Filter = "PNG Image|*.png";
	if (open_dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		container_4.saveToFile(msclr::interop::marshal_as<std::string>(open_dialog->FileName));
	}
	return System::Void();
}

