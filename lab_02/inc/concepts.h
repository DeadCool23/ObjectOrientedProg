#ifndef __CONCEPTS_HPP__
#define __CONCEPTS_HPP__

#include <ostream>
#include <concepts>
#include <type_traits>

namespace MathConcepcts {
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
    concept Neitral = requires { T(0); };

    template<typename T>
    concept Сommutativity = requires (T a, T b) {
        a + b == b + a;
    };
}

template<typename T>
concept EmptyConstructable = std::is_default_constructible_v<T>;

template<typename _From, typename _To>
concept ConvertableTo = std::convertible_to<_From, _To>;

template<typename T, typename U>
concept Convertable = 
    ConvertableTo<T, U> &&
    ConvertableTo<U, T>;

template<typename T>
concept EqualityComparable = requires (T a, T b) {
    {a == b} -> std::convertible_to<bool>;
    {a != b} -> std::convertible_to<bool>;
    // {!a} -> std::convertible_to<bool>;
    // !a == (a == T(0));
};

template <typename C>
concept ContainerClass = requires (C c) {
    typename C::value_type;
    typename C::size_type;

    typename C::iterator;
    typename C::const_iterator;

    { c.size() } noexcept -> std::same_as<typename C::size_type>;
    { c.end() } noexcept -> std::same_as<typename C::iterator>;
    { c.begin() } noexcept -> std::same_as<typename C::iterator>;
};

template<typename T>
concept Incrementable = requires (T a) {
    { a++ } -> std::same_as<T>;
    { ++a } -> std::same_as<T&>;
};

template <typename I>
concept IteratorCheck = requires() {
    typename I::value_type;
    typename I::difference_type;
    typename I::pointer;
    typename I::reference;
};

template <typename T, typename U>
concept DerivedFrom = std::is_base_of<U, T>::value;

namespace IterConcepts {
    template <typename I>
    concept InputIterator = 
        IteratorCheck<I> &&
        requires { typename I::iterator_category; } &&
        EqualityComparable<I> &&
        DerivedFrom<typename I::iterator_category, std::input_iterator_tag>;

    template <typename I>
    concept ForwardIterator = 
        InputIterator<I> && 
        Incrementable<I> && 
        DerivedFrom<typename I::iterator_category, std::forward_iterator_tag>;
}

template <typename T>
concept Printable = requires (T a, std::ostream os) { os << a; };

#endif // __CONCEPTS_HPP__