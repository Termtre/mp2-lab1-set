// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp), MaxPower(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength())
{
}

TSet::operator TBitField()
{
    TBitField temp(BitField);

    return temp;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return this->BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    this->BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    this->BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (this != &s)
    {
        this->BitField = s.BitField;
        this->MaxPower = s.MaxPower;
    }

    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return this->BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return !(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet temp(this->BitField | s.BitField);

    return temp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet temp(*this);
    temp.InsElem(Elem);

    return temp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet temp(*this);
    temp.DelElem(Elem);

    return temp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet temp(this->BitField & s.BitField);

    return temp;
}

TSet TSet::operator~(void) // дополнение
{
    TSet temp(~this->BitField);

    return temp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &bf) // ввод
{
    cin >> bf.BitField;

    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &bf) // вывод
{
    //cout << bf.BitField;
    for (int i = 0; i < bf.MaxPower; i++)
        if (bf.IsMember(i))
            ostr << 1 << " ";
        else
            ostr << 0 << " ";
    return ostr;
}