#include "MyForm6.h"
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

sf::Image container_red_6;
sf::Image container6;

//Встраивает данные в пиксели. 
int coding_of_parts_LSB(ap_int<8192> message, int start, int count_of_pieces, int number_of_part) {
	int rows = container6.getSize().x;
	int columns = container6.getSize().y;

	int columns_of_block = rows / count_of_pieces; //кол-во колонок в блоке
	int help_value = start;
	int message_length = length_of_bit_LSB(message);

	message_length += (3 - message_length % 3) % 3;
	////////////////////////////////////////////////////запись длины сообщения////////////////////////////////////////////////////
	std::vector<int> length_message(27);
	length_message = binary_form_length_of_value_LSB(message_length);
	//1 (int)pixel (красный = 0 на конце всегда)
	sf::Color pix = container6.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
	int help_color = change(pix.r, length_message[0]);
	pix.r = help_color;
	help_color = change((int)pix.g, length_message[1]);
	pix.g = help_color;
	help_color = change((int)pix.b, length_message[2]);
	pix.b = help_color;
	container6.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

	//2 (int)pixel
	help_value++;
	pix = container6.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
	help_color = change((int)pix.r, length_message[3]);
	pix.r = help_color;
	help_color = change((int)pix.g, length_message[4]);
	pix.g = help_color;
	help_color = change((int)pix.b, length_message[5]);
	pix.b = help_color;
	container6.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

	//3 (int)pixel
	help_value++;
	pix = container6.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
	help_color = change((int)pix.r, length_message[6]);
	pix.r = help_color;
	help_color = change((int)pix.g, length_message[7]);
	pix.g = help_color;
	help_color = change((int)pix.b, length_message[8]);
	pix.b = help_color;
	container6.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

	//4 (int)pixel
	help_value++;
	pix = container6.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
	help_color = change((int)pix.r, length_message[9]);
	pix.r = help_color;
	help_color = change((int)pix.g, length_message[10]);
	pix.g = help_color;
	help_color = change((int)pix.b, length_message[11]);
	pix.b = help_color;
	container6.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

	//5 (int)pixel
	help_value++;
	pix = container6.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
	help_color = change((int)pix.r, length_message[12]);
	pix.r = help_color;
	help_color = change((int)pix.g, length_message[13]);
	pix.g = help_color;
	help_color = change((int)pix.b, length_message[14]);
	pix.b = help_color;
	container6.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

	//6 (int)pixel
	help_value++;
	pix = container6.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
	help_color = change((int)pix.r, length_message[15]);
	pix.r = help_color;
	help_color = change((int)pix.g, length_message[16]);
	pix.g = help_color;
	help_color = change((int)pix.b, length_message[17]);
	pix.b = help_color;
	container6.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

	//7 (int)pixel
	help_value++;
	pix = container6.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
	help_color = change((int)pix.r, length_message[18]);
	pix.r = help_color;
	help_color = change((int)pix.g, length_message[19]);
	pix.g = help_color;
	help_color = change((int)pix.b, length_message[20]);
	pix.b = help_color;
	container6.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

	//8 (int)pixel
	help_value++;
	pix = container6.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
	help_color = change((int)pix.r, length_message[21]);
	pix.r = help_color;
	help_color = change((int)pix.g, length_message[22]);
	pix.g = help_color;
	help_color = change((int)pix.b, length_message[23]);
	pix.b = help_color;
	container6.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

	//9 (int)pixel
	help_value++;
	pix = container6.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
	help_color = change((int)pix.r, length_message[24]);
	pix.r = help_color;
	help_color = change((int)pix.g, length_message[25]);
	pix.g = help_color;
	help_color = change((int)pix.b, length_message[26]);
	pix.b = help_color;
	container6.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);
	////////////////////////////////////////////////////запись длины сообщения////////////////////////////////////////////////////
	help_value = start + 9;

	ap_int<8192> ten_power = 1;
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
		pix = container6.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
		help_color = change((int)pix.r, num_for_first[0]);
		pix.r = help_color;
		help_color = change((int)pix.g, num_for_first[1]);
		pix.g = help_color;
		help_color = change((int)pix.b, num_for_first[2]);
		pix.b = help_color;
		container6.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);
		help_value++;
	}

	while (message_length > 0) {
		std::vector<int> num(3);
		num[0] = int(message / (ten_power / 10));
		num[1] = int((message / (ten_power / 100)) % 10);
		num[2] = int((message / (ten_power / 1000)) % 10);
		ten_power /= 1000;
		message = message % ten_power;
		sf::Color pix = container6.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
		int help_color = change((int)pix.r, num[0]);
		pix.r = help_color;
		help_color = change((int)pix.g, num[1]);
		pix.g = help_color;
		help_color = change((int)pix.b, num[2]);
		pix.b = help_color;
		container6.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);
		help_value++;
		message_length -= 3;
	}
	return help_value;
}
//Пиксели, в которые были встроены данные красит красным цветом
int coding_of_parts_red_LSB(ap_int<8192> message, int start, int count_of_pieces, int number_of_part) {
	int rows = container_red_6.getSize().x;
	int columns = container_red_6.getSize().y;

	int columns_of_block = rows / count_of_pieces; //кол-во колонок в блоке
	int help_value = start;
	int message_length = length_of_bit_LSB(message);

	message_length += (3 - message_length % 3) % 3;
	////////////////////////////////////////////////////запись длины сообщения////////////////////////////////////////////////////
	std::vector<int> length_message(9);
	length_message = binary_form_length_of_value_LSB(message_length);
	//1 (int)pixel (красный = 0 на конце всегда)
	sf::Color pix = container_red_6.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
	pix.r = 255;
	pix.g = 0;
	pix.b = 0;
	container_red_6.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

	//2 (int)pixel
	help_value++;
	pix = container_red_6.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
	pix.r = 255;
	pix.g = 0;
	pix.b = 0;
	container_red_6.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

	//3 (int)pixel
	help_value++;
	pix = container_red_6.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
	pix.r = 255;
	pix.g = 0;
	pix.b = 0;
	container_red_6.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);

	////////////////////////////////////////////////////запись длины сообщения////////////////////////////////////////////////////
	help_value = start + 3;

	ap_int<8192> ten_power = 1;
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
		pix = container_red_6.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
		pix.r = 255;
		pix.g = 0;
		pix.b = 0;
		container_red_6.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);
		help_value++;
	}

	while (message_length > 0) {
		std::vector<int> num(3);
		num[0] = int(message / (ten_power / 10));
		num[1] = int((message / (ten_power / 100)) % 10);
		num[2] = int((message / (ten_power / 1000)) % 10);
		ten_power /= 1000;
		message = message % ten_power;
		sf::Color pix = container_red_6.getPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block));
		pix.r = 255;
		pix.g = 0;
		pix.b = 0;
		container_red_6.setPixel((help_value % columns_of_block + columns_of_block * number_of_part), (help_value / columns_of_block), pix);
		help_value++;
		message_length -= 3;
	}
	return help_value;
}

