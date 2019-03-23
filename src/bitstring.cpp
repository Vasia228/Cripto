#include "bitstring.h"

#define SHIFT 96

/////////////////////////////////////////////////////////////// constructors
bitstring::bitstring(){}

bitstring::bitstring(string& str)
{
    tolow(str);

    int buffer[5],iter,tmp;
    for (int i= 0; i<str.size(); i++)
    {
        tmp= (int)str[i]-SHIFT;
        if (tmp>25 || tmp<0) continue;
        iter= 0;
        memset(buffer, 0, sizeof(buffer));

        while (tmp>0)
        {
            buffer[4-iter]=tmp%2;
            tmp=tmp/2;
            iter++;
        }
        for (int i= 0; i<5; i++)data.push_back(buffer[i]);
    }
}

bitstring::bitstring(int num)
{
    bitstring(num, 0);
}

bitstring::bitstring(int num, int element_size)
{
    vector<bool> tmp;
    while (num>0)
    {
        tmp.push_back(num%2);
        num= num/2;
    }
    int size_tmp= tmp.size();
    if (element_size-size_tmp>0)
    {
        for (int i= 0; i<element_size-size_tmp; i++)data.push_back(0);
    }
    for (int i= 0; i<size_tmp; i++)data.push_back(tmp[(size_tmp-1)-i]);
}

bitstring::bitstring(bitstring& str_bit)
{
    *this= str_bit;
}

bitstring::bitstring(bitstring& str_bit, int size_of_slice)
{
    int str_size=str_bit.data.size();
    if (abs(size_of_slice)>str_size)
    {
        size_of_slice= str_size;
    }

    if (size_of_slice>0)
    {
        for (int i= 0; i<size_of_slice; i++)
        {
            data.push_back(str_bit.data[i]);
        }
    }
    else
    {
        for (int i= size_of_slice+1; i<=0; i++)
        {
            data.push_back(str_bit.data[(str_size-1)+i]);
        }
    }
}

bitstring::bitstring(bitstring& str_bit, int start_index, int size_of_slice)
{
    if (start_index+size_of_slice>str_bit.data.size())
    {
        size_of_slice= str_bit.data.size()-start_index;
    }
    for (int i= 0; i<size_of_slice; i++)
    {
        data.push_back(str_bit.data[start_index+i]);
    }
}

/////////////////////////////////////////////////////////////////////////destructor

bitstring::~bitstring()
{
    delete &data;
}

/////////////////////////////////////////////////////////////////////////overloaded operators

bitstring& bitstring::operator=(bitstring& str_bin)
{
    data.clear();
    for (int i= 0; i<str_bin.data.size(); i++)
    {
        data.push_back(str_bin.data[i]);
    }
    return *this;
}

void bitstring::operator=(vector<bool>& tmp)
{
    data.clear();
    for (int i= 0; i<tmp.size(); i++)
    {
        data.push_back(tmp[i]);
    }
}

bool bitstring::operator[](int index)
{
    if (index>=0 && index<data.size())
    {
        return data[index];
    }
}

void bitstring::operator()(int index, bool value)
{
    if (index>=0 && index<data.size())
    {
        data[index]= value;
    }
}

bitstring& bitstring::operator+(bitstring& str_bit)
{
    bitstring* tmp= new bitstring;
    for (int i= 0; i<data.size(); i++)tmp->push(data[i]);
    for (int i= 0; i<str_bit.get_size(); i++)tmp->push(str_bit[i]);
    return *tmp;
}

void bitstring::operator+=(bitstring& str_bit)
{
    for (int i= 0; i<str_bit.get_size(); i++)this->push(str_bit[i]);
}

bitstring& bitstring::operator^(bitstring& str_bit)
{
    bitstring* tmp= new bitstring;
    for (int i= 0; i<data.size(); i++)
    {
        if (data[i]+str_bit[i]==1)tmp->push(1);
        else tmp->push(0);
    }
    return *tmp;
}
/////////////////////////////////////////////////////////////////////////methods

void bitstring::tolow(string& str)
{
    for (int i= 0; i<str.size(); i++)
    {
        str[i]= tolower(str[i]);
    }
}

string bitstring::to_string()
{
    string* str= new string;
    int strnum, range= data.size()-(data.size()%5);

    for (int i= 0; i<range; i+=5)
    {
        strnum=data[i]*16 + data[i+1]*8 + data[i+2]*4 + data[i+3]*2 + data[i+4]*1;
        if (strnum!= 0)
        {
            strnum+=SHIFT;
            str->push_back(char(strnum));
        }
    }

    return *str;
}

void bitstring::push(bool n)
{
    data.push_back(n);
}

void bitstring::clear_data()
{
    data.clear();
}

bitstring& bitstring::Hbit(int size_of_slice)
{
    bitstring* tmp= new bitstring(*this, size_of_slice);
    return *tmp;
}

bitstring& bitstring::Lbit(int size_of_slice)
{
    bitstring* tmp= new bitstring(*this, -size_of_slice);
    return *tmp;
}

void bitstring::cycle_rotate_left(int n)
{
    for (int i= 0; i<n; i++)
    {
        cycle_rotate_left();
    }
}

void bitstring::cycle_rotate_left()
{
    bool tmp= data[0];
    for (int i= 1; i<data.size(); i++)
    {
        data[i-1]= data[i];
    }
    data[data.size()-1]= tmp;
}

void bitstring::show(int size_of_slice)
{
    int space=0;
    for (int i= 0; i<data.size(); i++)
    {
        if (space==size_of_slice)
        {
            cout<<" ";
            space=0;
        }
        cout<<data[i];
        space++;
    }
    cout<<endl;
}

void bitstring::show_size()
{
    cout<<data.size()<<endl;
}
