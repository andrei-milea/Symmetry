
#define BOOST_TEST_MODULE "test_resultsdb"
#include "boost/test/included/unit_test.hpp"

#include "../engine/lrumap.h"
#include "../engine/results_bucket.h"
#include "../engine/results_db.h"
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>

using namespace boost::unit_test;
using namespace boost::filesystem;
using namespace boost::random;
using namespace resultsDB;
using namespace engine;
using namespace std;



struct gfixture
{
	gfixture()
	{
		//create db folder
		path dir(DB_PATH);
		remove_all(dir);

		if(true != create_directory(dir))
			BOOST_ASSERT(false);
		fstream file;
		file.open(string(DB_PATH) + DBIDX_FILENAME, fstream::out);
		BOOST_ASSERT(file.is_open());
	}

	~gfixture()
	{
		//delete db folder and contents
		path dir(DB_PATH);
		if(remove_all(dir) <= 0)
			BOOST_ASSERT(false);
	}
};


BOOST_AUTO_TEST_CASE(test_lrumap)
{
	cLruHashMap<int, int> inthash(500);
	for(int i = 0; i < 1000; i++)
	{
		int val = 2*i;
		inthash.insert(i, val);
	}
	
	for(int i = 501; i < 1000; i++)
	{
		const int val = inthash.get(i);
		BOOST_CHECK(val == 2 * i);
	}

	BOOST_CHECK(inthash.find(1) == inthash.end());
	BOOST_CHECK(inthash.find(995) != inthash.end());
}

BOOST_FIXTURE_TEST_CASE(test_results_bucket, gfixture)
{
	//basic test
	{
		cResultsBucket results_bucket(0, 3, true);
		string param1 = "param1";
		string param2 = "param2";
		string param3 = "param3";
		string result1 = "result1";
		string result2 = "result2";
		string result3 = "result3";

		unique_ptr<cResultsBucket> new_results_bucket = results_bucket.SaveResult(1, param1, result1);
		BOOST_CHECK(new_results_bucket == nullptr);
		new_results_bucket = results_bucket.SaveResult(2, param2, result2);
		BOOST_CHECK(new_results_bucket == nullptr);
		new_results_bucket = results_bucket.SaveResult(3, param3, result3);
		BOOST_CHECK(new_results_bucket == nullptr);

		string result;
		bool ok = results_bucket.GetResult(1, param1, result);
		BOOST_CHECK(ok);
		BOOST_CHECK(result == result1);

		ok = results_bucket.GetResult(2, param2, result);
		BOOST_CHECK(ok);
		BOOST_CHECK(result == result2);

		ok = results_bucket.GetResult(3, param3, result);
		BOOST_CHECK(ok);
		BOOST_CHECK(result == result3);

		BOOST_CHECK(results_bucket.GetIndexBitsSz() == 3);
		BOOST_CHECK(results_bucket.GetCode() == 0);
	}

	//test persistance
	{
		cResultsBucket results_bucket(0, 3);
		string param1 = "param1";
		string param2 = "param2";
		string param3 = "param3";
		string result1 = "result1";
		string result2 = "result2";
		string result3 = "result3";

		string result;
		bool ok = results_bucket.GetResult(1, param1, result);
		BOOST_CHECK(ok);
		BOOST_CHECK(result == result1);

		ok = results_bucket.GetResult(2, param2, result);
		BOOST_CHECK(ok);
		BOOST_CHECK(result == result2);

		ok = results_bucket.GetResult(3, param3, result);
		BOOST_CHECK(ok);
		BOOST_CHECK(result == result3);

		BOOST_CHECK(results_bucket.GetIndexBitsSz() == 3);
		BOOST_CHECK(results_bucket.GetCode() == 0);
	
		//check invalid param
		string invalid_param = "dsadaldnsaaA";
		ok = results_bucket.GetResult(3, invalid_param, result);
		BOOST_CHECK(!ok);
		BOOST_CHECK(result == result3);
	}

	//test split
	{
		cResultsBucket results_bucket(0, 3);
		string param1;
		string result1;
		string result;
		unique_ptr<cResultsBucket> new_results_bucket = nullptr;
		bool ok = false;
		size_t idx = 0;
		for(idx = 4; idx < MAX_ENTRIES; idx++)
		{
			stringstream ss;
			ss<<idx;
			param1 = string("param") + ss.str();
			result1 = string("result") + ss.str();
			new_results_bucket = results_bucket.SaveResult(idx, param1, result1);
			ok = results_bucket.GetResult(idx, param1, result);

			BOOST_CHECK(new_results_bucket == nullptr);
			BOOST_CHECK(ok);
			BOOST_CHECK(result == result1);
			BOOST_CHECK(results_bucket.GetIndexBitsSz() == 3);
			BOOST_CHECK(results_bucket.GetCode() == 0);
		}

		param1 = "paramf";
		result1 = "resultf";
		new_results_bucket = results_bucket.SaveResult(idx + 1, param1, result1);
		BOOST_CHECK(new_results_bucket != nullptr);
		BOOST_CHECK(results_bucket.GetIndexBitsSz() == 4);
		BOOST_CHECK(new_results_bucket->GetIndexBitsSz() == 4);
	}
} 

string generate_random_text()
{
	boost::random::random_device rnd_dev;
	boost::random::uniform_int_distribution<> uniform_dist_size(10, 200);
	string chars("ZXCVBNMASDFGHJKLQWERTYUIOP:qwertyuiopasdfghjklzxcvbnm,.!@#$%^&*()1234567890-= ");
	string text;
	std::size_t size = uniform_dist_size(rnd_dev);
	for(std::size_t idx = 5; idx < size; idx++)
	{
		boost::random::uniform_int_distribution<> uniform_dist(0, chars.size() - 1);
		text += chars[uniform_dist(rnd_dev)];
	}
	return text;
}

//BOOST_AUTO_TEST_CASE(test_results_db)
BOOST_FIXTURE_TEST_CASE(test_results_db, gfixture)
{
	cResultsDB* results_db = cResultsDB::GetInstance();

	for(size_t idx = 10; idx < (15 * MAX_ENTRIES); idx++)
	{
		string param = generate_random_text();
		string result = generate_random_text();
		string getresult;
		results_db->SaveResult(GET_ELEMENTS, param, result);
		bool ok = results_db->GetResult(GET_ELEMENTS, param, getresult);
		BOOST_CHECK(ok);
		if(getresult != result)
			ok = false;
		BOOST_CHECK(getresult == result);
		BOOST_CHECK(ok);
	}
	results_db->SaveDB();
}



