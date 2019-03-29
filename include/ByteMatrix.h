#ifndef BYTEMATRIX_H
#define BYTEMATRIX_H

#include "bitstring.h"

class ByteMatrix
{
    public:
        ByteMatrix();
        ByteMatrix(int a, int b);
        void initialize(int a, int b);
        virtual ~ByteMatrix();

        bitstring& get_byte(int a, int b){return table[a][b];};
        void set_byte(int a, int b, bitstring& byte);
        void cycle_rotate_left(int index, int num);
        void cycle_rotate_right(int index, int num);
        void show_byte(int a, int b, bool enter = true);
        void show();
    protected:

    private:
        bitstring** table;
};

#endif // BYTEMATRIX_H
