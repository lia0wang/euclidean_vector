// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <comp6771/euclidean_vector.hpp>

namespace comp6771 {

	/*
	 * Constructors
	 */

	euclidean_vector::euclidean_vector() noexcept
	: magnitude_{std::make_unique<double[]>(1)}
	, dimension_{1}
	, e_norm_{-1} {
		magnitude_[0] = 0;
	}

	euclidean_vector::euclidean_vector(int num_dimensions) noexcept
	: magnitude_{std::make_unique<double[]>(static_cast<std::size_t>(num_dimensions))}
	, dimension_{static_cast<std::size_t>(num_dimensions)}
	, e_norm_{-1} {
		std::fill_n(magnitude_.get(), dimension_, 0);
	}

	euclidean_vector::euclidean_vector(int num_dimensions, double value) noexcept
	: euclidean_vector(num_dimensions) {
		std::fill_n(magnitude_.get(), dimension_, value);
	}

	euclidean_vector::euclidean_vector(std::vector<double>::const_iterator begin,
	                                   std::vector<double>::const_iterator end) noexcept
	: euclidean_vector(static_cast<int>(std::distance(begin, end))) {
		std::copy(begin, end, magnitude_.get());
	}

	euclidean_vector::euclidean_vector(std::initializer_list<double> list) noexcept
	: euclidean_vector(static_cast<int>(list.size()), 0) {
		std::copy(list.begin(), list.end(), magnitude_.get());
	}

	euclidean_vector::euclidean_vector(euclidean_vector const& org) noexcept
	: euclidean_vector(org.dimension_) {
		std::copy(org.magnitude_.get(), org.magnitude_.get() + dimension_, magnitude_.get());
		e_norm_ = org.e_norm_;
	}

	euclidean_vector::euclidean_vector(euclidean_vector&& org) noexcept
	: magnitude_{std::move(org.magnitude_)}
	, dimension_{org.dimension_}
	, e_norm_{org.e_norm_} {
		org.dimension_ = 0;
		org.e_norm_ = -1;
	}

	/*
	 * Operator Overloads
	 */
	auto euclidean_vector::operator=(euclidean_vector const& org) noexcept -> euclidean_vector& {
		auto cp_vector = euclidean_vector(org);
		std::swap(magnitude_, cp_vector.magnitude_);
		std::swap(dimension_, cp_vector.dimension_);
		std::swap(e_norm_, cp_vector.e_norm_);
		return *this;
	}

	auto euclidean_vector::operator=(euclidean_vector&& org) noexcept -> euclidean_vector& {
		if (this == &org) // self-assignment
			return *this;

		std::swap(magnitude_, org.magnitude_);
		std::swap(dimension_, org.dimension_);
		std::swap(e_norm_, org.e_norm_);

		// reset the moved-from vector
		org.dimension_ = 0;
		org.e_norm_ = -1;
		org.magnitude_.reset();

		return *this;
	}

	auto euclidean_vector::operator[](int index) noexcept -> double& {
		assert(index >= 0 and index < dimension_);
		e_norm_ = -1;
		return magnitude_[static_cast<std::size_t>(index)];
	}

	auto euclidean_vector::operator[](int index) const noexcept -> const double& {
		assert(index >= 0 and index < dimension_);
		return magnitude_[static_cast<std::size_t>(index)];
	}

	auto euclidean_vector::operator+() const noexcept -> euclidean_vector {
		return *this;
	}

	auto euclidean_vector::operator-() const noexcept -> euclidean_vector {
		std::transform(magnitude_.get(),
		               magnitude_.get() + dimension_,
		               magnitude_.get(),
		               std::negate<double>());
		return *this;
	}

	auto euclidean_vector::operator+=(euclidean_vector const& v2) -> euclidean_vector& {
		euclidean_vector::throw_if_dimension_not_equal(*this, v2);
		std::transform(magnitude_.get(),
		               magnitude_.get() + dimension_,
		               v2.magnitude_.get(),
		               magnitude_.get(),
		               std::plus<double>());
		e_norm_ = -1;
		return *this;
	}

	auto euclidean_vector::operator-=(euclidean_vector const& v2) -> euclidean_vector& {
		euclidean_vector::throw_if_dimension_not_equal(*this, v2);
		std::transform(magnitude_.get(),
		               magnitude_.get() + dimension_,
		               v2.magnitude_.get(),
		               magnitude_.get(),
		               std::minus<double>());
		e_norm_ = -1;
		return *this;
	}

	auto euclidean_vector::operator*=(double v2) noexcept -> euclidean_vector& {
		std::transform(magnitude_.get(), magnitude_.get() + dimension_, magnitude_.get(), [&](double x) {
			return std::multiplies<double>()(x, v2);
		});
		e_norm_ = -1;
		return *this;
	}

	auto euclidean_vector::operator/=(double v2) -> euclidean_vector& {
		euclidean_vector::throw_if_factor_is_zero(v2);
		std::transform(magnitude_.get(), magnitude_.get() + dimension_, magnitude_.get(), [&](double x) {
			return std::divides<double>()(x, v2);
		});
		e_norm_ = -1;
		return *this;
	}

	euclidean_vector::operator std::vector<double>() const noexcept {
		return std::vector<double>(magnitude_.get(), magnitude_.get() + dimension_);
	}

