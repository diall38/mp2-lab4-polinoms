#pragma once
#include "polynomial.h"
#include <gtest/gtest.h>

TEST(list, can_create_list) {
	ASSERT_NO_THROW(list<int> l);
}

TEST(list, can_copy_list) {
	list<int> l1;
	ASSERT_NO_THROW(list<int> l2(l1));
}

TEST(list, can_get_size) {
	list<int> l1;
	int num = 3;
	l1.insert(0, num);
	ASSERT_NO_THROW(l1.get_size());
	EXPECT_EQ(l1.get_size(), 1);
}

TEST(list, correct_check_of_empty) {
	list<int> l1, l2;
	l2.insert(0, 2);
	EXPECT_EQ(l1.empty(), true);
	EXPECT_EQ(l2.empty(), false);
}

TEST(list, can_insert_first) {
	list<int> l1;
	int num = 5;
	ASSERT_NO_THROW(l1.insert(0, num));
}

TEST(list, can_insert) {
	list<int> l1;
	int num1 = 5, num2 = 6, num3 = 7;
	l1.insert(0, num1);
	l1.insert(0, num2);
	list<int>::iterator it(l1.get_first());
	++it;
	ASSERT_NO_THROW(l1.insert(*it, num3));
}

TEST(list, can_delete_first) {
	list<int> l1;
	l1.insert(0, 2);
	l1.insert(0, 3);
	ASSERT_NO_THROW(l1.erase(0));
	EXPECT_EQ(l1.get_size(), 1);
}

TEST(list, can_delete_node) {
	list<int> l1;
	list<int>::iterator it = l1.begin();
	int num = 30;
	l1.insert(0, 2);
	l1.insert(0, 30);
	ASSERT_NO_THROW(l1.erase(*it));
	l1.print();
	EXPECT_EQ(l1.get_size(), 1);
}

TEST(list, can_search_node) {
	list<int> l1;
	int num1 = 1, num2 = 2, num3 = 3;
	l1.insert(0, num1);
	l1.insert(0, num2);
	l1.insert(0, num3);
	list<int>::iterator iter1(l1.get_first());
	++iter1;
	EXPECT_EQ(iter1, l1.search(num2));
}

TEST(iterator, can_create) {
	ASSERT_NO_THROW(list<int>::iterator it);
}

TEST(iterator, can_copy) {
	list<int>::iterator it2;
	ASSERT_NO_THROW(list<int>::iterator it1(it2));
}

TEST(iterator, operator_plus_plus_is_correct)
{
	list<int> l1;
	l1.insert(0, 1);
	l1.insert(0, 2);
	l1.insert(0, 3);
	l1.print();
	list<int>::iterator iter1(l1.get_first());
	++iter1;
	EXPECT_EQ(iter1->data, 2);
	list<int>::iterator iter2(iter1++);
	EXPECT_EQ(iter2->data, 2);
	EXPECT_EQ(iter1->data, 1);
}
TEST(iterator, operator_equal_is_correct)
{
	list<int> l1;
	l1.insert(0, 1);
	l1.insert(0, 2);
	l1.insert(0, 3);
	list<int>::iterator iter1(l1.get_first());
	++iter1;
	list<int>::iterator iter2(iter1);
	EXPECT_EQ(iter2 == iter1, true);
}
TEST(iterator, operator_not_equal_is_correct)
{
	list<int> l1;
	l1.insert(0, 1);
	l1.insert(0, 2);
	l1.insert(0, 3);
	list<int>::iterator iter1(l1.get_first());
	++iter1;
	list<int>::iterator iter2(iter1++);
	EXPECT_EQ(iter2 != iter1, true);
}

TEST(polynomial, can_create_polynomial_by_constructor_with_parametrs)
{
	ASSERT_NO_THROW(polynomial p("19x+3yz"));
	ASSERT_NO_THROW(polynomial p1("x-3.6"));
	ASSERT_NO_THROW(polynomial p2("-7.1y^9-3z^2x^6+y"));
}

TEST(polynomial, can_create_polynomial_by_constructor_of_copy)
{
	polynomial a("43x^2y-35z+17.8x");
	ASSERT_NO_THROW(polynomial b(a));
}

TEST(polynomial, throw_then_negative_degree)
{
	ASSERT_ANY_THROW(polynomial a("11y^-4+5z"));
}

TEST(polynomial, throw_then_too_large_degree)
{
	ASSERT_ANY_THROW(polynomial a("xyz^2022+5.09"));
}

TEST(polynomial, operator_of_equal_is_correctly)
{
	polynomial a("4.9x^2y-35z+3y");
	polynomial b("12x+5.8y^3-1");
	ASSERT_NO_THROW(b = a);
	EXPECT_EQ(b, a);
}

TEST(polynomial, operator_of_doudle_equal_is_correctly)	
{
	polynomial a("37x^2y-10.17z+0");
	polynomial b("-10.17z+5+37x^2y-7+2");
	EXPECT_EQ(true, a==b);
}


