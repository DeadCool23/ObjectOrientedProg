#ifndef __LIST_H__
#define __LIST_H__

#include "errors.h"

#include "concepts.h"

#include "container.h"

#include "iterator.h"
#include "citerator.h"

#include <memory>
#include <functional>
#include <initializer_list>

template <typename T>
requires Comparable<T> && Empty<T> &&
         Divable<T> && Multable<T> && 
         Neitral<T> && Printable<T>
class List : public Container {
public:
    using value_t = T;
    using iterator_t = Iterator<T>;
    using citerator_t = ConstIterator<T>;

    friend class Iterator<T>;
    friend class ConstIterator<T>;
public:
    List(void);
    explicit List(const T &value);
    List(size_t size, const T &value);
    List(const std::initializer_list<T> &init);

    List(const iterator_t &beg, const iterator_t &end);
    List(const iterator_t &beg, const iterator_t &end, size_t count);
    
    List(const citerator_t &beg, const citerator_t &end);
    List(const citerator_t &beg, const citerator_t &end, size_t count);

    template<typename Iter>
    requires IteratorCheck<Iter, T>
    List(const Iter &begin, const Iter &end);
    template<typename Iter>
    requires IteratorCheck<Iter, T>
    List(const Iter &begin, const Iter &end, size_t count);

    template <template<typename> class C>
    requires ContainerClass<C<T>>
    explicit List(const C<T> &container);

    template <typename U, template<typename> class C>
    requires ContainerClass<C<U>> && Convertable<T, U>
    explicit List(const C<U> &container);


    List(List<T> &&list);
    explicit List(const List<T> &list);
    template <typename U>
    requires Convertable<T, U>
    explicit List(const List<U> &list);

    bool is_empty() const override;
    size_t size(void) const override;

    void push_back(const T &value);
    void push_back(const List<T> &list);
    template<typename U>
    requires Convertable<T, U>
    void push_back(const List<U> &list);

    void push_front(const T &value);
    void push_front(const List<T> &list);
    template<typename U>
    requires Convertable<T, U>
    void push_front(const List<U> &list);
    
    T pop_back(void);
    T pop_front(void);
    T pop(size_t index = 0);

    void clear(void) noexcept;
    void reverse(void) noexcept;
    bool find(const T &find_value) const noexcept;

    void insert(size_t index, const T &value);
    void insert(size_t index, const List<T> &list);
    template<typename U>
    requires Convertable<T, U>
    void insert(size_t index, const List<U> &list);

    void remove(const T &value);

    void each(const std::function<T(const T &value)> &func);

    T& operator[](size_t ind);
    const T& operator[](size_t ind) const;

    List<T> &operator=(List<T> &&list);
    List<T> &operator=(const List<T> &list);
    template<typename U>
    requires Convertable<T, U>
    List<T> &operator=(const List<U> &list);

    List<T> operator*(const T& multer);
    List<T> &operator*=(const T& multer);

    List<T> operator/(const T& diver);
    List<T> &operator/=(const T& diver);

    List<T> operator+(const List<T> &add_list);
    template<typename U>
    requires Convertable<T, U>
    List<T> operator+(const List<U> &add_list);
    
    List<T> &operator+=(const List<T> &add_list);
    template<typename U>
    requires Convertable<T, U>
    List<T> &operator+=(const List<U> &add_list);

    template<typename U>
    requires Convertable<T, U>
    bool operator==(const List<U> &add_list);

    template<typename U>
    requires Convertable<T, U>
    bool operator!=(const List<U> &add_list);

    void print(void) const noexcept;
    void debug_print(void) const noexcept;

    iterator_t begin(void);
    iterator_t end(void);

    citerator_t begin(void) const;
    citerator_t end(void) const;

    citerator_t cbegin(void) const;
    citerator_t cend(void) const;

    ~List() = default;

protected:
    class ListNode {
        friend class Iterator<T>;
        friend class ConstIterator<T>;
    public:
        ListNode(void);
        ListNode(const T &val);
        ListNode(ListNode &node);
        ListNode(ListNode &&node);
        ListNode(std::shared_ptr<ListNode> &node);

        void set_value(const T &val);
        void set_next(ListNode &node);
        void set_next(const std::shared_ptr<ListNode> &node);

        void set_next_null(void);

        T& get_ref(void);
        const T& get_value(void) const;

        std::shared_ptr<ListNode> get_next(void) const;

        bool operator == (const ListNode &node) const;
        bool operator != (const ListNode &node) const;

        bool operator == (const std::shared_ptr<ListNode> &node) const;
        bool operator != (const std::shared_ptr<ListNode> &node) const;

        ~ListNode() = default;

    private:
        T value;
        std::shared_ptr<ListNode> next;
    };

protected:
    std::shared_ptr<ListNode> get_head(void);
    std::shared_ptr<ListNode> get_tail(void);

    std::shared_ptr<ListNode> NodeAlloc(const T &value);

private:
    std::shared_ptr<ListNode> head;
    std::shared_ptr<ListNode> tail;
};

#include "list.hpp"
#include "listnode.hpp"

#endif // __LIST_H__