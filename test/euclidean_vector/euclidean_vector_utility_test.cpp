// author: Wang, Liao
// date: 2022-7
// description:
//      This test file is to test the utility functions of EuclideanVector class.
//      The test cases are:
//         1. test euclidean_norm() function
//         2. test unit() function
//         3. test dot() function

#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>

TEST_CASE("Euclidean Norm", "[utility_functions]") {
	auto const v1 = comp6771::euclidean_vector{14.3, 26.5, -12.8, 2.1};
	auto const v2 = comp6771::euclidean_vector(0);
	auto const v3 = comp6771::euclidean_vector{14.3};

	SECTION("Check euclidean norm computation") {
		CHECK(comp6771::euclidean_norm(v1)
		      == Approx(std::sqrt(14.3 * 14.3 + 26.5 * 26.5 + -12.8 * -12.8 + 2.1 * 2.1)));
		CHECK(comp6771::euclidean_norm(v2) == 0.0);
		CHECK(comp6771::euclidean_norm(v3) == 14.3);
	}

	auto v4 = comp6771::euclidean_vector{14.3, 26.5, -12.8, 2.1};

	SECTION("Check cached euclidean norm") {
		CHECK(comp6771::euclidean_norm(v4)
		      == Approx(std::sqrt(14.3 * 14.3 + 26.5 * 26.5 + -12.8 * -12.8 + 2.1 * 2.1)));

		v4[0] = 17.3;
		CHECK(comp6771::euclidean_norm(v4)
		      == Approx(std::sqrt(17.3 * 17.3 + 26.5 * 26.5 + -12.8 * -12.8 + 2.1 * 2.1)));

		v4 += v1;
		CHECK(comp6771::euclidean_norm(v4)
		      == Approx(std::sqrt(31.6 * 31.6 + 53 * 53 + -25.6 * -25.6 + 4.2 * 4.2)));

		v4 -= v1;
		CHECK(comp6771::euclidean_norm(v4)
		      == Approx(std::sqrt(17.3 * 17.3 + 26.5 * 26.5 + -12.8 * -12.8 + 2.1 * 2.1)));

		v4 *= 2.0;
		CHECK(comp6771::euclidean_norm(v4)
		      == Approx(std::sqrt(34.6 * 34.6 + 53 * 53 + -25.6 * -25.6 + 4.2 * 4.2)));

		v4 /= 2.0;
		CHECK(comp6771::euclidean_norm(v4)
		      == Approx(std::sqrt(17.3 * 17.3 + 26.5 * 26.5 + -12.8 * -12.8 + 2.1 * 2.1)));
	}
}

TEST_CASE("Unit Vector", "[utility_functions]") {
	auto const v1 = comp6771::euclidean_vector{14.3, 26.5, -12.8, 2.1};
	auto const v2 = comp6771::euclidean_vector{1, 2, 3, 4};

	SECTION("Check unit vector computation") {
		auto const u1 = comp6771::unit(v1);
		auto const u2 = comp6771::unit(v2);

		CHECK(u1.dimensions() == 4);
		CHECK(u2.dimensions() == 4);

		CHECK(u1[0] == Approx(14.3 / comp6771::euclidean_norm(v1)));
		CHECK(u1[1] == Approx(26.5 / comp6771::euclidean_norm(v1)));
		CHECK(u1[2] == Approx(-12.8 / comp6771::euclidean_norm(v1)));
		CHECK(u1[3] == Approx(2.1 / comp6771::euclidean_norm(v1)));

		CHECK(u2[0] == Approx(1.0 / comp6771::euclidean_norm(v2)));
		CHECK(u2[1] == Approx(2.0 / comp6771::euclidean_norm(v2)));
		CHECK(u2[2] == Approx(3.0 / comp6771::euclidean_norm(v2)));
		CHECK(u2[3] == Approx(4.0 / comp6771::euclidean_norm(v2)));

		CHECK(comp6771::euclidean_norm(u1) == Approx(1.0));
		CHECK(comp6771::euclidean_norm(u2) == Approx(1.0));
	}

	auto const v3 = comp6771::euclidean_vector(0);
	auto const v4 = comp6771::euclidean_vector(4);

	SECTION("Exception handling") {
		CHECK_THROWS_WITH(comp6771::unit(v3),
		                  "euclidean_vector with no dimensions does not have a unit vector");
		CHECK_THROWS_WITH(comp6771::unit(v4),
		                  "euclidean_vector with zero euclidean normal does not have a unit vector");
	}
}

TEST_CASE("Dot Product", "[utility_functions]") {
	auto const v1 = comp6771::euclidean_vector{14.3, 26.5, -12.8, 2.1};
	auto const v2 = comp6771::euclidean_vector{1, 2, 3, 4};

	SECTION("Check dot product computation") {
		CHECK(comp6771::dot(v1, v2) == Approx(14.3 * 1 + 26.5 * 2 + -12.8 * 3 + 2.1 * 4));
	}

	auto const v3 = comp6771::euclidean_vector(0);
	auto const v4 = comp6771::euclidean_vector(5);

	SECTION("Check dot product computation - zero vector") {
		CHECK(comp6771::dot(v3, v3) == 0.0);
	}

	SECTION("Exception handling") {
		CHECK_THROWS_WITH(comp6771::dot(v1, v3), "Dimensions of LHS(4) and RHS(0) do not match");
		CHECK_THROWS_WITH(comp6771::dot(v3, v4), "Dimensions of LHS(0) and RHS(5) do not match");
	}
}