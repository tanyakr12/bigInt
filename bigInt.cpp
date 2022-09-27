#include <bits/stdc++.h>
using namespace std;

class BigInt{
	string number;
public:

	// Constructors
	BigInt(unsigned long long n = 0);
	BigInt(string &);
	BigInt(const char *);
	BigInt(BigInt &);

	// Helper Functions
	friend bool Null (const BigInt &);
	friend int Lenght (const BigInt &);
	int operator[] (const int) const; // const keyword mtlb ye -> [] argument ki value nhi change krne waala

    /* --------- operator overloading --------- */

	// Direct assignment (=)
	BigInt &operator= (const BigInt &);

	// Incrementation (++) and decrement(--) opreator (pre and post)
	BigInt &operator++ ();
	BigInt operator++ (int temp);
	BigInt &operator-- ();
	BigInt operator-- (int temp);

	// Addition and Subtraction (+, -, +=, -=)
	friend BigInt &operator+= (BigInt &, const BigInt &);
	friend BigInt operator+ (const BigInt &, const BigInt &);
	friend BigInt operator- (const BigInt &, const BigInt &);
	friend BigInt &operator-= (BigInt &, const BigInt &);

	// Comparison operators (==, !=, >, <, >=, <=)
	friend bool operator== (const BigInt &, const BigInt &);
	friend bool operator!= (const BigInt &, const BigInt &);

	friend bool operator> (const BigInt &, const BigInt &);
	friend bool operator>= (const BigInt &, const BigInt &);
	friend bool operator< (const BigInt &, const BigInt &);
	friend bool operator<= (const BigInt &, const BigInt &);

	// Multiplication and Division (*, *=, /, /=)
	friend BigInt &operator*= (BigInt &, const BigInt &);
	friend BigInt operator* (const BigInt &, const BigInt &);
	friend BigInt &operator/= (BigInt &, const BigInt &);
	friend BigInt operator/ (const BigInt &, const BigInt &);

	// Modulo (%)
	friend BigInt operator% (const BigInt &, const BigInt &);
	friend BigInt &operator%= (BigInt &, const BigInt &);

	// Read and Write (<<, >>)
	friend ostream &operator<< (ostream &,const BigInt &);
	friend istream &operator>> (istream &, BigInt &);
};

/* ------------------ function definitions ------------------ */

/* --------- defining constructors --------- */

BigInt::BigInt(string & s){
	number = "";
	int n = s.size();
	for (int i = n - 1; i >= 0;i--){
		if(!isdigit(s[i]))
			throw("ERROR");
		number.push_back(s[i] - '0');
	}
}
BigInt::BigInt(unsigned long long nr){
	do{
		number.push_back(nr % 10);
		nr /= 10;
	} while (nr);
}
BigInt::BigInt(const char *s){
	number = "";
	for (int i = strlen(s) - 1; i >= 0;i--)
	{
		if(!isdigit(s[i]))
			throw("ERROR");
		number.push_back(s[i] - '0');
	}
}
BigInt::BigInt(BigInt & a){
	number = a.number;
}

/* --------- defining helper functions --------- */

bool Null(const BigInt& a){
	if(a.number.size() == 1 && a.number[0] == 0)
		return true;
	return false;
}
int Lenght(const BigInt & a){
	return a.number.size();
}
int BigInt::operator[](const int index)const{
	if(number.size() <= index || index < 0)
		throw("ERROR");
	return number[index];
}

/* --------- overloading operators --------- */

// Comparision opreators (==, !=, >, <, >=, <=)

bool operator==(const BigInt &a, const BigInt &b){
	return a.number == b.number;
}
bool operator!=(const BigInt & a,const BigInt &b){
	return !(a == b);
}
bool operator<(const BigInt&a,const BigInt&b){
	int n = Lenght(a), m = Lenght(b);
	if(n != m)
		return n < m;
	while(n--)
		if(a.number[n] != b.number[n])
			return a.number[n] < b.number[n];
	return false;
}
bool operator>(const BigInt&a,const BigInt&b){
	return b < a;
}
bool operator>=(const BigInt&a,const BigInt&b){
	return !(a < b);
}
bool operator<=(const BigInt&a,const BigInt&b){
	return !(a > b);
}

// Assignment opreators (=)

BigInt &BigInt::operator=(const BigInt &a){
	number = a.number;
	return *this;
}

// Incrementation (++) and decrement(--) opreator

BigInt &BigInt::operator++(){
	int i, n = number.size();
	for (i = 0; i < n && number[i] == 9;i++)
		number[i] = 0;
	if(i == n)
		number.push_back(1);
	else
		number[i]++;
	return *this;
}
BigInt BigInt::operator++(int temp){
	BigInt aux;
	aux = *this;
	++(*this);
	return aux;
}

BigInt &BigInt::operator--(){
	if(number[0] == 0 && number.size() == 1)
		throw("UNDERFLOW");
	int i, n = number.size();
	for (i = 0; number[i] == 0 && i < n;i++)
		number[i] = 9;
	number[i]--;
	if(n > 1 && number[n - 1] == 0)
		number.pop_back();
	return *this;
}
BigInt BigInt::operator--(int temp){
	BigInt aux;
	aux = *this;
	--(*this);
	return aux;
}

