#ifndef AES_UTILS_H_INCLUDED
#define AES_UTILS_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <ctime>

#include "bitstring.h"
#include "ByteMatrix.h"

bitstring& encrypt_AES(bitstring& str_bit, bitstring& key);
void generate_key_AES(bitstring& key);
void create_key_shedule_AES(bitstring key, ByteMatrix* shedule);
void apply_Rcon(bitstring* collumn, int index);
bool encrypt_block_AES(bitstring& block, ByteMatrix* shedule);
bool add_round_key(ByteMatrix* state, ByteMatrix* key);
void sub_byte(ByteMatrix* state);
void shift_rows(ByteMatrix* state);
void mix_colums(ByteMatrix* state);
bool decrypt_block_AES(bitstring& block, ByteMatrix* shedule);
void inv_sub_byte(ByteMatrix* state);
void inv_shift_rows(ByteMatrix* state);

#endif // AES_UTILS_H_INCLUDED
