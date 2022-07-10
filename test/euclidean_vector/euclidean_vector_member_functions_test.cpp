// author: Wang, Liao
// date: 2022-7
// description:
//      This test file is to test the member functions of EuclideanVector class.
//      The test cases are:
//          1. test the at() function for const object
//          2. test the at() function for non-const object
//          3. test the dimensions() function for non-const object
//          4. test the dimensions() function for const object
//          5. test the exception handling for at() function for const object
//          6. test the exception handling for at() function for non-const object

#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>

TEST_CASE("Member functions for const object", "[member_functions]") {
	auto const v1 = comp6771::euclidean_vector{14.3, 26.5, -12.8, 2.1};
	auto const v2 = comp6771::euclidean_vector(0);

	SECTION("At function for const object") {
		CHECK(v1.at(0) == 14.3);
		CHECK(v1.at(1) == 26.5);
		CHECK(v1.at(2) == -12.8);
		CHECK(v1.at(3) == 2.1);
	}

	SECTION("Dimensions function") {
		CHECK(v1.dimensions() == 4);
		CHECK(v2.dimensions() == 0);
	}

	SECTION("Exception handling for at() function") {
		CHECK_THROWS_WITH(v1.at(-1), "Index -1 is not valid for this euclidean_vector object");
		CHECK_THROWS_WITH(v1.at(5), "Index 5 is not valid for this euclidean_vector object");
		CHECK_THROWS_WITH(v2.at(0), "Index 0 is not valid for this euclidean_vector object");
	}
}

TEST_CASE("Member functions for non-const object", "[member_functions]") {
	auto v1 = comp6771::euclidean_vector{14.3, 26.5, -12.8, 2.1};
	auto v2 = comp6771::euclidean_vector(0);

	SECTION("At function for non-const object") {
		v1.at(0) = -1.0;
		v1.at(1) = -2.0;
		v1.at(2) = -3.0;
		v1.at(3) = -4.0;

		CHECK(v1.at(0) == -1.0);
		CHECK(v1.at(1) == -2.0);
		CHECK(v1.at(2) == -3.0);
		CHECK(v1.at(3) == -4.0);
	}
}