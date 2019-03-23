#include "DES_Utils.h"

const short int TRANSFORM_MATRIX[64]= {57, 49, 41, 33, 25, 17, 9, 1,
                                    59, 51, 43, 35, 27, 19, 11, 3,
                                    61, 53, 45, 37, 29, 21, 13, 5,
                                    63, 55, 47, 39, 31, 23, 15, 7,
                                    56, 48, 40, 32, 24, 16, 8, 0,
                                    58, 50, 42, 34, 26, 18, 10, 2,
                                    60, 52, 44, 36, 28, 20, 12, 4,
                                    62, 54, 46, 38, 30, 22, 14, 6};

const short int REVERSE_TRANSFORM_MATRIX[64]= {39, 7, 47, 15, 55, 23, 63, 31,
                                            38, 6, 46, 14, 54, 22, 62, 30,
                                            37, 5, 45, 13, 53, 21, 61, 29,
                                            36, 4, 44, 12, 52, 20, 60, 28,
                                            35, 3, 43, 11, 51, 19, 59, 27,
                                            34, 2, 42, 10, 50, 18, 58, 26,
                                            33, 1, 41, 9, 49, 17, 57, 25,
                                            32, 0, 40, 8, 48, 16, 56, 24};

const short int P[16]= {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

const short int START_KEY_MATRIX[56]= {56, 48, 40, 32, 24, 16, 8,
                                        0, 57, 49, 41, 33, 25, 17,
                                        9, 1, 58, 50, 42, 34, 26,
                                        18, 10, 2, 59, 51, 43, 35,
                                        62, 54, 46, 38, 30, 22, 14,
                                        6, 61, 53, 45, 37, 29, 21,
                                        13, 5, 60, 52, 44, 36, 28,
                                        20, 12, 4, 27, 19, 11, 3};

const short int END_KEY_MATRIX[48]= {13, 16, 10, 23, 0, 4,
                                        2, 27, 14, 5, 20, 9,
                                        22, 18, 11, 3, 25, 7,
                                        15, 6, 26, 19, 12, 1,
                                        40, 51, 30, 36, 46, 54,
                                        29, 39, 50, 44, 32, 47,
                                        43, 48, 38, 55, 33, 52,
                                        45, 41, 49, 35, 28, 31};

const short int END_CRYPT_REPLACEMENT_MATRIX[32]= {15, 6, 19, 20, 28, 11, 27, 16,
                                                    0, 14, 22, 25, 4, 17, 30, 9,
                                                    1, 7, 23, 13, 31, 26, 2, 8,
                                                    18, 12, 29, 5, 21, 10, 3, 24};

const short int REPLACEMENT_NODES_MATRIX[8][64]= {{14, 0, 4, 15, 13, 7, 1, 4, 2, 14, 15, 2, 11, 13, 8, 1, 3, 10, 10, 6, 6, 12, 12, 11, 5, 9, 9, 5, 0, 3, 7, 8, 4, 15, 1, 12, 14, 8, 8, 2, 13, 4, 6, 9, 2, 1, 11, 7, 15, 5, 12, 11, 9, 3, 7, 14, 3, 10, 10, 0, 5, 6, 0, 13},
                                                   {15, 3, 1, 13, 8, 4, 14, 7, 6, 15, 11, 2, 3, 8, 4, 14, 9, 12, 7, 0, 2, 1, 13, 10, 12, 6, 0, 9, 5, 11, 10, 5, 0, 13, 14, 8, 7, 10, 11, 1, 10, 3, 4, 15, 13, 4, 1, 2, 5, 11, 8, 6, 12, 7, 6, 12, 9, 0, 3, 5, 2, 14, 15, 9},
                                                   {10, 13, 0, 7, 9, 0, 14, 9, 6, 3, 3, 4, 15, 6, 5, 10, 1, 2, 13, 8, 12, 5, 7, 14, 11, 12, 4, 11, 2, 15, 8, 1, 13, 1, 6, 10, 4, 13, 9, 0, 8, 6, 15, 9, 3, 8, 0, 7, 11, 4, 1, 15, 2, 14, 12, 3, 5, 11, 10, 5, 14, 2, 7, 12},
                                                   {7, 13, 13, 8, 14, 11, 3, 5, 0, 6, 6, 15, 9, 0, 10, 3, 1, 4, 2, 7, 8, 2, 5, 12, 11, 1, 12, 10, 4, 14, 15, 9, 10, 3, 6, 15, 9, 0, 0, 6, 12, 10, 11, 1, 7, 13, 13, 8, 15, 9, 1, 4, 3, 5, 14, 11, 5, 12, 2, 7, 8, 2, 4, 14},
                                                   {2, 14, 12, 11, 4, 2, 1, 12, 7, 4, 10, 7, 11, 13, 6, 1, 8, 5, 5, 0, 3, 15, 15, 10, 13, 3, 0, 9, 14, 8, 9, 6, 4, 11, 2, 8, 1, 12, 11, 7, 10, 1, 13, 14, 7, 2, 8, 13, 15, 6, 9, 15, 12, 0, 5, 9, 6, 10, 3, 4, 0, 5, 14, 3},
                                                   {12, 10, 1, 15, 10, 4, 15, 2, 9, 7, 2, 12, 6, 9, 8, 5, 0, 6, 13, 1, 3, 13, 4, 14, 14, 0, 7, 11, 5, 3, 11, 8, 9, 4, 14, 3, 15, 2, 5, 12, 2, 9, 8, 5, 12, 15, 3, 10, 7, 11, 0, 14, 4, 1, 10, 7, 1, 6, 13, 0, 11, 8, 6, 13},
                                                   {4, 13, 11, 0, 2, 11, 14, 7, 15, 4, 0, 9, 8, 1, 13, 10, 3, 14, 12, 3, 9, 5, 7, 12, 5, 2, 10, 15, 6, 8, 1, 6, 1, 6, 4, 11, 11, 13, 13, 8, 12, 1, 3, 4, 7, 10, 14, 7, 10, 9, 15, 5, 6, 0, 8, 15, 0, 14, 5, 2, 9, 3, 2, 12},
                                                   {13, 1, 2, 15, 8, 13, 4, 8, 6, 10, 15, 3, 11, 7, 1, 4, 10, 12, 9, 5, 3, 5, 14, 11, 5, 0, 0, 14, 12, 9, 7, 2, 7, 2, 11, 1, 4, 14, 1, 7, 9, 4, 12, 10, 14, 8, 2, 13, 0, 15, 6, 12, 10, 9, 13, 0, 15, 3, 3, 5, 5, 6, 8, 11}};

bitstring& encrypt_DES(bitstring& str_bit)
{
    bitstring* key= new bitstring;
    generate_key_DES(*key);
    encrypt_DES(str_bit, *key);
    cout<<"OK"<<endl;
    return *key;
}

bitstring& encrypt_DES(bitstring& str_bit, bitstring& key)
{
    bitstring shedule[16];
    create_key_shedule_DES(key, shedule);

    long long size_of_remain_data= str_bit.get_size(), start_index= 0;
    bitstring block, encrypt_str_bit;

    while (size_of_remain_data>0)
    {
        erase_block_DES(block, str_bit, start_index, 64);
        encrypt_block_DES(block, shedule);

        size_of_remain_data-=64;
        start_index+=64;

        encrypt_str_bit+=block;
    }
    str_bit= encrypt_str_bit;
    cout<<str_bit.get_size()<<endl;
    return key;
}

void generate_key_DES(bitstring& key) ///////////////////////////////////////need rework/////////////////////////////////
{
    srand(time(NULL));
    int counter= 0;
    bool n;
    for (int i= 0; i<8; i++)
    {
        counter= 0;
        for (int j= 0; j<7; j++)
        {
            n= rand()%2;
            counter+= n;

            key.push(n);
        }
        (counter%2== 0) ? (key.push(0)) : (key.push(1));
    }
}

void create_key_shedule_DES(bitstring key, bitstring shedule[])
{
    apply_SKmatrix_DES(key);
    bitstring C= key.Hbit(28);
    bitstring D= key.Hbit(28);
    for (int i= 0; i<16; i++)
    {
        C.cycle_rotate_left(P[i]);
        D.cycle_rotate_left(P[i]);
        key= C+D;
        apply_EKmatrix_DES(key);
        shedule[i]=key;
    }
}

void erase_block_DES(bitstring& block, bitstring& str_bit, long long start_index, int size_of_slice)
{
    bitstring tmp(str_bit, start_index, size_of_slice);
    if (tmp.get_size()<size_of_slice)
    {
        for (int i= 0; i<size_of_slice-tmp.get_size(); i++)
        {
            tmp.push(0);
        }
    }
    block= tmp;
}

bool encrypt_block_DES(bitstring& block, bitstring shedule[])
{
    apply_Tmatrix_DES(block);
    bitstring L, L_, R, R_, buffer;
    L= block.Hbit(32);
    R= block.Lbit(32);

    for (int i= 0; i<16; i++)
    {
            L_= R;

            buffer= crypt_function_DES(R, shedule[i]);
            R_= L^buffer;

            R= R_;
            L= L_;
    }
    block= L_+R_;
    apply_RTmatrix_DES(block);
}

bitstring& crypt_function_DES(bitstring block, bitstring& key)
{
    expansion_DES(block);
    block= block^key;
    bitstring blocks[8];
    separate_to_part_DES(blocks, block, 8, 6);
    block.clear_data();
    int index;
    for (int i=0; i<8; i++)
    {
        index= trandform_to_int_DES(blocks[i]);
        block+= transform_to_bit_DES(REPLACEMENT_NODES_MATRIX[i][index]);
    }
    apply_ECRmatrix(block);
    bitstring* tmp= new bitstring(block);
    return *tmp;
}

void expansion_DES(bitstring& block)
{
    bitstring tmp(block);
    tmp.cycle_rotate_left(5);
    block= tmp.Lbit(6);
    for (int i= 0; i<7; i++)
    {
        tmp.cycle_rotate_left(4);
        block+= tmp.Lbit(6);
    }
}

void separate_to_part_DES(bitstring blocks[], bitstring& block, int amount_of_part, int size_of_part)
{
    bitstring* tmp;
    for (int i= 0; i<amount_of_part; i++)
    {
        tmp= new bitstring(block, i*size_of_part, size_of_part);
        blocks[i]=*tmp;
    }
}

int trandform_to_int_DES(bitstring& str_bit)
{
    int str_size= str_bit.get_size(), two= 1, num=0;
    for (int i= 0; i<str_size; i++)
    {
        num+= str_bit[(str_size-1)-i]*two;
        two= two*2;
    }
    return num;
}

bitstring& transform_to_bit_DES(int num)
{
    bitstring* tmp= new bitstring(num, 4);
    return *tmp;
}



bool decrypt(bitstring& str_bit, bitstring& key)
{
    bitstring shedule[16], tmp;
    create_key_shedule_DES(key, shedule);

    long long size_of_remain_data= str_bit.get_size(), start_index= 0;
    bitstring block, decrypt_str_bit;

    while (size_of_remain_data>0)
    {
        erase_block_DES(block, str_bit, start_index, 64);
        decrypt_block_DES(block, shedule);

        size_of_remain_data-=64;
        start_index+=64;

        decrypt_str_bit+=block;
    }
    str_bit= decrypt_str_bit;
}

bool decrypt_block_DES(bitstring& block, bitstring shedule[])
{
    apply_Tmatrix_DES(block);
    bitstring L, L_, R, R_, buffer;
    L= block.Hbit(32);
    R= block.Lbit(32);

    for (int i= 0; i<16; i++)
    {
            R_= L;

            buffer= crypt_function_DES(L, shedule[15-i]);
            L_= R^buffer;

            R= R_;
            L= L_;
    }
    block= L_+R_;
    apply_RTmatrix_DES(block);
}






















































void apply_ECRmatrix(bitstring& block)
{
    vector<bool> tmp;
    for (int i= 0; i<32; i++)
    {
        tmp.push_back(block[END_CRYPT_REPLACEMENT_MATRIX[i]]);
    }
    block= tmp;
}

void apply_Tmatrix_DES(bitstring& block)
{
    vector<bool> tmp;
    for (int i= 0; i<64; i++)
    {
        tmp.push_back(block[TRANSFORM_MATRIX[i]]);
    }
    block= tmp;
}

void apply_RTmatrix_DES(bitstring& block)
{
    bool buffer[64];
    for (int i= 0; i<64; i++) buffer[i]=block[i];
    bool value;
    for (int i= 0; i<64; i++)
    {
        value= buffer[REVERSE_TRANSFORM_MATRIX[i]];
        block(i, value);
    }
}

void apply_SKmatrix_DES(bitstring& key)
{
    vector<bool> tmp;
    for (int i= 0; i<56; i++)
    {
        tmp.push_back(key[START_KEY_MATRIX[i]]);
    }
    key= tmp;
}

void apply_EKmatrix_DES(bitstring& key)
{
    vector<bool> tmp;
    for (int i= 0; i<48; i++)
    {
        tmp.push_back(key[END_KEY_MATRIX[i]]);
    }
    key= tmp;
}
