#ifndef BITSTRING_H
#define BITSTRING_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <string.h>

using namespace std;

class bitstring
{
    public:
        //constructor
        bitstring();
        bitstring(int num);
        bitstring(int num, int element_size);
        bitstring(string& str);
        bitstring(bitstring& str_bit);
        bitstring(bitstring& str_bit, int size_of_slice); //if size_of_slice<0 return slice from the end
        bitstring(bitstring& str_bit, int start_index, int size_of_slice);

        //destructor
        virtual ~bitstring();

        //overloaded operator
        bitstring& operator=(bitstring& str_bit);
        void operator=(vector<bool>& tmp);
        bool operator[](int index);
        void operator()(int index, bool value);
        bitstring& operator+(bitstring& str_bit);
        void operator+=(bitstring& str_bit);
        bitstring& operator^(bitstring& str_bit);

        //methods
        void tolow(string& str);
        string to_string();
        void push(bool n);
        void clear_data();
        bitstring& Hbit(int size_of_slice);
        bitstring& Lbit(int size_of_slice);
        void cycle_rotate_left(int n);
        void cycle_rotate_left();
        void show(int size_of_slice= 5);
        void show_size();

        //getter
        int get_size(){return data.size();};

    private:
        vector<bool> data;
};

#endif // BITSTRING_H
