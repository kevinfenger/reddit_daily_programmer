#include <stdlib.h>
#include <stdio.h>
#include <iostream> 
#include <sstream> 
#include <algorithm> 

using namespace std;

class ISBN { 
    public :
       static const int length = 10; 
       bool verify(string); 
       std::string generate(); 
       std::string cleanse(string); 
       ISBN(); 
       ~ISBN(); 
};

ISBN::ISBN() 
{ 
}
ISBN::~ISBN() 
{ 
}

string 
ISBN::generate() {
    stringstream ss; 
    int total = 0;
    int multiplier = 10;  
    for (int i = 0; i < this->length+2 ; i++) 
    { 
        if (i == 1 || i == 6 || i == 11) 
           ss << '-';
        else { 
           int random = rand() % 10;
           total += random * multiplier--;
           ss << random;  
        }
    }
    int last_digit = 0; 
    while (last_digit <= 10) {  
        if (last_digit == 10) {  
            ss << 'X'; 
        }
        else { 
            if ((total + last_digit) % 11 == 0) { 
                ss << last_digit; 
                break; 
            }
        }
        last_digit++; 
    }
    return ss.str(); 
}

string 
ISBN::cleanse(string str) { 
    string output; 
    for (size_t i = 0; i < str.size(); i++) 
        if (str[i] != '-') 
            output += str[i];
    return output;  
}

bool 
ISBN::verify(string isbn_code) {
    isbn_code = cleanse(isbn_code);
    int current_multiplier = 10,  
        total = 0, tmp=0; 
    if (isbn_code.length() == 10) { 
        for (size_t i = 0; i < isbn_code.length() ; i++) {
            if (isbn_code[i] == 'X') 
                tmp = 10;
            else 
                tmp = isbn_code[i] - '0';
            total += current_multiplier * tmp;    
            current_multiplier--; 
        }
        if (total % 11 == 0) 
            return true; 
    } 
    return false; 
}

int main() { 
   srand(time(0));
   ISBN isbn; 
   cout << endl; 
   string generated = isbn.generate();
   cout << "generated : " << generated << endl;  
   isbn.verify(generated) ? cout << "yes" : cout << "no"; 
   cout << endl;  
} 