// Addition and Subtraction operator  (+, -, +=, -=)

BigInt &operator+=(BigInt &a,const BigInt& b){
	int t = 0, s, i;
	int n = Lenght(a), m = Lenght(b);
	if(m > n)
		a.number.append(m - n, 0);
	n = Lenght(a);
	for (i = 0; i < n;i++){
		if(i < m)
			s = (a.number[i] + b.number[i]) + t;
		else
			s = a.number[i] + t;
		t = s / 10;
		a.number[i] = (s % 10);
	}
	if(t)
		a.number.push_back(t);
	return a;
}
BigInt operator+(const BigInt &a, const BigInt &b){
	BigInt temp;
	temp = a;
	temp += b;
	return temp;
}

BigInt &operator-=(BigInt&a,const BigInt &b){
	if(a < b)
		throw("UNDERFLOW");
	int n = Lenght(a), m = Lenght(b);
	int i, t = 0, s;
	for (i = 0; i < n;i++){
		if(i < m)
			s = a.number[i] - b.number[i]+ t;
		else
			s = a.number[i]+ t;
		if(s < 0)
			s += 10,
			t = -1;
		else
			t = 0;
		a.number[i] = s;
	}
	while(n > 1 && a.number[n - 1] == 0)
		a.number.pop_back(),
		n--;
	return a;
}
BigInt operator-(const BigInt& a,const BigInt&b){
	BigInt temp;
	temp = a;
	temp -= b;
	return temp;
}

// Multiplication and Division operator (*, *=, /, /=)

BigInt &operator*=(BigInt &a, const BigInt &b)
{
	if(Null(a) || Null(b)){
		a = BigInt();
		return a;
	}
	int n = a.number.size(), m = b.number.size();
	vector<int> v(n + m, 0);
	for (int i = 0; i < n;i++)
		for (int j = 0; j < m;j++){
			v[i + j] += (a.number[i] ) * (b.number[j]);
		}
	n += m;
	a.number.resize(v.size());
	for (int s, i = 0, t = 0; i < n; i++)
	{
		s = t + v[i];
		v[i] = s % 10;
		t = s / 10;
		a.number[i] = v[i] ;
	}
	for (int i = n - 1; i >= 1 && !v[i];i--)
			a.number.pop_back();
	return a;
}
BigInt operator*(const BigInt&a,const BigInt&b){
	BigInt temp;
	temp = a;
	temp *= b;
	return temp;
}

BigInt &operator/=(BigInt& a,const BigInt &b){
	if(Null(b))
		throw("Arithmetic Error: Division By 0");
	if(a < b){
		a = BigInt();
		return a;
	}
	if(a == b){
		a = BigInt(1);
		return a;
	}
	int i, indexing = 0, cc;
	int n = Lenght(a), m = Lenght(b);
	vector<int> vec(n, 0);
	BigInt t;
	for (i = n - 1; t * 10 + a.number[i] < b;i--){
		t *= 10;
		t += a.number[i] ;
	}
	for (; i >= 0; i--){
		t = t * 10 + a.number[i];
		for (cc = 9; cc * b > t;cc--);
		t -= cc * b;
		vec[indexing++] = cc;
	}
	a.number.resize(vec.size());
	for (i = 0; i < indexing;i++)
		a.number[i] = vec[indexing - i - 1];
	a.number.resize(indexing);
	return a;
}
BigInt operator/(const BigInt &a,const BigInt &b){
	BigInt temp;
	temp = a;
	temp /= b;
	return temp;
}

BigInt &operator%=(BigInt& a,const BigInt &b){
	if(Null(b))
		throw("Arithmetic Error: Division By 0");
	if(a < b){
		a = BigInt();
		return a;
	}
	if(a == b){
		a = BigInt(1);
		return a;
	}
	int i, indexing = 0, cc;
	int n = Lenght(a), m = Lenght(b);
	vector<int> vec(n, 0);
	BigInt t;
	for (i = n - 1; t * 10 + a.number[i] < b;i--){
		t *= 10;
		t += a.number[i];
	}
	for (; i >= 0; i--){
		t = t * 10 + a.number[i];
		for (cc = 9; cc * b > t;cc--);
		t -= cc * b;
		vec[indexing++] = cc;
	}
	a = t;
	return a;
}
BigInt operator%(const BigInt &a,BigInt &b){
	BigInt temp;
	temp = a;
	temp %= b;
	return temp;
}

// Read and Write opreator (<<, >>)

istream &operator>>(istream &in,BigInt&a){
	string s;
	in >> s;
	int n = s.size();
	for (int i = n - 1; i >= 0;i--){
		if(!isdigit(s[i]))
			throw("INVALID NUMBER");
		a.number[n - i - 1] = s[i];
	}
	return in;
}

ostream &operator<<(ostream &out,const BigInt &a){
	for (int i = a.number.size() - 1; i >= 0;i--)
		cout << (short)a.number[i];
	return cout;
}

//Driver code
int main()
{

	// To define name use: BigInt varName("522545444");
	// To get length use: Length(varName);
	// other opreations are as usual
	return 0;
}
