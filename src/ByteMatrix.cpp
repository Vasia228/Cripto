#include "ByteMatrix.h"
using namespace std;

ByteMatrix::ByteMatrix()
{

}

ByteMatrix::ByteMatrix(int a, int b)
{
    table = new bitstring*[a];
    for (int i = 0; i < a; i++)
    {
        table[i] = new bitstring[b];
    }
}

void ByteMatrix::initialize(int a, int b)
{
    table = new bitstring*[a];
    for (int i = 0; i < a; i++)
    {
        table[i] = new bitstring[b];
    }
}

ByteMatrix::~ByteMatrix()
{
    //dtor
}

void ByteMatrix::set_byte(int a, int b, bitstring& byte)
{
    table[a][b].clear_data();
    for(int i = 0; i < byte.get_size(); i++)
    {
        table[a][b].push(byte[i]);
    }
}

void ByteMatrix::cycle_rotate_left(int index, int num)
{
    bitstring tmp[4];
    for (int i = 0; i<4-num; i++)
    {
        tmp[i] = table[index][(num)+i];
    }
    for (int i = 0; i<num; i++)
    {
        tmp[(4-num)+i] = table[index][i];
    }
    for (int i = 0; i<4; i++)
    {
        table[index][i] = tmp[i];
    }
}

void ByteMatrix::cycle_rotate_right(int index, int num)
{
    bitstring tmp[4];
    for (int i = 0; i<num; i++)
    {
        tmp[i] = table[index][(4-num)+i];
    }
    for (int i = 0; i<4-num; i++)
    {
        tmp[num+i] = table[index][i];
    }
    for (int i = 0; i<4; i++)
    {
        table[index][i] = tmp[i];
    }
}

void ByteMatrix::show_byte(int a, int b, bool enter)
{
    table[a][b].show(8, enter);
}

void ByteMatrix::show()
{
    for (int i = 0; i<4; i++)
    {
        for (int j = 0; j<4; j++)
        {
            show_byte(i, j, false);
            cout<<" ";
        }
        cout<<endl;
    }
}
