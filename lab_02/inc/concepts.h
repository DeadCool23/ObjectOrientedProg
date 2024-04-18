#ifndef __CONCEPTS_HPP__
#define __CONCEPTS_HPP__

#include <ostream>
#include <concepts>

template<typename T>
concept Summable = requires (T a, T b) {
    {a + b} -> std::same_as<T>;
};

template<typename T>
concept Multable = requires (T a, T b) {
    {a * b} -> std::same_as<T>;
};

template<typename T>
concept Divable = requires (T a, T b) {
    {a / b} -> std::same_as<T>;
    {b / a} -> std::same_as<T>;
    // (a / b) * (b / a) == T(1); 
};

template<typename T>
concept Empty = requires { T(); };

template<typename T>
concept Neitral = requires { T(0); };

template<typename T>
concept Сommutativity = requires (T a, T b) {
    a + b == b + a;
};

template<typename T>
concept Comparable = requires (T a, T b) {
    {a == b} -> std::convertible_to<bool>;
    {a != b} -> std::convertible_to<bool>;
    // {!a} -> std::convertible_to<bool>;
    // !a == (a == T(0));
};

template<typename T, typename U>
concept Convertable = requires (T a, U b) {
    T(b); U(a);
};

template <typename C>
concept ContainerClass = requires (C c) {
    c.size();
    c.begin(); c.end();
    {C()} -> std::same_as<C>;
};

template <typename T>
concept Printable = requires (T a, std::ostream os) {
    os << a;
};

#endif // __CONCEPTS_HPP__