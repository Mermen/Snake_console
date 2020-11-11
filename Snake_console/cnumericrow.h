class CNumericRow
{
    unsigned int nSize;
    unsigned int nReserveSize;
    unsigned int sArray;
    int* a;

    void clear();

public:

    CNumericRow(unsigned int _nSize);
    CNumericRow(const CNumericRow& _copy);
    ~CNumericRow();
    CNumericRow& operator=(const CNumericRow& _copy);

    unsigned int getSize() const;
    void print() const;

    void resize(const unsigned int _newSize, char _pFlag);

    int& operator[](const unsigned int _nIdx);

    void push_back(const unsigned int _n);
    void push_front(const unsigned int _n);


    int pop_back();
    int pop_front();
};
