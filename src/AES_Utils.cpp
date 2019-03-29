#include "AES_Utils.h"
using namespace std;

const short int S_BOX_MATRIX[16][16][2] = {
{{6, 3}, {7, 12}, {7, 7}, {7, 11}, {15, 2}, {6, 11}, {6, 15}, {12, 5}, {3, 0}, {0, 1}, {6, 7}, {2, 11}, {15, 14}, {13, 7}, {10, 11}, {7, 6}},
{{12, 10}, {8, 2}, {12, 9}, {7, 13}, {15, 10}, {5, 9}, {4, 7}, {15, 0}, {10, 13}, {13, 4}, {10, 2}, {10, 15}, {9, 12}, {10, 4}, {7, 2}, {12, 0}},
{{11, 7}, {15, 13}, {9, 3}, {2, 6}, {3, 6}, {3, 15}, {15, 7}, {12, 12}, {3, 4}, {10, 5}, {14, 5}, {15, 1}, {7, 1}, {13, 8}, {3, 1}, {1, 5}},
{{0, 4}, {12, 7}, {2, 3}, {12, 3}, {1, 8}, {9, 6}, {0, 5}, {9, 10}, {0, 7}, {1, 2}, {8, 0}, {14, 2}, {14, 11}, {2, 7}, {11, 2}, {7, 5}},
{{0, 9}, {8, 3}, {2, 12}, {1, 10}, {1, 11}, {6, 14}, {5, 10}, {10, 0}, {5, 2}, {3, 11}, {13, 6}, {11, 3}, {2, 9}, {14, 3}, {2, 15}, {8, 4}},
{{5, 3}, {13, 1}, {0, 0}, {14, 13}, {2, 0}, {15, 12}, {11, 1}, {5, 11}, {6, 10}, {12, 11}, {11, 14}, {3, 9}, {4, 10}, {4, 12}, {5, 8}, {12, 15}},
{{13, 0}, {14, 15}, {10, 10}, {15, 11}, {4, 3}, {4, 13}, {3, 3}, {8, 5}, {4, 5}, {15, 9}, {0, 2}, {7, 15}, {5, 0}, {3, 12}, {9, 15}, {10, 8}},
{{5, 1}, {10, 3}, {4, 0}, {8, 15}, {9, 2}, {9, 13}, {3, 8}, {15, 5}, {11, 12}, {11, 6}, {13, 10}, {2, 1}, {1, 0}, {15, 15}, {15, 3}, {13, 2}},
{{12, 13}, {0, 12}, {1, 3}, {14, 12}, {5, 15}, {9, 7}, {4, 4}, {1, 7}, {12, 4}, {10, 7}, {7, 14}, {3, 13}, {6, 4}, {5, 13}, {1, 9}, {7, 3}},
{{6, 0}, {8, 1}, {4, 15}, {13, 12}, {2, 2}, {2, 10}, {9, 0}, {8, 8}, {4, 6}, {14, 14}, {11, 8}, {1, 4}, {13, 14}, {5, 14}, {0, 11}, {13, 11}},
{{14, 0}, {3, 2}, {3, 10}, {0, 10}, {4, 9}, {0, 6}, {2, 4}, {5, 12}, {12, 2}, {13, 3}, {10, 12}, {6, 2}, {9, 1}, {9, 5}, {14, 4}, {7, 9}},
{{14, 7}, {12, 8}, {3, 7}, {6, 13}, {8, 13}, {13, 5}, {4, 14}, {10, 9}, {6, 12}, {5, 6}, {15, 4}, {14, 10}, {6, 5}, {7, 10}, {10, 14}, {0, 8}},
{{11, 10}, {7, 8}, {2, 5}, {2, 14}, {1, 12}, {10, 6}, {11, 4}, {12, 6}, {14, 8}, {13, 13}, {7, 4}, {1, 15}, {4, 11}, {11, 13}, {8, 11}, {8, 10}},
{{7, 0}, {3, 14}, {11, 5}, {6, 6}, {4, 8}, {0, 3}, {15, 6}, {0, 14}, {6, 1}, {3, 5}, {5, 7}, {11, 9}, {8, 6}, {12, 1}, {1, 13}, {9, 14}},
{{14, 1}, {15, 8}, {9, 8}, {1, 1}, {6, 9}, {13, 9}, {8, 14}, {9, 4}, {9, 11}, {1, 14}, {8, 7}, {14, 9}, {12, 14}, {5, 5}, {2, 8}, {13, 15}},
{{8, 12}, {10, 1}, {8, 9}, {0, 13}, {11, 15}, {14, 6}, {4, 2}, {6, 8}, {4, 1}, {9, 9}, {2, 13}, {0, 15}, {11, 0}, {5, 4}, {11, 11}, {1, 6}}
};

