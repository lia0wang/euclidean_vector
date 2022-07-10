// author: Wang, Liao
// date: 2022-7
// description:
//      This test file is to test the constructor of EuclideanVector class.
//      The test cases are:
//          1. test the default constructor
//          2. test the constructor takes the number of dimensions
//          3. test the constructor takes the number of dimensions and the initial value
//          4. test the constructor takes the start and end of an iterator
//          5. test the constructor takes an initializer list
//          6. test the copy constructor
//          7. test the move constructor

#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>

TEST_CASE("Default constructor", "[constructor]") {
	auto const v1 = comp6771::euclidean_vector();
	auto const expected_v1 = std::vector<double>{0.0};

	CHECK(v1.at(0) == 0.0);
	CHECK(v1.dimensions() == 1);
	CHECK_THAT(static_cast<std::vector<double>>(v1), Catch::Equals(expected_v1));
	CHECK_THROWS_WITH(v1.at(1), "Index 1 is not valid for this euclidean_vector object");
}

TEST_CASE("Constructor with number of dimensions", "[constructor]") {
	auto const v1 = comp6771::euclidean_vector(0);
	auto const v2 = comp6771::euclidean_vector(3);

	auto const expected_v1 = std::vector<double>{};
	auto const expected_v2 = std::vector<double>{0.0, 0.0, 0.0};

	CHECK(v2.at(0) == 0.0);
	CHECK(v2.at(1) == 0.0);
	CHECK(v2.at(2) == 0.0);

	CHECK(v1.dimensions() == 0);
	CHECK(v2.dimensions() == 3);

	CHECK_THAT(static_cast<std::vector<double>>(v1), Catch::Equals(expected_v1));
	CHECK_THAT(static_cast<std::vector<double>>(v2), Catch::Equals(expected_v2));

	CHECK_THROWS_WITH(v1.at(0), "Index 0 is not valid for this euclidean_vector object");
	CHECK_THROWS_WITH(v1.at(3), "Index 3 is not valid for this euclidean_vector object");
}

TEST_CASE("Constructor with number of dimensions and initial value", "[constructor]") {
	auto const v1 = comp6771::euclidean_vector(0, 0.0);
	auto const v2 = comp6771::euclidean_vector(3, 1.0);

	auto const expected_v1 = std::vector<double>{};
	auto const expected_v2 = std::vector<double>{1.0, 1.0, 1.0};

	CHECK(v2.at(0) == 1.0);
	CHECK(v2.at(1) == 1.0);
	CHECK(v2.at(2) == 1.0);

	CHECK(v1.dimensions() == 0);
	CHECK(v2.dimensions() == 3);

	CHECK_THAT(static_cast<std::vector<double>>(v1), Catch::Equals(expected_v1));
	CHECK_THAT(static_cast<std::vector<double>>(v2), Catch::Equals(expected_v2));

	CHECK_THROWS_WITH(v1.at(0), "Index 0 is not valid for this euclidean_vector object");
	CHECK_THROWS_WITH(v1.at(3), "Index 3 is not valid for this euclidean_vector object");
}

TEST_CASE("Constructor with start and end of an iterator", "[constructor]") {
	auto const v1 = std::vector<double>{1.0, 2.0, 3.0};
	auto const v2 = std::vector<double>{4.0, 5.0, 6.0};
	auto const v3 = std::vector<double>{};

	auto const v4 = comp6771::euclidean_vector(v1.begin(), v1.end());
	auto const v5 = comp6771::euclidean_vector(v2.begin(), v2.end());
	auto const v6 = comp6771::euclidean_vector(v3.begin(), v3.end());

	auto const expected_v4 = std::vector<double>{1.0, 2.0, 3.0};
	auto const expected_v5 = std::vector<double>{4.0, 5.0, 6.0};
	auto const expected_v6 = std::vector<double>{};

	CHECK_THAT(static_cast<std::vector<double>>(v4), Catch::Equals(expected_v4));
	CHECK_THAT(static_cast<std::vector<double>>(v5), Catch::Equals(expected_v5));
	CHECK_THAT(static_cast<std::vector<double>>(v6), Catch::Equals(expected_v6));

	CHECK_THROWS_WITH(v4.at(3), "Index 3 is not valid for this euclidean_vector object");
	CHECK_THROWS_WITH(v5.at(3), "Index 3 is not valid for this euclidean_vector object");
	CHECK_THROWS_WITH(v6.at(0), "Index 0 is not valid for this euclidean_vector object");
}

