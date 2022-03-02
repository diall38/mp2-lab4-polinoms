#pragma once

#include <iostream>
#include <string>
#include <vector>

template <class T>
class list {
public:
	class node {
	public:
		T data;
		node* next;
		node(T value = 0, node* next_ = NULL) : next(next_), data(value) {}
	};
	node* first;
	size_t size;

	class iterator {
	protected:
		node* ptr;
	public:
		iterator() : ptr(NULL) {}
		iterator(node* ptr_) : ptr(ptr_) {}
		iterator(const iterator& iter) : ptr(iter.ptr) {}

		iterator& operator++ ()
		{
			ptr = ptr->next;
			return *this;
		}

		iterator operator++ (int)
		{
			iterator iter(*this);
			++(*this);
			return iter;
		}

		node*& operator*() { return ptr; }
		node* operator->() { return ptr; }
		bool operator== (iterator iter) const { return ptr == iter.ptr; }
		bool operator!= (iterator iter) const { return !(*this == iter); }
	};

	list() : first(NULL), size(0) {}

	list(const list<T>& lst) : first(NULL), size(0) {
		node* pcurr = first;

		for (iterator it_curr = lst.begin(); it_curr != lst.end(); ++it_curr) {
			pcurr = insert(pcurr, it_curr->data);
			//pcurr = pcurr->next;
		}
	}

	~list() {
		while (first) {
			node* tmp = first;
			first = tmp->next;
			delete tmp;
			size--;
		}
	}

	void print()
	{
		iterator iter = begin();
		while (iter != end()) {
			std::cout << iter->data << " ";
			iter++;
		}
		std::cout << std::endl;
	}

	node* get_first() { return first; }

	iterator search(T& value)
	{
		iterator it = begin();
		while (it != end()) {
			if (it->data == value)
				break;
			it++;
		}
		return it;
	}

	void erase(node* pos)
	{
		if (pos == NULL) {
			if (!size) { throw "list is empty"; }
			node* tmp = first;
			first = tmp->next;
			delete tmp;
		}
		else {
			node* p = pos->next;
			pos->next = p->next;
			delete p;
		}
		size--;
	}

	iterator begin() const
	{
		iterator it(first);
		return it;
	}

	iterator end() const
	{
		iterator it(NULL);
		return it;
	}

	bool empty() { return size == 0; }
	size_t get_size() { return size; }

	node* insert(node* pos, const T& value)
	{
		node* tmp;
		if (pos == NULL) {
			tmp = new node(value, first);
			first = tmp;
		}
		else {
			tmp = new node(value, pos->next);
			pos->next = tmp;
		}
		size++;
		return tmp;
	}
};

#define EXP 9

class polynomial {//:public list {
public:
	class monomial {
	public:
		size_t degree;				// monomial degree in the range from 0 to 999 
		double multiplier;			// coefficient in front of the monomial  

		monomial() : degree(0), multiplier(0) {}
		monomial(size_t t_degree, int t_mult) : degree(t_degree), multiplier(t_mult) {}
		monomial(const monomial& t_monom) : degree(t_monom.degree), multiplier(t_monom.multiplier) {}
		virtual ~monomial() {

		}
		monomial& operator*=(const monomial& m) {
			if (degree / 100 + m.degree / 100 > EXP || degree / 10 % 10 + m.degree / 10 % 10 > EXP \
				|| degree % 10 + m.degree % 10 > EXP)
				throw "too big degree of monomial";
			else {
				multiplier *= m.multiplier;
				degree += m.degree;
				return (*this);
			}
		}
		monomial operator*(const monomial& m) {
			monomial tmp = (*this);
			tmp *= m;
			return tmp;
		}

		bool operator==(const monomial& m) const {
			return (abs(multiplier - m.multiplier) <= 1e-10 && degree == m.degree);
		}

		bool operator!=(const monomial& m) const {
			return !((*this) == m);
		}

