#include "MathClass.h"

MathClass::MathClass(int i)
{
    _value = i;
}

MathClass::~MathClass()
{
}

int MathClass::multiply(int a)
{
    return a * _value;
}

void MathClass::inc(void)
{
    _value++;
}

void MathClass::dec(void)
{
    _value--;
}