TEST(polynomial, operator_of_not_equal_is_correct)
{
	polynomial a("3x^2y-35z+4yz");
	polynomial b("-35z+4zx+4yz");
	EXPECT_EQ(true, a != b);
}

TEST(polynomial, can_erase_monomial_with_zero_coefficient)
{
	polynomial a("20.22xyz-7y+3-38z^4"), b("-3+7y-20.21xyz");
	EXPECT_EQ(4, a.get_count());
	a += b;	
	//a.print();
	EXPECT_EQ(2, a.get_count());
}

TEST(polynomial, can_to_group_monomials_with_the_same_coefficients)
{
	polynomial a("15xyz-23y+4"), b("-12zyx+8");
	EXPECT_EQ(3, a.get_count());
	a += b;	
	EXPECT_EQ(3, a.get_count());
}

TEST(polynomial, can_addeq_correctly)
{
	polynomial a("32x^4yz^5"), b("-x^7+12y-7.85"), c("-x^7+32x^4yz^5+12y-7.85");
	a += b;
	EXPECT_EQ(c, a);
}

TEST(polynomial, can_add_correctly)
{
	polynomial a("32x^4yz^5"), b("x^7+12y"), c("x^7+32x^4yz^5+12y"), d;
	d = a + b;
	EXPECT_EQ(c, d);
}

TEST(polynomial, can_subeq_correctly)
{
	polynomial a("3x^4yz^5"), b("-x^7+12y-2.1"), c("x^7+3x^4yz^5-12y+2.1");
	a -= b;
	EXPECT_EQ(c, a);
}

TEST(polynomial, can_sub_correctly)
{
	polynomial a("32.45x^4yz^5"), b("x^7+12y"), c("-x^7+32.45x^4yz^5-12y"), d;
	d = a - b;
	EXPECT_EQ(c, d);
}

TEST(polynomial, can_mult_eq_polynoms_correctly)
{
	polynomial a("x^2+y"), b("7x+z"), c("7x^3+x^2z+7xy+yz");
	a *= b;
	EXPECT_EQ(c, a);
}

TEST(polynomial, can_Mult_Pol_and_Pol_correctly)
{
	polynomial a("x^2+y"), b("7x+z"), c("7x^3+x^2z+7xy+yz"), d;
	d = a * b;
	EXPECT_EQ(c, d);
}

TEST(polynomial, throw_when_too_large_degree_after_mult)
{
	polynomial a("xy^9"), b("-2x^9y^2"), c;
	ASSERT_ANY_THROW(c = a * b);
}

TEST(polynomial, can_mult_polynom_and_scalar_correctly)
{
	polynomial a("0.6xy^7+z+21.001"), b("4.2xy^7+7z+147.007"), c;
	c = a * 7;
	EXPECT_EQ(b, c);
}

TEST(polynomial, can_add_when_input_polynom_is_empty)
{
	polynomial a("x^9y^9z^2+y^6z-4y"), b, c;
	ASSERT_NO_THROW(c = a+b);
	EXPECT_EQ(a, c);
}

TEST(polynomial, can_mult_when_input_polynom_is_empty)
{
	polynomial a("z^6y^8+y^5z-1"), b;
	ASSERT_NO_THROW(a *= b);
	EXPECT_EQ(true, a.empty());
}

TEST(polynomial, function_empty_is_correct)
{
	polynomial a("3x+5"), b("-5-3x^1"), c;
	EXPECT_EQ(false, a.empty());
	a += b;
	EXPECT_EQ(true, a.empty());
	EXPECT_EQ(true, c.empty());
}

TEST(polynomial, function_clear_is_correct)
{
	polynomial a("5+x^5y^5z^5-4y+2z^2");
	EXPECT_EQ(false, a.empty());
	a.clear();
	EXPECT_EQ(true, a.empty());
}

TEST(polynomial, can_clear_empty_polynom)
{
	polynomial a;
	ASSERT_NO_THROW(a.clear());
}

TEST(polynomial, check_input_correctly) {
	ASSERT_ANY_THROW(polynomial a("^4x-2"));
	ASSERT_NO_THROW(polynomial a1("4x-2"));
	ASSERT_ANY_THROW(polynomial b("2z+5x-"));
	ASSERT_NO_THROW(polynomial b1("2z+5x"));
	ASSERT_ANY_THROW(polynomial c("5+x^5y^5z^5-+2z^2"));
	ASSERT_NO_THROW(polynomial c1("5+x^5y^5z^5-2z^2"));
	ASSERT_ANY_THROW(polynomial d("5+^-4y+2z^2"));
	ASSERT_NO_THROW(polynomial d1("5-4y+2z^2"));
	ASSERT_ANY_THROW(polynomial e("5-.765x"));
	ASSERT_NO_THROW(polynomial e1("5-0.765x"));
	ASSERT_ANY_THROW(polynomial f("-cx^2"));
	ASSERT_NO_THROW(polynomial f1("-x^2"));
}