const short int INV_S_BOX_MATRIX[16][16][2] = {
{{5, 2}, {0, 9}, {6, 10}, {13, 5}, {3, 0}, {3, 6}, {10, 5}, {3, 8}, {11, 15}, {4, 0}, {10, 3}, {9, 14}, {8, 1}, {15, 3}, {13, 7}, {15, 11}},
{{7, 12}, {14, 3}, {3, 9}, {8, 2}, {9, 11}, {2, 15}, {15, 15}, {8, 7}, {3, 4}, {8, 14}, {4, 3}, {4, 4}, {12, 4}, {13, 14}, {14, 9}, {12, 11}},
{{5, 4}, {7, 11}, {9, 4}, {3, 2}, {10, 6}, {12, 2}, {2, 3}, {3, 13}, {14, 14}, {4, 12}, {9, 5}, {0, 11}, {4, 2}, {15, 10}, {12, 3}, {4, 14}},
{{0, 8}, {2, 14}, {10, 1}, {6, 6}, {2, 8}, {13, 9}, {2, 4}, {11, 2}, {7, 6}, {5, 11}, {10, 2}, {4, 9}, {6, 13}, {8, 11}, {13, 1}, {2, 5}},
{{7, 2}, {15, 8}, {15, 6}, {6, 4}, {8, 6}, {6, 8}, {9, 8}, {1, 6}, {13, 4}, {10, 4}, {5, 12}, {12, 12}, {5, 13}, {6, 5}, {11, 6}, {9, 2}},
{{6, 12}, {7, 0}, {4, 8}, {5, 0}, {15, 13}, {14, 13}, {11, 9}, {13, 10}, {5, 14}, {1, 5}, {4, 6}, {5, 7}, {10, 7}, {8, 13}, {9, 13}, {8, 4}},
{{9, 0}, {13, 8}, {10, 11}, {0, 0}, {8, 12}, {11, 12}, {13, 3}, {0, 10}, {15, 7}, {14, 4}, {5, 8}, {0, 5}, {11, 8}, {11, 3}, {4, 5}, {0, 6}},
{{13, 0}, {2, 12}, {1, 14}, {8, 15}, {12, 10}, {3, 15}, {0, 15}, {0, 2}, {12, 1}, {10, 15}, {11, 13}, {0, 3}, {0, 1}, {1, 3}, {8, 10}, {6, 11}},
{{3, 10}, {9, 1}, {1, 1}, {4, 1}, {4, 15}, {6, 7}, {13, 12}, {14, 10}, {9, 7}, {15, 2}, {12, 15}, {12, 14}, {15, 0}, {11, 4}, {14, 6}, {7, 3}},
{{9, 6}, {10, 12}, {7, 4}, {2, 2}, {14, 7}, {10, 13}, {3, 5}, {8, 5}, {14, 2}, {15, 9}, {3, 7}, {14, 8}, {1, 12}, {7, 5}, {13, 15}, {6, 14}},
{{4, 7}, {15, 1}, {1, 10}, {7, 1}, {1, 13}, {2, 9}, {12, 5}, {8, 9}, {6, 15}, {11, 7}, {6, 2}, {0, 14}, {10, 10}, {1, 8}, {11, 14}, {1, 11}},
{{15, 12}, {5, 6}, {3, 14}, {4, 11}, {12, 6}, {13, 2}, {7, 9}, {2, 0}, {9, 10}, {13, 11}, {12, 0}, {15, 14}, {7, 8}, {12, 13}, {5, 10}, {15, 4}},
{{1, 15}, {13, 13}, {10, 8}, {3, 3}, {8, 8}, {0, 7}, {12, 7}, {3, 1}, {11, 1}, {1, 2}, {1, 0}, {5, 9}, {2, 7}, {8, 0}, {14, 12}, {5, 15}},
{{6, 0}, {5, 1}, {7, 15}, {10, 9}, {1, 9}, {11, 5}, {4, 10}, {0, 13}, {2, 13}, {14, 5}, {7, 10}, {9, 15}, {9, 3}, {12, 9}, {9, 12}, {14, 15}},
{{10, 0}, {14, 0}, {3, 11}, {4, 13}, {10, 14}, {2, 10}, {15, 5}, {11, 0}, {12, 8}, {14, 11}, {11, 11}, {3, 12}, {8, 3}, {5, 3}, {9, 9}, {6, 1}},
{{1, 7}, {2, 11}, {0, 4}, {7, 14}, {11, 10}, {7, 7}, {13, 6}, {2, 6}, {14, 1}, {6, 9}, {1, 4}, {6, 3}, {5, 5}, {2, 1}, {0, 12}, {7, 13}}
};