TEST_CASE("Constructor with initializer list", "[constructor]") {
	auto const v1 = comp6771::euclidean_vector({-1.0, -2.0, -3.0});
	auto const v2 = comp6771::euclidean_vector({});

	auto const expected_v1 = std::vector<double>{-1.0, -2.0, -3.0};
	auto const expected_v2 = std::vector<double>{};

	CHECK_THAT(static_cast<std::vector<double>>(v1), Catch::Equals(expected_v1));
	CHECK_THAT(static_cast<std::vector<double>>(v2), Catch::Equals(expected_v2));
}

TEST_CASE("Copy constructor", "[constructor]") {
	auto const v1 = comp6771::euclidean_vector({});
	auto const v2 = comp6771::euclidean_vector({-1.1, -2.2, -3.3});

	auto cp_v1 = v1;
	auto cp_v2 = v2;

	auto const expected_v1 = std::vector<double>{};
	auto const expected_v2 = std::vector<double>{-1.1, -2.2, -3.3};

	CHECK(cp_v1.dimensions() == static_cast<std::size_t>(expected_v1.size()));
	CHECK(cp_v2.dimensions() == static_cast<std::size_t>(expected_v2.size()));

	CHECK_THAT(static_cast<std::vector<double>>(cp_v1), Catch::Equals(expected_v1));
	CHECK_THAT(static_cast<std::vector<double>>(cp_v2), Catch::Equals(expected_v2));

	CHECK_THAT(static_cast<std::vector<double>>(v1), Catch::Equals(expected_v1));
	CHECK_THAT(static_cast<std::vector<double>>(v2), Catch::Equals(expected_v2));

	SECTION("Check Self-Assignment") {
		cp_v1 = cp_v1;
		cp_v2 = cp_v2;

		CHECK(cp_v1.dimensions() == static_cast<std::size_t>(expected_v1.size()));
		CHECK(cp_v2.dimensions() == static_cast<std::size_t>(expected_v2.size()));

		CHECK_THAT(static_cast<std::vector<double>>(cp_v1), Catch::Equals(expected_v1));
		CHECK_THAT(static_cast<std::vector<double>>(cp_v2), Catch::Equals(expected_v2));

		SECTION("Check if modified vectors are not affected") {
			cp_v1 += comp6771::euclidean_vector({});
			cp_v2 += cp_v2;

			CHECK_THAT(static_cast<std::vector<double>>(v1), Catch::Equals(expected_v1));
			CHECK_THAT(static_cast<std::vector<double>>(v2), Catch::Equals(expected_v2));
		}
	}
}

TEST_CASE("Move constructor", "[constructor]") {
	auto v = comp6771::euclidean_vector({1.0, 2.0, 3.0});
	auto const expected_v = std::vector<double>{1.0, 2.0, 3.0};
	auto const mv_v = std::move(v);

	CHECK(mv_v.dimensions() == static_cast<std::size_t>(expected_v.size()));
	CHECK_THAT(static_cast<std::vector<double>>(mv_v), Catch::Equals(expected_v));

	CHECK(v.dimensions() == 0);
	CHECK_THAT(static_cast<std::vector<double>>(v), Catch::Equals(std::vector<double>{}));
	CHECK_THROWS_WITH(v.at(0), "Index 0 is not valid for this euclidean_vector object");
}