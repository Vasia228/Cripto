#include "Magma_Utils.h"

const short int K_BLOCK_REPLACEMENT_MATRIX[8][16]= {{4, 10, 9, 2, 13, 8, 0, 14, 6, 11, 1, 12, 7, 15, 5, 3},
                                                    {14, 11, 4, 12, 6, 13, 15, 10, 2, 3, 8, 1, 0, 7, 5, 9},
                                                    {5, 8, 1, 13, 10, 3, 4, 2, 14, 15, 12, 7, 6, 0, 9, 11},
                                                    {7, 13, 10, 1, 0, 8, 9, 15, 14, 4, 6, 12, 11, 2, 5, 3},
                                                    {6, 12, 7, 1, 5, 15, 13, 8, 4, 10, 9, 14, 0, 3, 11, 2},
                                                    {4, 11, 10, 0, 7, 2, 1, 13, 3, 6, 8, 5, 9, 12, 15, 14},
                                                    {13, 11, 4, 1, 3, 15, 5, 9, 0, 10, 14, 7, 6, 8, 2, 12},
                                                    {1, 15, 13, 0, 5, 7, 10, 4, 9, 2, 3, 14, 6, 11, 8, 12}};












bitstring& encrypt_Magma(bitstring& str_bit, bitstring& key)
{
     generate_key_Magma(key);
     bitstring shedule[8];
     create_key_shedule_Magma(key, shedule);
     bitstring tmp(str_bit, 0, 64);
     tmp.show(32);
     encrypt_block_Magma(tmp, shedule);
     tmp.show(32);
     decrypt_block_Magma(tmp, shedule);
     tmp.show(32);

     return key;
}


void generate_key_Magma(bitstring& key) ///////////////////////////////////////need rework/////////////////////////////////
{
    srand(time(NULL));
    bool n;
    for (int i= 0; i<256; i++)
    {
        n = rand()%2;
        key.push(n);
    }
}


void create_key_shedule_Magma(bitstring key, bitstring shedule[])
{
    for (int i = 0; i<8; i++)
    {
        bitstring tmp(key, 32*i, 32);
        shedule[i] = tmp;
    }
}


bool encrypt_block_Magma(bitstring& block, bitstring shedule[])
{
    bitstring B(block, 0, 32), A(block, 32, 32), crypt_result, buffer;
    for (int i = 0; i<24; i++)
    {
        buffer = A;
        crypt_result = crypt_function_Magma(A, shedule[i%8]);
        //crypt_result.show();
        A = B^crypt_result;
        B = buffer;
    }
    for (int i = 7; i > 0; i--)
    {
        buffer = A;
        crypt_result = crypt_function_Magma(A, shedule[i]);
        A = B^crypt_result;
        B = buffer;
    }
    buffer = B;
    crypt_result = crypt_function_Magma(A, shedule[0]);
    B = buffer^crypt_result;

    block = B + A;
}


bitstring& crypt_function_Magma(bitstring block, bitstring& key)
{
    bitstring temp = xor_32_Magma(block, key);
    apply_K_BLOCK_REPLACEMENT(temp);
    temp.cycle_rotate_left(11);
    bitstring* tmp = new bitstring(temp);
    return *tmp;
}


bitstring& xor_32_Magma(bitstring block, bitstring key)
{
    bitstring temp = block.plus(key);
    if (temp.get_size() >= 33)
    {
        block.generate_2_pow(32);
        block = temp.minus(block);
        temp = block.Lbit(32);
    }
    bitstring* tmp = new bitstring(temp);
    return *tmp;
}

void apply_K_BLOCK_REPLACEMENT(bitstring& block)
{
    bitstring block_part[8];
    for (int i = 0; i<8; i++)
    {
        bitstring temp(block, i*4, 4);
        block_part[i] = temp;
    }
    block.clear_data();
    int index = 0;
    for (int i = 0; i<8; i++)
    {
        index = block_part[i].return_int();
        bitstring temp(K_BLOCK_REPLACEMENT_MATRIX[i][index], 4);
        block += temp;
    }
}


bool decrypt_block_Magma(bitstring& block, bitstring shedule[])
{
    bitstring B(block, 0, 32), A(block, 32, 32), crypt_result, buffer;

    for (int i = 0; i < 8; i++)
    {
        buffer = A;
        crypt_result = crypt_function_Magma(A, shedule[i]);
        A = B^crypt_result;
        B = buffer;
    }
    for (int i = 23; i>= 0; i--)
    {
        buffer = A;
        crypt_result = crypt_function_Magma(A, shedule[i%8]);
        A = B^crypt_result;
        B = buffer;
    }
    block = A + B;
}





