const short int Rcon[11][2] = {{0, 0}, {0, 1}, {0, 2}, {0, 4}, {0, 8}, {1, 0}, {2, 0}, {4, 0}, {8, 0}, {1, 11}, {3, 6}};

bitstring& encrypt_AES(bitstring& str_bit, bitstring& key)
{
    if (key.get_size()!= 128)
    {
        generate_key_AES(key);
    }
    ByteMatrix* shedule = new ByteMatrix[11];
    for (int i = 0; i<11; i++)
    {
        shedule[i].initialize(4, 4);
    }
    create_key_shedule_AES(key, shedule);

    bitstring tmp(str_bit, 0, 128);
    tmp.show(64);
    encrypt_block_AES(tmp, shedule);
    tmp.show(64);
    decrypt_block_AES(tmp, shedule);
    tmp.show(64);

    return key;
}

void generate_key_AES(bitstring& key) ///////////////////////////////////////need rework/////////////////////////////////
{
    srand(time(NULL));
    bool n;
    key.clear_data();
    for (int i= 0; i<128; i++)
    {
        n = rand()%2;
        key.push(n);
    }
}


void create_key_shedule_AES(bitstring key, ByteMatrix* shedule)
{
    int index = 0;
    bitstring temp, a, b;
    for (int i = 0; i<4; i++)
    {
        for (int j = 0; j< 4; j++)
        {
            temp.clear_data();
            for (int k = index; k<index+8;k++)
            {
                temp.push(key[k]);
            }
            index += 8;
            shedule[0].set_byte(j, i, temp);
        }
    }

    bitstring collumn[4];
    short int new_byte[2];
    for (int iteration = 1; iteration < 11; iteration++)
    {

        collumn[4] = shedule[iteration].get_byte(0, 3);
        //errase last collumn
        for (int i = 0; i<3; i++)
        {
            collumn[i] = shedule[iteration-1].get_byte(i+1, 3);
        }
        //apply sbox
        for (int i = 0; i<4; i++)
        {
            a = collumn[i].Hbit(4);
            b = collumn[i].Lbit(4);
            new_byte[0] = S_BOX_MATRIX[a.return_int()][b.return_int()][0];
            new_byte[1] = S_BOX_MATRIX[a.return_int()][b.return_int()][1];
            a.initialize(new_byte[0], 4);
            b.initialize(new_byte[1], 4);
            collumn[i] = a + b;
        }
        //apply rcon
        apply_Rcon(&collumn[0], iteration);
        //initialize first collumn of iteration key
        for (int i = 0; i<4; i++)
        {
            temp = shedule[iteration].get_byte(i, 0);
            shedule[iteration].set_byte(i, 0, collumn[i]^temp);
        }
        //initialize other collumn
        for (int j = 1; j<4; j++)
        {
            for (int i = 0; i<4; i++)
            {
                collumn[i] = shedule[iteration].get_byte(i, j-1);
                temp = shedule[iteration-1].get_byte(i, j);
                shedule[iteration].set_byte(i, j, collumn[i]^temp);
            }
        }

    }

}


void apply_Rcon(bitstring* collumn, int index)
{
    short int new_byte[2];
    bitstring a, b, temp(0, 8);
    new_byte[0] = Rcon[index][0];
    new_byte[1] = Rcon[index][1];
    a.initialize(new_byte[0], 4);
    b.initialize(new_byte[1], 4);
    temp = a + b;
    a = *collumn;
    *collumn = temp^a;
}