	euclidean_vector::operator std::list<double>() const noexcept {
		return std::list<double>(magnitude_.get(), magnitude_.get() + dimension_);
	}

	/*
	 * Member Functions
	 */
	[[nodiscard]] auto euclidean_vector::at(int index) const -> double {
		euclidean_vector::throw_if_index_out_of_range(index, static_cast<int>(dimension_));
		return magnitude_[static_cast<std::size_t>(index)];
	}

	[[nodiscard]] auto euclidean_vector::at(int index) -> double& {
		euclidean_vector::throw_if_index_out_of_range(index, static_cast<int>(dimension_));
		e_norm_ = -1;
		return magnitude_[static_cast<std::size_t>(index)];
	}

	[[nodiscard]] auto euclidean_vector::dimensions() const -> int {
		return static_cast<int>(dimension_);
	}

	/*
	 * Friend Functions
	 */
	auto operator==(euclidean_vector const& v1, euclidean_vector const& v2) noexcept -> bool {
		return euclidean_vector::is_dimension_equal(v1, v2)
		       and std::equal(v1.magnitude_.get(),
		                      v1.magnitude_.get() + v1.dimension_,
		                      v2.magnitude_.get(),
		                      v2.magnitude_.get() + v2.dimension_,
		                      [](double x, double y) { return std::equal_to<double>()(x, y); });
	}

	auto operator!=(euclidean_vector const& v1, euclidean_vector const& v2) noexcept -> bool {
		return not(v1 == v2);
	}

	auto operator+(euclidean_vector const& v1, euclidean_vector const& v2) -> euclidean_vector {
		auto lhs_cp = euclidean_vector(v1);
		return lhs_cp += v2;
	}

	auto operator-(euclidean_vector const& v1, euclidean_vector const& v2) -> euclidean_vector {
		auto lhs_cp = euclidean_vector(v1);
		return lhs_cp -= v2;
	}

	auto operator*(euclidean_vector const& vec, double factor) noexcept -> euclidean_vector {
		auto vec_cp = euclidean_vector(vec);
		return vec_cp *= factor;
	}

	auto operator/(euclidean_vector const& vec, double factor) -> euclidean_vector {
		auto vec_cp = euclidean_vector(vec);
		return vec_cp /= factor;
	}

	auto operator<<(std::ostream& os, euclidean_vector const& vec) noexcept -> std::ostream& {
		if (vec.dimension_ == 0)
			return os << "[]";

		os << "[";

		std::copy(vec.magnitude_.get(),
		          vec.magnitude_.get() + vec.dimension_,
		          std::ostream_iterator<double>(os, " "));
		os.seekp(-1, std::ios_base::end);
		return os << "]";
	}

	/*
	 * Utility functions
	 */
	auto euclidean_norm(euclidean_vector const& v) noexcept -> double {
		if (v.e_norm_ != -1)
			return v.e_norm_;

		auto e_norm = std::sqrt(std::inner_product(v.magnitude_.get(),
		                                           v.magnitude_.get() + v.dimension_,
		                                           v.magnitude_.get(),
		                                           0.0));
		v.e_norm_ = e_norm;
		return e_norm;
	}

	auto unit(euclidean_vector const& v) -> euclidean_vector {
		euclidean_vector::throw_if_dimension_is_zero(v.dimensions());
		auto e_norm = euclidean_norm(v);
		auto unit_vec = euclidean_vector(v);
		euclidean_vector::throw_if_norm_is_zero(e_norm);
		return unit_vec /= e_norm;
	}

	auto dot(euclidean_vector const& v1, euclidean_vector const& v2) -> double {
		euclidean_vector::throw_if_dimension_not_equal(v1, v2);
		return v1.dimensions() == 0 ? 0
		                            : std::inner_product(v1.magnitude_.get(),
		                                                 v1.magnitude_.get() + v1.dimension_,
		                                                 v2.magnitude_.get(),
		                                                 0.0);
	}

	/*
	 * Helper Functions
	 */
	auto euclidean_vector::throw_if_norm_is_zero(double norm) -> void {
		if (norm == 0)
			throw euclidean_vector_error("euclidean_vector with zero euclidean normal does not "
			                             "have a unit vector");
	}

	auto euclidean_vector::throw_if_dimension_is_zero(int dimension) -> void {
		if (dimension == 0)
			throw euclidean_vector_error("euclidean_vector with no dimensions does not have a unit "
			                             "vector");
	}

	auto euclidean_vector::is_dimension_equal(euclidean_vector const& v1, euclidean_vector const& v2)
	   -> bool {
		return v1.dimension_ == v2.dimension_;
	}

	auto euclidean_vector::throw_if_dimension_not_equal(euclidean_vector const& v1,
	                                                    euclidean_vector const& v2) -> void {
		if (not euclidean_vector::is_dimension_equal(v1, v2))
			throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(v1.dimension_)
			                             + ") "
			                               "and RHS("
			                             + std::to_string(v2.dimension_) + ") do not match");
	}

	auto euclidean_vector::throw_if_factor_is_zero(double factor) -> void {
		if (factor == 0)
			throw euclidean_vector_error("Invalid vector division by 0");
	}

	auto euclidean_vector::throw_if_index_out_of_range(int index, int dimension) const -> void {
		if (index < 0 or index >= dimension)
			throw euclidean_vector_error("Index " + std::to_string(index)
			                             + " is not valid for this euclidean_vector object");
	}
} // namespace comp6771