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
    return 0;
}
