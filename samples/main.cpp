#pragma once

#include <iostream>
#include <string>
#include <polynomial.h>

int main()
{
	std::cout << "\n	Hi!!! This program will allow you to perform operations on polynomials.\n"<<\
		" When entering a polynomial, please follow some rules : \n";
	std::cout << " 1) Enter a polynomial without spaces\n" << \
		" 2) Only 3 variables are allowed in the polynomial: x, y and z\n" << \
		" 3) Monomials are written in any order\n" << \
		" 4) Degree of each variable in a monomial from 0 to 9\n" << \
		" 5) After writing the polynom, press enter\n\n";
	std::cout << "Select the action you want to perform on the polynomials\n" << \
		" 1. Add two polynomials\n" << \
		" 2. Subtract two polynomials\n" << \
		" 3. Multiply two polynomials\n" << \
		" 4. Multiply a polynomial by a number\n" << \
		" 5. Find the number of monomials in a polynomial\n" << \
		" 6. Exit\n";

	int item;
	std::cin >> item;
	while (item != 6) {
		if (item == 1 || item == 2 || item == 3) {
			std::cout << " Enter two polynomials:\n";

			std::string s1, s2;
			std::cin >> s1 >> s2;
			try {
				polynomial p1(s1), p2(s2);

				if (item == 1) {
					p1 += p2;
				}
				else {
					if (item == 2) p1 -= p2;
					else p1 *= p2;
				}
				p1.print();
			}
			catch (const std::string& e) {
				std::cout << e << std::endl;
				std::cout << " Please, try again:\n";
			}
		}
		if (item == 4 || item == 5) {
			try {
				std::cout << "Enter polynomial\n";
				std::string s;
				std::cin >> s;
				polynomial p(s);

				if (item == 4) {
					std::cout << "Ented number(double)\n";
					double m;
					std::cin >> m;

					p *= m;
					p.print();
				}
				else
					std::cout << p.get_count() << '\n';

			}
			catch (const std::string& e) {
				std::cout << e << std::endl;
				std::cout << " Please, try again:\n";
			}
		}
		std::cout << "Enter the item\n";
		std::cin >> item;
	}
	return 0;
}

