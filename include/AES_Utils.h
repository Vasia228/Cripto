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

#endif // AES_UTILS_H_INCLUDED