System::Void Project1::MyForm6::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	OpenFileDialog^ open_dialog = gcnew OpenFileDialog; //создание диалогового окна для выбора файла
	open_dialog->Filter = "Image Files(*.BMP;*.JPG;*.GIF;*.PNG)|*.BMP;*.JPG;*.GIF;*.PNG|All files (*.*)|*.*";
	if (open_dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		pictureBox1->Refresh();
		pictureBox1->Image = gcnew Bitmap(open_dialog->FileName);
		container6.loadFromFile(msclr::interop::marshal_as<std::string>(open_dialog->FileName));
		container_red_6.loadFromFile(msclr::interop::marshal_as<std::string>(open_dialog->FileName));

	}

	return System::Void();
}

System::Void Project1::MyForm6::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
	std::string m_text = msclr::interop::marshal_as<std::string>(textBox1->Text);

	ap_int<8192> message = binary_form_of_value_LSB(convert_secret_LSB(m_text));

	int length_of_cod = length_of_bit_LSB(message);
	if (length_of_cod > container6.getSize().x * container6.getSize().y) {
		textBox2->Text = "Не удалось закодировать доли!";
		button3->Enabled = false;
	}
	else {
		coding_of_parts_LSB(message, 0, 1, 0);
		container6.saveToFile("picture_with_message.png");

		coding_of_parts_red_LSB(message, 0, 1, 0);
		container_red_6.saveToFile("RED_LSB.png");


		textBox2->Text = "Картинка успешно сохранена!";
		button3->Enabled = true;
	}

	return System::Void();
}

System::Void Project1::MyForm6::button3_Click(System::Object^ sender, System::EventArgs^ e)
{
	SaveFileDialog^ open_dialog = gcnew SaveFileDialog;
	open_dialog->Filter = "PNG Image|*.png";
	if (open_dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		container6.saveToFile(msclr::interop::marshal_as<std::string>(open_dialog->FileName));
	}
	return System::Void();
}