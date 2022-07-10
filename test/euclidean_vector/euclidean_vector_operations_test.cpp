// author: Wang, Liao
// date: 2022-7
// description:
//      This test file is to test the operator functions of EuclideanVector class.
//      The test cases are:
//          1. test the copy assignment operator
//          2. test the move assignment operator
//          3. test the subscript operator
//          4. test the unary plus operator
//          5. test the unary minus operator
//          6. test the compound addition operator
//          7. test the compound subtraction operator
//          8. test the compound multiplication operator
//          9. test the compound division operator
//          10. test the vector type conversion operator
//          11. test the list type conversion operator

#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>

TEST_CASE("Copy Assignment", "[operation]") {
	auto const v1 = comp6771::euclidean_vector{14.3, 26.5, -12.8, 2.1};
	auto v2 = comp6771::euclidean_vector(0);
	auto const expected = std::vector<double>{14.3, 26.5, -12.8, 2.1};

	v2 = v1;

	SECTION("Copy assignment operator") {
		CHECK_THAT(static_cast<std::vector<double>>(v2), Catch::Equals(expected));
	}

	SECTION("Self assignment") {
		v2 = v2;
		CHECK_THAT(static_cast<std::vector<double>>(v2), Catch::Equals(expected));
	}
}

TEST_CASE("Move Assignment", "[operation]") {
	auto v1 = comp6771::euclidean_vector{14.3, 26.5, -12.8, 2.1};
	auto v2 = comp6771::euclidean_vector(0);
	auto const expected = std::vector<double>{14.3, 26.5, -12.8, 2.1};

	v2 = std::move(v1);

	SECTION("Move assignment operator") {
		CHECK_THAT(static_cast<std::vector<double>>(v2), Catch::Equals(expected));
	}

	SECTION("Check the moved object") {
		CHECK(v1.dimensions() == 0);
		CHECK_THROWS_WITH(v1.at(0), "Index 0 is not valid for this euclidean_vector object");
	}
}

TEST_CASE("Subscript operator - const object", "[operation]") {
	auto const v1 = comp6771::euclidean_vector{14.3, 26.5, -12.8, 2.1};
	auto const v2 = comp6771::euclidean_vector(0);

	CHECK(v1[0] == 14.3);
	CHECK(v1[1] == 26.5);
	CHECK(v1[2] == -12.8);
	CHECK(v1[3] == 2.1);
}

TEST_CASE("Subscript operator - non-const object", "[operation]") {
	auto v1 = comp6771::euclidean_vector{14.3, 26.5, -12.8, 2.1};
	auto v2 = comp6771::euclidean_vector(0);

	CHECK(v1[0] == 14.3);
	CHECK(v1[1] == 26.5);
	CHECK(v1[2] == -12.8);
	CHECK(v1[3] == 2.1);

	v1[0] = 99;
	v1[1] = 99;
	v1[2] = 99;
	v1[3] = 99;

	CHECK(v1[0] == 99);
	CHECK(v1[1] == 99);
	CHECK(v1[2] == 99);
	CHECK(v1[3] == 99);
}

TEST_CASE("Unary plus operator", "[operation]") {
	auto v1 = comp6771::euclidean_vector{14.3, 26.5, -12.8, 2.1};
	auto v2 = comp6771::euclidean_vector(0);
	auto const expected = std::vector<double>{14.3, 26.5, -12.8, 2.1};

	auto v3 = +v2;
	v2 = +v1;

	SECTION("Unary plus operator") {
		CHECK_THAT(static_cast<std::vector<double>>(v2), Catch::Equals(expected));
		CHECK(v3.dimensions() == 0);
	}
}

TEST_CASE("Unary minus operator", "[operation]") {
	auto v1 = comp6771::euclidean_vector{14.3, 26.5, -12.8, 2.1};
	auto v2 = comp6771::euclidean_vector(0);
	auto const expected = std::vector<double>{-14.3, -26.5, 12.8, -2.1};

	auto v3 = -v2;
	v2 = -v1;

	SECTION("Unary minus operator") {
		CHECK_THAT(static_cast<std::vector<double>>(v2), Catch::Equals(expected));
		CHECK(v3.dimensions() == 0);
	}
}

