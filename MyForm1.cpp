#include <iostream>
#include "MyForm1.h"
#include "MyForm.h"
#include "MyForm2.h"
#include "MyForm3.h"
#include "MyForm4.h"
#include "MyForm5.h"
#include "MyForm6.h"
#include "MyForm7.h"
#include <msclr\marshal_cppstd.h>  
#include <string>  
using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args) {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	Project1::MyForm1 form;
	Application::Run(% form);
}

System::Void Project1::MyForm1::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	std::string text = msclr::interop::marshal_as<std::string>(comboBox1->Text);
	if (text == "схема Асмута - Блума") {
		MyForm^ form_1;
		form_1 = gcnew MyForm();
		form_1->Show();
	}
	if (text == "схема Шамира") {
		MyForm4^ form_4;
		form_4 = gcnew MyForm4();
		form_4->Show();
	}
	if (text == "LSB - классика") {
		MyForm6^ form_6;
		form_6 = gcnew MyForm6();
		form_6->Show();
	}

	return System::Void();
}

System::Void Project1::MyForm1::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
	std::string text = msclr::interop::marshal_as<std::string>(comboBox1->Text);
	
		MyForm2^ form_2;
		form_2 = gcnew MyForm2();
		form_2->Show();
	

	return System::Void();
}

System::Void Project1::MyForm1::button3_Click(System::Object^ sender, System::EventArgs^ e)
{
	std::string text = msclr::interop::marshal_as<std::string>(comboBox1->Text);
	if (text == "схема Асмута - Блума") {
		MyForm3^ form_3;
		form_3 = gcnew MyForm3();
		form_3->Show();
	}
	if (text == "схема Шамира") {
		MyForm5^ form_5;
		form_5 = gcnew MyForm5();
		form_5->Show();
	}
	if (text == "LSB - классика") {
		MyForm7^ form_7;
		form_7 = gcnew MyForm7();
		form_7->Show();
	}
	return System::Void();
}

System::Void Project1::MyForm1::comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
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
