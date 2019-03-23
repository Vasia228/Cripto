#ifndef DES_UTILS_H_INCLUDED
#define DES_UTILS_H_INCLUDED

#include <iostream>
#include <bitstring.h>

#include <stdlib.h>
#include <ctime>

bitstring& encrypt_DES(bitstring& str_bit);
bitstring& encrypt_DES(bitstring& str_bit, bitstring& key);
void generate_key_DES(bitstring& key);
void create_key_shedule_DES(bitstring key, bitstring shedule[]);
void erase_block_DES(bitstring& block, bitstring& str_bit,long long start_index, int  size_of_slice);
void swap_block_DES(bitstring& str_bit, bitstring& block, long long start_index);
bool encrypt_block_DES(bitstring& block, bitstring shedule[]);
bitstring& crypt_function_DES(bitstring block, bitstring& key);
void expansion_DES(bitstring& block);
void separate_to_part_DES(bitstring blocks[], bitstring& block, int amount_of_part, int size_of_part);
int trandform_to_int_DES(bitstring& str_bit);
bitstring& transform_to_bit_DES(int num);

bool decrypt(bitstring& str_bit, bitstring& key);
bool decrypt_block_DES(bitstring& block, bitstring shedule[]);

void apply_ECRmatrix(bitstring& block);
void apply_Tmatrix_DES(bitstring& block);
void apply_RTmatrix_DES(bitstring& block);
void apply_SKmatrix_DES(bitstring& key);
void apply_EKmatrix_DES(bitstring& key);

#endif // DES_UTILS_H_INCLUDED
