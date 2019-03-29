#include <iostream>
#include <string>
#include "bitstring.h"
#include "ByteMatrix.h"
#include <string.h>
//#include "DES_Utils.h"
//#include "Magma_Utils.h"
#include "AES_Utils.h"

using namespace std;

int main()
{
    string str("I am Grout and i am aliveI am Grout and i am aliveI am Grout and i a ");
    bitstring str_bit(str), key;
    /*cout<<str_bit.get_size()<<endl;
    key= encrypt_DES(str_bit);
    cout<<"OKkkkkkkkkkkkkkkkkkkkkkkk"<<endl;
    decrypt(str_bit, key);
    cout<<str_bit.to_string()<<endl;
    cout<<str_bit.get_size()<<endl;*/
    key = encrypt_AES(str_bit, key);

    /*ByteMatrix test(4,5);           Первый аргумент за номер строки, второй за номер столбца
    for (int i = 0; i < 4; i ++)
    {
        for (int j =0; j<5; j++)
        {
            bitstring tmp(j+1);
            test.set_byte(i, j, tmp);
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j =0; j<5; j++)
        {
            test.show_byte(i, j,false);
            cout<< " ";
        }
        cout<< endl;
    }
    cout<< endl;


    int a[4][5], index = 0;
    for (int i = 0; i < 4; i ++)
    {
        for (int j =0; j<5; j++)
        {
            a[i][j] = index;
            index++;
        }
    }
    for (int i = 0; i < 4; i ++)
    {
        for (int j =0; j<5; j++)
        {
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }*/

    return 0;
}
