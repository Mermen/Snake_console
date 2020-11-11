#include <iostream>

#include "cnumericrow.h"

using namespace std;

CNumericRow::CNumericRow(unsigned int _nSize)
{
    nSize = _nSize;
    sArray = _nSize;
    nReserveSize = _nSize * 3;
    a = new int[nReserveSize];
}

CNumericRow::~CNumericRow()
{
    clear();
}

void CNumericRow::clear()
{
    delete[] a;
}

CNumericRow::CNumericRow(const CNumericRow& _copy)
{
    sArray = _copy.sArray;
    nSize = _copy.nSize;
    nReserveSize = _copy.nReserveSize;
    a = new int[nReserveSize];
    for (unsigned int i = sArray; i < nSize+sArray; i++)
    {
        a[i] = _copy.a[i];
    }
}

CNumericRow& CNumericRow::operator=(const CNumericRow& _copy)
{
    clear();

    nSize = _copy.nSize;
    nReserveSize = _copy.nReserveSize;
    a = new int[nReserveSize];
    for (unsigned int i = sArray; i < nSize + sArray; i++)
    {
        a[i] = _copy.a[i];
    }

    return *this;
}

unsigned int CNumericRow::getSize() const
{
    return nSize;
}

void CNumericRow::print() const
{
    for (int i = sArray; i < nSize+sArray; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

int& CNumericRow::operator[](const unsigned int _nIdx)
{
    if ((_nIdx) >= nSize)
    {
        cerr << "Wrong index! " << _nIdx << " >=  " << (nSize) << "!" << endl;
        exit(1);
    }

    return a[_nIdx+sArray];
}

void CNumericRow::resize(const unsigned int _newSize, char _pFlag)
{
    if (_pFlag == 'b')
    {
        if (_newSize <= nReserveSize - sArray)
        {
            
            for (int i = nSize + sArray; i < _newSize + sArray; i++)
            {
                a[i] = 0;
            }
            nSize = _newSize;
            return;
        }

        nReserveSize = _newSize * 3;
        
        int* tempA = a;

        a = new int[nReserveSize];

        for (int i = sArray; i < (_newSize+sArray); i++)
        {
            a[i] = (i < (nSize + sArray)) ? tempA[i] : 0;
        }

        delete[] tempA;
        nSize = _newSize;
    }
    else if (_pFlag == 'f')
    {
        if (_newSize <= (sArray + nSize))
        {
            if (_newSize < nSize)
            {
                nSize = _newSize;
                sArray += 1;
                return;
            }
            else if (_newSize > nSize)
            {
                nSize = _newSize;
                sArray -= 1;
                return;
            }
            else
            {
                return;
            }
        }
        else
        {

            int* tempA = a;
            nReserveSize = _newSize * 3;
            a = new int[nReserveSize];
            for (int i = sArray; i < (_newSize + sArray-1); i++)
            {
                a[_newSize+i] = (i < (nSize + sArray)) ? tempA[i] : 0;
            }

            delete[] tempA;
            nSize = _newSize;
            sArray = _newSize - 1;
        }
    }
}


void CNumericRow::push_back(const unsigned int _n)
{
    resize(nSize + 1, 'b');
    a[sArray+nSize - 1] = _n;
}

void CNumericRow::push_front(const unsigned int _n)
{
    resize(nSize + 1, 'f');
    /*
    for (int i = nSize - 1 + sArray; i > 0+sArray; i--)
    {
        a[i] = a[i - 1];
    }
    */
    a[sArray] = _n;
}

int CNumericRow::pop_back()
{
    int nTemp = a[nSize - 1 + sArray];
    resize(nSize - 1, 'b');

    return nTemp;
}

int CNumericRow::pop_front()
{
    int nTemp = a[0 + sArray];
    /*
    for (unsigned int i = 0+sArray; i < (nSize - 1)+sArray; i++)
    {
        a[i] = a[i + 1];
    }
    */
    resize(nSize - 1, 'f');

    return nTemp;
}
