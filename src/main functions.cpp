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

//начало блока кода проверки на простоту
ap_int<2048> gcd(ap_int<2048> a, ap_int<2048> b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
ap_int<2048> mul(ap_int<2048> a, ap_int<2048> b, ap_int<2048> m) {
    if (b == 1)
        return a;
    if (b % 2 == 0) {
        ap_int<2048> t = mul(a, b / 2, m);
        return (2 * t) % m;
    }
    return (mul(a, b - 1, m) + a) % m;
}
ap_int<2048> pows(ap_int<2048> a, ap_int<2048> b, ap_int<2048> m) {
    if (b == 0)
        return 1;
    if (b % 2 == 0) {
        ap_int<2048> t = pows(a, b / 2, m);
        return mul(t, t, m) % m;
    }
    return (mul(pows(a, b - 1, m), a, m)) % m;
}
bool ferma(ap_int<2048> x) {
    if (x == 2)
        return true;
    for (int i = 0; i < 100; i++) {
        ap_int<2048> a = (rand() % (x - 2)) + 2;
        if (gcd(a, x) != 1)
            return false;
        if (pows(a, x - 1, x) != 1)
            return false;
    }
    return true;
}
//конец блока кода проверки на простоту


//вспомогательные функции
ap_int<2048> random(const ap_int<2048>& lower_bound, const ap_int<2048>& upper_bound)
{
    ap_int<2048> output = lower_bound + (rand() % (upper_bound - lower_bound + 1));
    return output;
}
std::vector<int> binary_form(int a) {
    int res = 0;
    int i = 7;
    std::vector<int> vec(8);
    while (a != 0) {
        vec[i] = (a % 2);
        i--;
        a = a / 2;
    }
    return vec;
}
int change(int color, int element) {
    if (((color % 2) == 1) && (element == 0)) {
        color--;
    }
    else if (((color % 2) == 0) && (element == 1)) {
        color++;
    }
    return color;
}
ap_int<2048> power(int a, int s, ap_int<2048> p) {
    ap_int<2048> znach = a;
    for (int i = 1; i < s; i++) {
        znach = znach * a;
    }
    return znach;
}
int length_of_value(ap_int<2048> a) {
    int result = 0;
    if (a == 0) { return 1; }
    while (a != 0) {
        a = a / 10;
        result++;
    }
    return result;
}
ap_int<2048> converter(std::string aa) {
    ap_int<2048> result = 0;
    ap_int<2048> ten = 1;
    while (aa.length() != 0) {
        char symbol = aa.back();
        result = result + int(symbol - '0') * ten;
        ten = ten * 10;
        aa.pop_back();
    }
    return result;
}
int length_of_bit(ap_int<2048> a) {
    int result = 0;
    while (a != 0) {
        a = a / 10;
        result++;
    }
    return result;
}
ap_int<2048> binary_form_of_value(ap_int<2048> a) {
    ap_int<2048> result = 0;
    ap_int<2048> ten = 1;
    while (a != 0) {
        result = result + (a % 2) * ten;
        a /= 2;
        ten *= 10;
    }
    return result;
}//new
std::vector<int> binary_form_length_of_value(int a) {//new//new//new
    int res = 0;
    int i = 8;
    std::vector<int> vec(9);
    while (a != 0) {
        vec[i] = (a % 2);
        i--;
        a = a / 2;
    }
    return vec;
}
std::string xor (std::string a, std::string b) {
    std::string result;
    for (int i = 0; i < a.length(); i++) {
        if (a[i] == b[i]) {
            result.push_back('0');
        }
        else {
            result.push_back('1');
        }
    }
    int res = std::stoi(result);
    result = std::to_string(res);
    return result;
}
std::string to_bit_string(ap_int<2048> a) {
    std::string result;
    char bit;
    while (a != 0) {
        if (a % 2 == 1) {
            result.push_back('1');
        }
        else {
            result.push_back('0');
        }
        a = a / 2;
    }
    reverse(result.begin(), result.end());
    return result;
}
ap_int<2048> crc_code(ap_int<2048> a1) {
    std::string b = "100110001";
    std::string c;
    std::string a = to_bit_string(a1);
    a = a + "00000000";
    while (a.length() >= b.length()) {
        c = a.substr(0, 5);
        a = a.erase(0, 5);
        c = xor (c, b);
        a = c + a;
    }
    ap_int<2048> result = converter(a);
    return result;
}
ap_int<2048> to_dec(ap_int<2048> a) {
    ap_int<2048> result = 0;
    ap_int<2048> two = 1;
    while (a != 0) {
        result = result + (a % 10) * two;
        two = two * 2;
        a = a / 10;
    }
    return result;
}
ap_int<2048> convert_secret(std::string a) {
    ap_int<2048> result = 0;
    for (int i = 0; i < a.length(); i++) {
        result = result * 1000 + (int)a[i];
    }
    return result;
}
int two_to_ten(std::vector<int> a) {
    int value = 0;
    int two = 1;
    for (int i = 0; i < a.size(); i++) {
        value = value + a[a.size() - i - 1] * two;
        two = two * 2;
    }
    return value;
}
std::string converter_secret_to_text(ap_int<2048> secret) {
    std::string result;
    while (secret >= 1000) {
        result = result + (char)(secret % 1000);
        secret = secret / 1000;
    }
    result = result + (char)secret;
    reverse(result.begin(), result.end());
    return result;
}
ap_int<2048> get_reverse(ap_int<2048> a, ap_int<2048> p) {
    ap_int<2048> reverse = 0;
    ap_int<2048> a0, a1, x0, y0, x1, y1, ai, xi, yi, b0, b1, zero;
    zero = 0;
    b0 = a;
    b1 = p;
    a0 = a;
    a1 = p;
    ai = 1;
    x0 = 1;
    y0 = 0;
    x1 = 0;
    y1 = 1;
    xi = 0;
    yi = 0;
    while (ai != 0) {
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
    reverse = x0;
    return reverse;
}
ap_int<2048> subtraction(ap_int<2048> a, ap_int<2048> b, ap_int<2048> p) {
    //a-b
    ap_int<2048> c = a - b;
    ap_int<2048> zero = 0;
    while (c < zero) {
        c = c + p;
    }
    return c;
}


//LSB classic 
ap_int<8192> binary_form_of_value_LSB(ap_int<8192> a) {
    ap_int<8192> result = 0;
    ap_int<8192> ten = 1;
    while (a != 0) {
        result = result + (a % 2) * ten;
        a /= 2;
        ten *= 10;
    }
    return result;
}//new
std::vector<int> binary_form_length_of_value_LSB(int a) {//new//new//new
    int res = 0;
    int i = 26;
    std::vector<int> vec(27);
    while (a != 0) {
        vec[i] = (a % 2);
        i--;
        a = a / 2;
    }
    return vec;
}
int length_of_bit_LSB(ap_int<8192> a) {
    int result = 0;
    while (a != 0) {
        a = a / 10;
        result++;
    }
    return result;
}
ap_int<8192> convert_secret_LSB(std::string a) {
    ap_int<8192> result = 0;
    for (int i = 0; i < a.length(); i++) {
        result = result * 1000 + (int)a[i];
    }
    return result;
}
ap_int<8192> converter_LSB(std::string aa) {
    ap_int<8192> result = 0;
    ap_int<8192> ten = 1;
    while (aa.length() != 0) {
        char symbol = aa.back();
        result = result + int(symbol - '0') * ten;
        ten = ten * 10;
        aa.pop_back();
    }
    return result;
}
std::string converter_secret_to_text_LSB(ap_int<8192> secret) {
    std::string result;
    while (secret >= 1000) {
        result = result + (char)(secret % 1000);
        secret = secret / 1000;
    }
    result = result + (char)secret;
    reverse(result.begin(), result.end());
    return result;
}
ap_int<8192> to_dec_LSB(ap_int<8192> a) {
    ap_int<8192> result = 0;
    ap_int<8192> two = 1;
    while (a != 0) {
        result = result + (a % 10) * two;
        two = two * 2;
        a = a / 10;
    }
    return result;
}
