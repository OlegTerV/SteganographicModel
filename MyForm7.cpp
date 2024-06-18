#include "MyForm7.h"
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
sf::Image container7;

std::pair <int, ap_int<8192>> decoding_test_version_LSB(int start, int count_of_pieces, int number_of_part) {
	int columns = container7.getSize().y;
	int rows = container7.getSize().x;
	int columns_of_block = rows / count_of_pieces;
	ap_int<8192> code_message = 0;
	int length_of_message = 0;
	std::vector<int> length_message_binary_form(27);
	int index = 0;
	int i = start;
	int stop_flag = container7.getSize().x / count_of_pieces * container7.getSize().y - 1;
	//for (int i = start; i < start + 3; i++) {
	while ((i < start + 9) && (i < stop_flag)) {
		sf::Color pix = container7.getPixel(((i % columns_of_block) + columns_of_block * number_of_part), (i / columns_of_block));
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
	i = start + 9;
	while ((i < (start + count_of_pixels + 9)) && (i < stop_flag)) {
		sf::Color pix = container7.getPixel((i % columns_of_block) + columns_of_block * number_of_part, i / columns_of_block);
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

	return std::pair<int, ap_int<8192>>(start + count_of_pixels + 9, code_message);
}

System::Void Project1::MyForm7::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	OpenFileDialog^ open_dialog = gcnew OpenFileDialog; //создание диалогового окна для выбора файла
	open_dialog->Filter = "Image Files(*.BMP;*.JPG;*.GIF;*.PNG)|*.BMP;*.JPG;*.GIF;*.PNG|All files (*.*)|*.*";
	if (open_dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		pictureBox1->Image = gcnew Bitmap(open_dialog->FileName);
		container7.loadFromFile(msclr::interop::marshal_as<std::string>(open_dialog->FileName));

	}
	return System::Void();
}

System::Void Project1::MyForm7::button2_Click(System::Object^ sender, System::EventArgs^ e)
{

	ap_int<8192> secret_value = to_dec_LSB(decoding_test_version_LSB(0, 1, 0).second);
	std::string code_message= converter_secret_to_text_LSB(secret_value);

	textBox4->Text = gcnew String(code_message.c_str());

	return System::Void();
}