bool encrypt_block_AES(bitstring& block, ByteMatrix* shedule)
{
    //feel state
    int index = 0;
    bitstring temp, a, b;
    ByteMatrix state(4, 4);
    for (int i = 0; i<4; i++)
    {
        for (int j = 0; j< 4; j++)
        {
            temp.clear_data();
            for (int k = index; k<index+8;k++)
            {
                temp.push(block[k]);
            }
            index += 8;
            state.set_byte(j, i, temp);
        }
    }

    add_round_key(&state, &shedule[0]);

    for (int index = 1; index < 10; index++)
    {
        sub_byte(&state);
        shift_rows(&state);
        mix_colums(&state);
        add_round_key(&state, &shedule[index]);
    }
    sub_byte(&state);
    shift_rows(&state);
    add_round_key(&state, &shedule[10]);

    block.clear_data();
    for (int i = 0; i<4; i++)
    {
        for (int j = 0; j< 4; j++)
        {
            temp = state.get_byte(j, i);
            block += temp;
        }
    }
}


bool add_round_key(ByteMatrix* state, ByteMatrix* key)
{
    bitstring temp;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            temp = state->get_byte(i, j);
            temp = temp^key->get_byte(i ,j);
            state->set_byte(i, j, temp);
        }
    }
}


void sub_byte(ByteMatrix* state)
{
    bitstring a, b;
    short int new_byte[2]{0};
    for (int j = 0; j<4; j++)
    {
        for (int i = 0; i<4; i++)
        {
            a = state->get_byte(i, j).Hbit(4);
            b = state->get_byte(i, j).Lbit(4);
            new_byte[0] = S_BOX_MATRIX[a.return_int()][b.return_int()][0];
            new_byte[1] = S_BOX_MATRIX[a.return_int()][b.return_int()][1];
            a.initialize(new_byte[0], 4);
            b.initialize(new_byte[1], 4);
            state->set_byte(i, j, a + b);
        }
    }
}


void shift_rows(ByteMatrix* state)
{
    for (int i = 1; i<4; i++)
    {
        state->cycle_rotate_left(i, i);
    }
}


void mix_colums(ByteMatrix* state)
{

}


bool decrypt_block_AES(bitstring& block, ByteMatrix* shedule)
{
    //feel state
    int index = 0;
    bitstring temp, a, b;
    ByteMatrix state(4, 4);
    for (int i = 0; i<4; i++)
    {
        for (int j = 0; j< 4; j++)
        {
            temp.clear_data();
            for (int k = index; k<index+8;k++)
            {
                temp.push(block[k]);
            }
            index += 8;
            state.set_byte(j, i, temp);
        }
    }

    add_round_key(&state, &shedule[10]);
    inv_shift_rows(&state);
    inv_sub_byte(&state);

    for (int index = 1; index < 10; index++)
    {
        add_round_key(&state, &shedule[10-index]);
        mix_colums(&state);
        inv_shift_rows(&state);
        inv_sub_byte(&state);
    }

    add_round_key(&state, &shedule[0]);

    block.clear_data();
    for (int i = 0; i<4; i++)
    {
        for (int j = 0; j< 4; j++)
        {
            temp = state.get_byte(j, i);
            block += temp;
        }
    }
}


void inv_sub_byte(ByteMatrix* state)
{
    bitstring a, b;
    short int new_byte[2]{0};
    for (int j = 0; j<4; j++)
    {
        for (int i = 0; i<4; i++)
        {
            a = state->get_byte(i, j).Hbit(4);
            b = state->get_byte(i, j).Lbit(4);
            new_byte[0] = INV_S_BOX_MATRIX[a.return_int()][b.return_int()][0];
            new_byte[1] = INV_S_BOX_MATRIX[a.return_int()][b.return_int()][1];
            a.initialize(new_byte[0], 4);
            b.initialize(new_byte[1], 4);
            state->set_byte(i, j, a + b);
        }
    }
}


void inv_shift_rows(ByteMatrix* state)
{
    for (int i = 1; i<4; i++)
    {
        state->cycle_rotate_right(i, i);
    }
}




















