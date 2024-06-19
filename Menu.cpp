#include <iostream>
#include "Menu.h"
#include "CodingAsmuthBloom.h"
#include "DecodingParts.h"
#include "RestoringSecretAsmuthBloom.h"
#include "CodingShamir.h"
#include "RestoringSecretShamir.h"
#include "CodingLSB.h"
#include "RestoringSecretLSB.h"
#include <msclr\marshal_cppstd.h>  
#include <string>  
using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args) {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	Project1::Menu form;
	Application::Run(% form);
}

System::Void Project1::Menu::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	std::string text = msclr::interop::marshal_as<std::string>(comboBox1->Text);
	if (text == "схема Асмута - Блума") {
		CodingAsmuthBloom^ form_1;
		form_1 = gcnew CodingAsmuthBloom();
		form_1->Show();
	}
	if (text == "схема Шамира") {
		CodingShamir^ form_4;
		form_4 = gcnew CodingShamir();
		form_4->Show();
	}
	if (text == "LSB - классика") {
		CodingLSB^ form_6;
		form_6 = gcnew CodingLSB();
		form_6->Show();
	}

	return System::Void();
}

System::Void Project1::Menu::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
	std::string text = msclr::interop::marshal_as<std::string>(comboBox1->Text);
	
		DecodingParts^ form_2;
		form_2 = gcnew DecodingParts();
		form_2->Show();
	

	return System::Void();
}

System::Void Project1::Menu::button3_Click(System::Object^ sender, System::EventArgs^ e)
{
	std::string text = msclr::interop::marshal_as<std::string>(comboBox1->Text);
	if (text == "схема Асмута - Блума") {
		RestoringSecretAsmuthBloom^ form_3;
		form_3 = gcnew RestoringSecretAsmuthBloom();
		form_3->Show();
	}
	if (text == "схема Шамира") {
		RestoringSecretShamir^ form_5;
		form_5 = gcnew RestoringSecretShamir();
		form_5->Show();
	}
	if (text == "LSB - классика") {
		RestoringSecretLSB^ form_7;
		form_7 = gcnew RestoringSecretLSB();
		form_7->Show();
	}
	return System::Void();
}

System::Void Project1::Menu::comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	std::string text = msclr::interop::marshal_as<std::string>(comboBox1->Text);
	if ((text == "схема Шамира") || (text == "схема Асмута - Блума")) {
		button2->Enabled = true;
	}
	else {
		button2->Enabled = false;
	}

	return System::Void();
}
