// author: Wang, Liao
// date: 2022-7
// description:
//      This test file is to test the friend functions of EuclideanVector class.
//      The test cases are:
//          1. test the friend function of operator==
//          2. test the friend function of operator!=
//          3. test the friend function of operator+
//          4. test the friend function of operator-
//          5. test the friend function of operator*
//          6. test the friend function of operator/
//          7. test the friend function of operator<<

#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>

TEST_CASE("Equal", "[friend_operation]") {
	auto const v1 = comp6771::euclidean_vector{14.3, 26.5, -12.8, 2.1};
	auto const v2 = comp6771::euclidean_vector{14.3, 26.5, -12.8, 2.1};
	auto const v3 = comp6771::euclidean_vector(4);
	auto const v4 = comp6771::euclidean_vector(3);
	auto const v5 = comp6771::euclidean_vector(0);

	SECTION("Check equal to itself") {
		CHECK(v1 == v1);
		CHECK(v5 == v5);
	}

	SECTION("Check same dimension") {
		CHECK_FALSE(v1 == v3);
	}

	SECTION("Check different dimension") {
		CHECK_FALSE(v1 == v4);
	}

	SECTION("Check same dimension and magnitude") {
		CHECK(v1 == v2);
	}
}

TEST_CASE("Not Equal", "[friend_operation]") {
	auto const v1 = comp6771::euclidean_vector{14.3, 26.5, -12.8, 2.1};
	auto const v2 = comp6771::euclidean_vector{14.3, 26.5, -12.8, 2.1};
	auto const v3 = comp6771::euclidean_vector(4);
	auto const v4 = comp6771::euclidean_vector(3);
	auto const v5 = comp6771::euclidean_vector(0);

	SECTION("Check not equal to itself") {
		CHECK_FALSE(v1 != v1);
		CHECK_FALSE(v5 != v5);
	}

	SECTION("Check different dimension") {
		CHECK(v1 != v3);
	}

	SECTION("Check same dimension") {
		CHECK_FALSE(v1 != v2);
	}

	SECTION("Check same dimension and magnitude") {
		CHECK_FALSE(v1 != v2);
	}
}

TEST_CASE("Addition", "[friend_operation]") {
	auto const v1 = comp6771::euclidean_vector{14.3, 26.5, -12.8, 2.1};
	auto const v2 = comp6771::euclidean_vector{-1, -1, -1, -1};
	auto const v3 = comp6771::euclidean_vector(4);
	auto const v4 = comp6771::euclidean_vector(0);

	SECTION("Check addition of two vectors") {
		CHECK(v1 + v2 == comp6771::euclidean_vector{13.3, 25.5, -13.8, 1.1});
		CHECK(v3 + v3 == comp6771::euclidean_vector(4));
		CHECK(v4 + v4 == comp6771::euclidean_vector(0));
		CHECK(v1 + v1 == comp6771::euclidean_vector{28.6, 53, -25.6, 4.2});
	}

	SECTION("Check addition with different dimension") {
		CHECK_THROWS_WITH(v3 + v4, "Dimensions of LHS(4) and RHS(0) do not match");
		CHECK_NOTHROW(v1 + v2);
	}
}

TEST_CASE("Subtraction", "[friend_operation]") {
	auto const v1 = comp6771::euclidean_vector{14.3, 26.5, -12.8, 2.1};
	auto const v2 = comp6771::euclidean_vector{-1, -1, -1, -1};
	auto const v3 = comp6771::euclidean_vector(4);
	auto const v4 = comp6771::euclidean_vector(0);

	SECTION("Check subtraction of two vectors") {
		CHECK(v1 - v2 == comp6771::euclidean_vector{15.3, 27.5, -11.8, 3.1});
		CHECK(v3 - v3 == comp6771::euclidean_vector(4));
		CHECK(v4 - v4 == comp6771::euclidean_vector(0));
		CHECK(v1 - v1 == comp6771::euclidean_vector{0, 0, 0, 0});
	}

	SECTION("Check subtraction with different dimension") {
		CHECK_THROWS_WITH(v3 - v4, "Dimensions of LHS(4) and RHS(0) do not match");
		CHECK_NOTHROW(v1 - v2);
	}
}

TEST_CASE("Multiplication", "[friend_operation]") {
	auto const v1 = comp6771::euclidean_vector{14.3, 26.5, -12.8, 2.1};
	auto const v2 = comp6771::euclidean_vector(4);
	auto const v3 = comp6771::euclidean_vector(0);

	SECTION("Check multiplication of two vectors") {
		CHECK(v1 * 2.0 == comp6771::euclidean_vector{28.6, 53, -25.6, 4.2});
		CHECK(v1 * 0.0 == comp6771::euclidean_vector{0, 0, 0, 0});
		CHECK(v1 * -1.0 == comp6771::euclidean_vector{-14.3, -26.5, 12.8, -2.1});
		CHECK(v2 * 0.0 == comp6771::euclidean_vector(4));
		CHECK(v2 * 1.0 == comp6771::euclidean_vector(4));
		CHECK(v3 * -2.0 == comp6771::euclidean_vector(0));
	}
}

TEST_CASE("Division", "[friend_operation]") {
	auto const v1 = comp6771::euclidean_vector{14.3, 26.5, -12.8, 2.1};
	auto const v2 = comp6771::euclidean_vector(4);
	auto const v3 = comp6771::euclidean_vector(0);

	SECTION("Check division of two vectors") {
		CHECK(v1 / 2.0 == comp6771::euclidean_vector{7.15, 13.25, -6.4, 1.05});
		CHECK(v1 / -1.0 == comp6771::euclidean_vector{-14.3, -26.5, 12.8, -2.1});
		CHECK(v2 / 1.0 == comp6771::euclidean_vector(4));
		CHECK(v3 / -2.0 == comp6771::euclidean_vector(0));
	}

	SECTION("Check division with different dimension") {
		CHECK_THROWS_WITH(v1 / 0.0, "Invalid vector division by 0");
		CHECK_NOTHROW(v1 / 2.0);
		CHECK_THROWS_WITH(v2 / 0.0, "Invalid vector division by 0");
		CHECK_NOTHROW(v3 / 2.0);
	}
}

TEST_CASE("Output Stream", "[friend_operation]") {
	auto const v1 = comp6771::euclidean_vector{14.3, 26.5, -12.8, 2.1};
	auto const v2 = comp6771::euclidean_vector(4);
	auto const v3 = comp6771::euclidean_vector(0);

	auto ss = std::stringstream{};

	ss << v1;
	CHECK(ss.str() == "[14.3 26.5 -12.8 2.1]");
	ss.str(std::string{});

	ss << v2;
	CHECK(ss.str() == "[0 0 0 0]");
	ss.str(std::string{});

	ss << v3;
	CHECK(ss.str() == "[]");
	ss.str(std::string{});
}