#ifndef MAGMA_UTILS_H_INCLUDED
#define MAGMA_UTILS_H_INCLUDED

#include <iostream>
#include <bitstring.h>

#include <stdlib.h>
#include <ctime>

bitstring& encrypt_Magma(bitstring& str_bit, bitstring& key);
void generate_key_Magma(bitstring& key);
void create_key_shedule_Magma(bitstring key, bitstring shedule[]);
bool encrypt_block_Magma(bitstring& block, bitstring shedule[]);
bitstring& crypt_function_Magma(bitstring block, bitstring& key);
bitstring& xor_32_Magma(bitstring block, bitstring key);
void apply_K_BLOCK_REPLACEMENT(bitstring& block);
bool decrypt_block_Magma(bitstring& block, bitstring shedule[]);

#endif // MAGMA_UTILS_H_INCLUDED
