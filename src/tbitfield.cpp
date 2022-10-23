// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

#ifdef it_allowed
const int TBitField::for_shift(int n)
{
	int shift = 0, temp = number_of_bits - 1;

	while (temp != 0)
	{
		temp >>= 1;
		shift += 1;
	}

	return shift;
}
#endif

TBitField::TBitField(int len)
{
	if (len < 0)
		throw invalid_argument("len must be positive or zero");

	BitLen = len;

#ifdef it_allowed
	MemLen = (len + number_of_bits - 1) >> shift;
#else
	MemLen = (len / (sizeof(TELEM) * 8)) + 1;
#endif

	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = (TELEM)0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	this->BitLen = bf.BitLen;
	this->MemLen = bf.MemLen;
	this->pMem = new TELEM[this->MemLen];
	for (int i = 0; i < this->MemLen; i++)
		this->pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
#ifdef it_allowed
	return n >> shift;
#else
	return n / (sizeof(TELEM) * 8);
#endif
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
#ifdef it_allowed
	return 1 << (n & (number_of_bits - 1));
#else
	return 1 << (n & (sizeof(TELEM) * 8) - 1);
#endif
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n >= BitLen) || (n < 0))
		throw out_of_range("n can't be greater or equal than BitLen or less than zero");

	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n >= BitLen) || (n < 0))
		throw out_of_range("n can't be greater or equal than BitLen or less than zero");

	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n >= BitLen) || (n < 0))
		throw out_of_range("n can't be greater or equal than BitLen or less than zero");

	return pMem[GetMemIndex(n)] & GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf)
	{
		delete[] this->pMem;
		this->BitLen = bf.BitLen;
		this->MemLen = bf.MemLen;
		this->pMem = new TELEM[this->MemLen];
		for (int i = 0; i < this->MemLen; i++)
			this->pMem[i] = bf.pMem[i];
	}

	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (this->BitLen != bf.BitLen)
		return 0;
	for (int i = 0; i < this->MemLen; i++)
		if (this->pMem[i] != bf.pMem[i])
			return 0;

	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField temp(1);
	int size;
	if (this->BitLen > bf.BitLen)
	{
		temp = *this;
		size = bf.MemLen;
	}

	else
	{
		temp = bf;
		size = this->MemLen;
	}

	for (int i = 0; i < size; i++)
		temp.pMem[i] = this->pMem[i] | bf.pMem[i];

	return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField temp(1);
	int size;
	if (this->BitLen > bf.BitLen)
	{
		temp = *this;
		size = bf.MemLen;
	}

	else
	{
		temp = bf;
		size = this->MemLen;
	}

	for (int i = 0; i < size; i++)
		temp.pMem[i] = this->pMem[i] & bf.pMem[i];

	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField temp(*this);
	for (int i = 0; i < this->MemLen; i++)
		temp.pMem[i] = ~this->pMem[i];

	temp.pMem[MemLen - 1] &= GetMemMask(BitLen) - 1;

	return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int size = bf.GetLength();
	int temp;
	for (int i = size - 1; i > -1; i--)
	{
		cout << "Enter " << size - i << " bit: ";
		istr >> temp;

		if ((temp != 0) && (temp != 1))
			throw invalid_argument("Bit must be 0 or 1");

		if (temp)
			bf.SetBit(i);
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.GetLength(); i++)
	{
		//if (bf.GetBit(i))
		//	ostr << 1 << " ";
		//else
		//	ostr << 0 << " ";
		if (!bf.GetBit(i))
			ostr << i << " ";
	}

	return ostr;
}
