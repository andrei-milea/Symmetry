#include "../lib/std_ex.h"


#include <vector>
#include <array>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

#define BOOST_TEST_MODULE "test_stdex"
#include "boost/test/included/unit_test.hpp"

using namespace boost::unit_test;

boost::mt19937 gen;

int get_random()
{
	boost::uniform_int<> dist(1, 999);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > rnd(gen, dist);
	return rnd();
};

BOOST_AUTO_TEST_CASE(test_set_inclusion)
{
	int index = 0;
	std::vector<int> set1(100);
	std::vector<int> set2(200);

	for(index = 0; index < 100; index++)
	{
		int x = get_random();
		set1[index]	= x;
		set2[index] = x;
	}
	while(index < 200)
	{
		set2[index] = get_random();
		index++;
	}
	BOOST_CHECK(std_ex::set_inclusion(set1, set2));
	BOOST_CHECK(!std_ex::set_inclusion(set2, set1));
};

BOOST_AUTO_TEST_CASE(test_set_equality)
{
	std::vector<int> set1(999);
	std::vector<int> set2(999);

	for(int index = 0; index < 999; index++)
	{
		int x = get_random();
		set1[index]	= x;
		set2[index] = x;
	}
	BOOST_CHECK(std_ex::set_equality(set1, set2));
	BOOST_CHECK(std_ex::set_equality(set2, set1));

	for(int index = 0; index < 999; index++)
	{
		set1[index]	= get_random();
		set2[index] = get_random();
	}
	BOOST_CHECK(!std_ex::set_equality(set1, set2));
	BOOST_CHECK(!std_ex::set_equality(set2, set1));
};


BOOST_AUTO_TEST_CASE(test_set_difference)
{
	std::vector<int> set1(999);
	std::vector<int> set2(999);
	std::vector<int> set3;

	for(int index = 0; index < 999; index++)
	{
		int x = get_random();
		set1[index]	= x;
		set2[index] = x;
	}
	std_ex::set_difference(set1, set2);
	BOOST_CHECK(set1.empty());
	set2.clear();

	set1.push_back(1);
	set1.push_back(2);
	set1.push_back(9);
	set1.push_back(7);

	set2.push_back(9);
	set2.push_back(1);

	set3.push_back(2);
	set3.push_back(7);
	std_ex::set_difference(set1, set2);

	BOOST_CHECK(std_ex::set_equality(set3, set1));
};


BOOST_AUTO_TEST_CASE(test_set_remove)
{
	std::vector<int> set1(9);
	std::vector<int> set2(9);
	set1.push_back(3);
	set2.push_back(3);

	set1.push_back(3);
	set2.push_back(3);

	set1.push_back(4);
	set1.push_back(4);

	set1.push_back(5);
	set2.push_back(5);

	set1.push_back(6);

	set1.push_back(5);
	set2.push_back(5);

	set1.push_back(7);
	set2.push_back(7);

	set1.push_back(6);

	std_ex::set_remove(set1, 6);
	std_ex::set_remove(set1, 4);

	BOOST_CHECK(std_ex::set_equality(set1, set2));

};