		void print() const {
			if (multiplier < 0) std::cout << " - ";
			if (abs(multiplier) - 1 > 1e-10 || \
				abs(multiplier) - 1 < 1e-10 && degree == 0) std::cout << abs(multiplier);
			int deg_x = degree / 100, deg_y = degree / 10 % 10, deg_z = degree % 10;

			if (deg_x > 1) std::cout << "x^" << deg_x;
			else if (deg_x == 1) std::cout << "x";

			if (deg_y > 1) std::cout << "y^" << deg_y;
			else if (deg_y == 1) std::cout << "y";

			if (deg_z > 1) std::cout << "z^" << deg_z;
			else if (deg_z == 1) std::cout << "z";
		}
	};
public:
	list<monomial> polynom;
public:
	polynomial() {}
	polynomial(const polynomial& p) : polynom(p.polynom) {}
	polynomial(std::string s) {
		translator(s);
		print();
	}
	virtual ~polynomial() {
		clear();
	}

	void print() const {
		auto it = polynom.begin();
		(*it)->data.print();
		++it;
		while (it != polynom.end()) {
			if ((*it)->data.multiplier > 1e-10)
				std::cout << " + ";
			(*it)->data.print();
			++it;
		}
		std::cout << '\n';
	}

	void insert(const monomial& m) {
		if (abs(m.multiplier) < 1e-10) return;

		auto it = polynom.begin();
		if (it == polynom.end()) {
			polynom.insert(NULL, m);
			return;
		}

		list<polynomial::monomial>::iterator ans = NULL;
		auto prev_it = it;

		while (it != polynom.end()) {

			if ((*it)->data.degree == m.degree) {

				(*it)->data.multiplier += m.multiplier;

				if (abs((*it)->data.multiplier) < 1e-10) {
					if (it == prev_it && it == polynom.begin())
						polynom.erase(NULL);
					else polynom.erase((*prev_it));
				}
				return;
			}
			else {
				if ((*it)->data.degree < m.degree)
					ans = it;
				else {
					polynom.insert(*ans, m);
					return;
				}
			}
			prev_it = it;
			++it;
		}

		if (it == polynom.end())
			polynom.insert(*ans, m);
	}

	void translator(std::string input) {
		bool first = true;
		polynomial::monomial* m = new polynomial::monomial();

		while (!input.empty()) {
			if (first) {
				if (input[0] >= '0' && input[0] <= '9') {
					std::string::size_type sz;
					double num = std::stod(input, &sz);
					input.erase(0, sz);
					m->multiplier = num;
				}
				first = false;
				continue;
			}
			if (input[0] == '+' || input[0] == '-') {     // beginning of a new monomial
				insert(*m);
				m->degree = 0;
				if (input[1] < '0' || input[1] > '9') {
					if (input[0] == '-') m->multiplier = -1;
					else m->multiplier = 1;
					input.erase(0, 1);
					continue;
				}
				std::string::size_type sz;
				double num = std::stod(input, &sz);
				input.erase(0, sz);
				m->multiplier = num;
			}
			else
				if (input[0] == 'x' || input[0] == 'y' || input[0] == 'z') {
					if (m->multiplier == 0) m->multiplier = 1;

					char tmp = input[0];
					int deg = 1;
					if (input[1] == '^') {
						input.erase(0, 2);

						std::string::size_type sz;
						deg *= std::stoi(input, &sz);
						input.erase(0, 1);
						if (deg < 0 || deg > EXP) {
							throw "degree is incorrect";
							return;
						}
					}
					else input.erase(0, 1);

					m->degree += tmp == 'x' ? deg * 100 : tmp == 'y' ? deg * 10 : deg;
				}
		}
		insert(*m);
	}

	polynomial& operator+=(const polynomial&);

	polynomial operator+(const polynomial&);

	polynomial& operator-=(const polynomial&);

	polynomial operator-(const polynomial&);

	polynomial& operator+=(const monomial&);

	polynomial& operator*=(const polynomial&);