TEST_CASE("Compound operators", "[operation]") {
	auto v1 = comp6771::euclidean_vector{14.3, 26.5, -12.8, 2.1};
	auto v2 = comp6771::euclidean_vector{17.3, -25.5, 22.8, -3.1};
	auto v3 = comp6771::euclidean_vector(0);

	SECTION("Addition") {
		v1 += v1;
		CHECK_THAT(static_cast<std::vector<double>>(v1),
		           Catch::Equals(std::vector<double>{28.6, 53.0, -25.6, 4.2}));

		v1 += v2;
		CHECK_THAT(static_cast<std::vector<double>>(v1),
		           Catch::Approx(std::vector<double>{45.9, 27.5, -2.8, 1.1}));

		v3 += v3;
		CHECK(v3.dimensions() == 0);
	}

	SECTION("Subtraction") {
		v1 -= v1;
		CHECK_THAT(static_cast<std::vector<double>>(v1),
		           Catch::Equals(std::vector<double>{0, 0, 0, 0}));

		v1 -= v2;
		CHECK_THAT(static_cast<std::vector<double>>(v1),
		           Catch::Equals(std::vector<double>{-17.3, 25.5, -22.8, 3.1}));

		v3 -= v3;
		CHECK(v3.dimensions() == 0);
	}

	SECTION("Multiplication") {
		v1 *= 1.0;
		CHECK_THAT(static_cast<std::vector<double>>(v1),
		           Catch::Equals(std::vector<double>{14.3, 26.5, -12.8, 2.1}));

		v1 *= 2.0;
		CHECK_THAT(static_cast<std::vector<double>>(v1),
		           Catch::Approx(std::vector<double>{28.6, 53.0, -25.6, 4.2}));

		v1 *= -1.0;
		CHECK_THAT(static_cast<std::vector<double>>(v1),
		           Catch::Approx(std::vector<double>{-28.6, -53.0, 25.6, -4.2}));

		v1 *= 0.0;
		CHECK_THAT(static_cast<std::vector<double>>(v1),
		           Catch::Equals(std::vector<double>{0, 0, 0, 0}));

		v3 *= 2.0;
		CHECK(v3.dimensions() == 0);
	}

	SECTION("Division") {
		v1 /= 1.0;
		CHECK_THAT(static_cast<std::vector<double>>(v1),
		           Catch::Equals(std::vector<double>{14.3, 26.5, -12.8, 2.1}));

		v1 /= 2.0;
		CHECK_THAT(static_cast<std::vector<double>>(v1),
		           Catch::Approx(std::vector<double>{7.15, 13.25, -6.4, 1.05}));

		v1 /= -1.0;
		CHECK_THAT(static_cast<std::vector<double>>(v1),
		           Catch::Approx(std::vector<double>{-7.15, -13.25, 6.4, -1.05}));

		v3 /= 2.0;
		CHECK(v3.dimensions() == 0);
	}

	SECTION("Exception") {
		CHECK_THROWS_WITH(v1 += v3, Catch::Contains("Dimensions of LHS(4) and RHS(0) do not match"));
		CHECK_THROWS_WITH(v1 -= v3, Catch::Contains("Dimensions of LHS(4) and RHS(0) do not match"));
		CHECK_THROWS_WITH(v1 /= 0.0, Catch::Contains("Invalid vector division by 0"));
	}
}

TEST_CASE("Vector type conversion", "[operation]") {
	auto const v1 = comp6771::euclidean_vector{14.3, 26.5, -12.8, 2.1};
	auto const v2 = comp6771::euclidean_vector(0);

	auto const expected_v1 = std::vector<double>{14.3, 26.5, -12.8, 2.1};
	auto const expected_v2 = std::vector<double>();

	auto const v3 = static_cast<std::vector<double>>(v1);
	auto const v4 = static_cast<std::vector<double>>(v2);
	CHECK_THAT(v3, Catch::Equals(expected_v1));
	CHECK_THAT(v4, Catch::Equals(expected_v2));
}

TEST_CASE("List type conversion", "[operation]") {
	auto const v1 = comp6771::euclidean_vector{14.3, 26.5, -12.8, 2.1};
	auto const v2 = comp6771::euclidean_vector(0);

	auto const expected_v1 = std::list<double>{14.3, 26.5, -12.8, 2.1};
	auto const expected_v2 = std::list<double>();

	auto const v3 = static_cast<std::list<double>>(v1);
	auto const v4 = static_cast<std::list<double>>(v2);
	CHECK(v3 == expected_v1);
	CHECK(v4 == expected_v2);
}