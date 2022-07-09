#ifndef COMP6771_EUCLIDEAN_VECTOR_HPP
#define COMP6771_EUCLIDEAN_VECTOR_HPP

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <list>
#include <iostream>


namespace comp6771 {
	class euclidean_vector_error : public std::runtime_error {
	public:
		explicit euclidean_vector_error(std::string const& what)
		: std::runtime_error(what) {}
	};

	class euclidean_vector {
	public:
		// Constructors
		euclidean_vector() noexcept;
		explicit euclidean_vector(int) noexcept;
		euclidean_vector(int, double) noexcept;
		euclidean_vector(std::vector<double>::const_iterator,
						 std::vector<double>::const_iterator) noexcept;
		euclidean_vector(std::initializer_list<double>) noexcept;

		// Copy constructor
		euclidean_vector(euclidean_vector const&) noexcept;

		// Move constructor
		euclidean_vector(euclidean_vector&&) noexcept;

		// Destructor
		~euclidean_vector() noexcept;

		// Operator overloads
		auto operator=(euclidean_vector const&) noexcept -> euclidean_vector&; // Copy assignment
		auto operator=(euclidean_vector&&) noexcept -> euclidean_vector&; // Move assignment

		auto operator[](int index) noexcept -> double&;
		auto operator[](int index) const noexcept -> const double&;

		auto operator+() const noexcept -> euclidean_vector; // Unary plus
		auto operator-() const noexcept -> euclidean_vector; // Negation

		auto operator+=(euclidean_vector const&) -> euclidean_vector&; // Compound addition
		auto operator-=(euclidean_vector const&) -> euclidean_vector&; // Compound subtraction
		auto operator*=(double) noexcept -> euclidean_vector&; // Compound multiplication
		auto operator/=(double) -> euclidean_vector&; // Compound division

		explicit operator std::vector<double>() const noexcept; // Vector type conversion
		explicit operator std::list<double>() const noexcept; // List type conversion

		// Member functions
		[[nodiscard]] auto at(int) const -> double; // Return value at index
		[[nodiscard]] auto at(int) -> double&; // Return reference to value at index
		[[nodiscard]] auto dimensions() const -> int; // Return the number of dimensions

		// Friend functions
		friend auto operator==(euclidean_vector const&,
							   euclidean_vector const&) noexcept -> bool; // Equal
		friend auto operator!=(euclidean_vector const&,
							   euclidean_vector const&) noexcept -> bool; // Not Equal

		friend auto operator+(euclidean_vector const&,
							  euclidean_vector const&) -> euclidean_vector; // Addition
		friend auto operator-(euclidean_vector const&,
						      euclidean_vector const&) -> euclidean_vector; // Subtraction

		friend auto operator*(euclidean_vector const&, double) noexcept -> euclidean_vector; // Multiply
		friend auto operator/(euclidean_vector const&, double) -> euclidean_vector; // Divide

		friend auto operator<<(std::ostream&,
							   euclidean_vector const&) noexcept -> std::ostream&; // Output stream

		// Helper functions
		static auto is_dimension_equal(euclidean_vector const& v1,
									   euclidean_vector const& v2) -> bool;

		static auto throw_if_dimension_not_equal(euclidean_vector const& v1,
												 euclidean_vector const& v2) -> void;
		auto throw_if_factor_is_zero(double) -> void;
		auto throw_if_index_out_of_range(int, int) const -> void;

		friend auto euclidean_norm(euclidean_vector const& v) noexcept -> double;
		static auto throw_if_dimension_is_zero(int) -> void;
		static auto throw_if_norm_is_zero(double) -> void;

		friend auto dot(euclidean_vector const& v1,
						euclidean_vector const& v2) -> double;
	private:
		// ass2 spec requires we use std::unique_ptr<double[]>
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		std::unique_ptr<double[]> magnitude_;
		std::size_t dimension_;
		mutable double e_norm_;
	};

	// Utility functions
	auto euclidean_norm(euclidean_vector const& v) noexcept -> double; // Euclidean norm
	auto unit(euclidean_vector const& v) -> euclidean_vector; // Unit vector
	auto dot(euclidean_vector const& x,
			 euclidean_vector const& y) -> double; // Dot product

} // namespace comp6771
#endif // COMP6771_EUCLIDEAN_VECTOR_HPP
