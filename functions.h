#include "MyForm.h"
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

ap_int<2048> gcd(ap_int<2048> a, ap_int<2048> b);
ap_int<2048> mul(ap_int<2048> a, ap_int<2048> b, ap_int<2048> m);
ap_int<2048> pows(ap_int<2048> a, ap_int<2048> b, ap_int<2048> m);
bool ferma(ap_int<2048> x);
ap_int<2048> random(const ap_int<2048>& lower_bound, const ap_int<2048>& upper_bound);
std::vector<int> binary_form(int a);
int change(int color, int element);
ap_int<2048> power(int a, int s, ap_int<2048> p);
int length_of_value(ap_int<2048> a);
ap_int<2048> converter(std::string aa);
int length_of_bit(ap_int<2048> a);
ap_int<2048> binary_form_of_value(ap_int<2048> a);
std::vector<int> binary_form_length_of_value(int a);
std::string xor (std::string a, std::string b);
std::string to_bit_string(ap_int<2048> a);
ap_int<2048> crc_code(ap_int<2048> a1);
ap_int<2048> to_dec(ap_int<2048> a);
ap_int<2048> convert_secret(std::string a);
int two_to_ten(std::vector<int> a);
std::string converter_secret_to_text(ap_int<2048> secret);
ap_int<2048> get_reverse(ap_int<2048> a, ap_int<2048> p);
ap_int<2048> subtraction(ap_int<2048> a, ap_int<2048> b, ap_int<2048> p);


//LSB classic
ap_int<8192> binary_form_of_value_LSB(ap_int<8192> a);
std::vector<int> binary_form_length_of_value_LSB(int a);
int length_of_bit_LSB(ap_int<8192> a);
ap_int<8192> convert_secret_LSB(std::string a);
ap_int<8192> converter_LSB(std::string aa);
std::string converter_secret_to_text_LSB(ap_int<8192> secret);
ap_int<8192> to_dec_LSB(ap_int<8192> a);