	polynomial operator*(const polynomial&);

	polynomial& operator*=(const double&);

	polynomial operator*(const double&);

	polynomial& operator=(const polynomial&);

	bool operator==(const polynomial&) const;

	bool operator!=(const polynomial&) const;

	bool search(const monomial&);

	void clear();

	bool empty();

	size_t get_count();
};

polynomial&
polynomial::operator+=(const polynomial& p)
{
	auto it = polynom.begin(), it_p = p.polynom.begin(), prev_it = it;

	while (it != polynom.end() && it_p != p.polynom.end()) {
		if (it->data.degree == it_p->data.degree) {
			it->data.multiplier += it_p->data.multiplier;
			if (abs(it->data.multiplier) < 1e-10) {
				if (it == prev_it && it == polynom.begin())
					polynom.erase(NULL);
				else polynom.erase((*prev_it));
			}
			++it_p;
			prev_it = it;
			++it;
		}
		else {
			if (it->data.degree < it_p->data.degree) {
				prev_it = it;
				++it;
			}
			else {
				insert((*it_p)->data);
				++it_p;
			}
		}
	}

	if (it == polynom.end())
		while (it_p != p.polynom.end()) {
			insert((*it_p)->data);
			it_p = it_p->next;
		}

	return (*this);
}

polynomial
polynomial::operator+(const polynomial& p)
{
	polynomial tmp(*this);
	tmp += p;
	return tmp;
}

polynomial&
polynomial::operator*=(const double& num)
{
	auto it = polynom.begin();
	while (it != polynom.end()) {
		it->data.multiplier *= num;
		++it;
	}
	return (*this);
}

polynomial&
polynomial::operator-=(const polynomial& p)
{
	polynomial tmp_p = p;
	tmp_p *= (const double)(-1);
	(*this) += tmp_p;
	return (*this);
}

polynomial
polynomial::operator*(const double& num)
{
	polynomial tmp(*this);
	tmp *= num;
	return tmp;
}

polynomial
polynomial::operator-(const polynomial& p)
{
	polynomial tmp(*this);
	tmp -= p;
	return tmp;
}

polynomial&
polynomial::operator+=(const monomial& m)
{
	insert(m);
	return (*this);
}

bool
polynomial::operator==(const polynomial& p) const
{
	auto it = polynom.begin(), it_p = p.polynom.begin();

	while (it != polynom.end() && it_p != p.polynom.end()) {
		if (it->data != it_p->data)
			return false;
		++it; ++it_p;
	}

	if (it != polynom.end() || it_p != p.polynom.end()) return false;
	return true;
}

bool
polynomial::operator!=(const polynomial& p) const {
	return !((*this) == p);
}

polynomial&
polynomial::operator*=(const polynomial& p) {
	polynomial tmp;
	auto it1 = polynom.begin(), it2 = p.polynom.begin();
	while (it1 != polynom.end()) {
		it2 = p.polynom.begin();
		while (it2 != p.polynom.end()) {
			tmp += (*it1)->data * (*it2)->data;
			++it2;
		}
		++it1;
	}
	*this = tmp;
	return *this;
}

polynomial
polynomial::operator*(const polynomial& p) {
	polynomial tmp;
	tmp = *this;
	tmp *= p;
	return tmp;
}

bool polynomial::search(const monomial& m)
{
	auto it = polynom.begin();
	while (it != polynom.end()) {
		if ((*it)->data == m)
			return true;
		else ++it;
	}

	return false;
}

void polynomial::clear()
{
	size_t count = polynom.size;
	while (count) {
		polynom.erase(NULL);
		count--;
	}
}

polynomial& polynomial::operator=(const polynomial& p) {
	clear();
	auto it = p.polynom.begin();
	while (it != p.polynom.end()) {
		insert((*it)->data);
		++it;
	}
	return *this;
}

bool polynomial::empty() {
	return polynom.size == 0;
}

size_t polynomial::get_count() {
	return polynom.size;
}

