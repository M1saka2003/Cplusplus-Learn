//
// Created by m1saka on 23-5-5.
//

#ifndef MYLIB_VECTOR_HPP
#define MYLIB_VECTOR_HPP

#include <memory>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>
#include <cstring>

namespace hsclib {

    template<typename T>
    struct vector_iterator {
        using value_type = std::remove_cv_t<T>;
        using pointer = T *;
        using reference = T &;

        [[nodiscard]]constexpr reference operator*() const noexcept {
            return *ptr;
        }

        [[nodiscard]] constexpr pointer operator->() const noexcept {
            return ptr;
        }

        constexpr vector_iterator &operator++() noexcept {
            ++ptr;
            return *this;
        }

        constexpr vector_iterator<T> operator++(int) noexcept {
            vector_iterator tmp{*this};
            ++*this;
            return tmp;
        }

        constexpr vector_iterator &operator--() noexcept {
            --ptr;
            return *this;
        }

        constexpr vector_iterator &operator--(int) noexcept {
            vector_iterator tmp{*this};
            --*ptr;
            return tmp;
        }

        [[nodiscard]] constexpr vector_iterator operator+(size_t n) const noexcept {
            vector_iterator tmp{*this};
            tmp.ptr += n;
            return tmp;
        }

        [[nodiscard]] constexpr vector_iterator operator-(size_t n) const noexcept {
            vector_iterator tmp{*this};
            tmp.ptr -= n;
            return tmp;
        }

        constexpr size_t operator-(const vector_iterator rhs) const noexcept {
            return ptr - rhs.ptr;
        }

        constexpr void operator+=(size_t n) {
            ptr += n;
        }

        constexpr void operator-=(size_t n) {
            ptr -= n;
        }

        constexpr void operator[](size_t n) {
            return ptr[n];
        }

        friend constexpr bool operator==(const vector_iterator &v1, const vector_iterator &v2) {
            return v1.ptr == v2.ptr;
        }

        friend constexpr auto operator<=>(const vector_iterator &v1, const vector_iterator &v2) {
            if (v1.ptr > v1.ptr) {
                return 1;
            } else if (v1.ptr < v2.ptr) {
                return -1;
            } else return 0;
        }

        explicit constexpr vector_iterator(pointer rhs) : ptr(rhs) {}

        pointer ptr;
    };

    template<typename T, typename Allocator= std::allocator<T>>
    struct vector {
        using value_type = T;
        using allocator_type = Allocator;
        using size_type = typename std::allocator_traits<Allocator>::size_type;
        using difference_type = typename std::allocator_traits<Allocator>::difference_type;
        using reference = value_type &;
        using const_reference = const value_type &;
        using pointer = typename std::allocator_traits<Allocator>::pointer;
        using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
        using iterator = vector_iterator<T>;
        using const_iterator = const vector_iterator<T>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        constexpr vector() noexcept(noexcept(Allocator())): _size(0), _capacity(0), _ptr(nullptr) {}

        constexpr vector(const vector &rhs) : _size(rhs.size()), _capacity(rhs.capacity()), _ptr(nullptr) {
            reserve(rhs.capacity());
            for (size_type i = 0; i < rhs.size(); i++) {
                new(_ptr + i)value_type{};
            }
            std::copy(rhs.begin(), rhs.end(), begin());
        }

        constexpr vector(size_type count, value_type value) : _size(0), _capacity(0), _ptr(nullptr) {
            assign(count, value);
        }

        constexpr vector(std::initializer_list<value_type> init) : _size(init.size()), _capacity(0), _ptr(nullptr) {
            reserve(_size);
            for (size_type i = 0; i < init.size(); i++) {
                new(_ptr + i)value_type{};
            }
            std::copy(init.begin(), init.end(), begin());
        }

        template<typename InputIt, typename =std::enable_if_t<std::is_same_v<InputIt, iterator>>>
        constexpr vector(InputIt first, InputIt last):_size(last - first), _capacity(0), _ptr(nullptr) {
            reserve(last - first + 1);
            difference_type len = last - first;
            for (size_type i = 0; i < len; i++) {
                new(_ptr + i)value_type{};
            }
            std::copy(first, last, begin());
        }

        constexpr vector(vector &&rhs) noexcept: _size(rhs.size()), _capacity(rhs.capacity()) {
            _ptr = rhs.data();
            rhs.data() = nullptr;
        }

        constexpr ~vector() {
            if constexpr (!std::is_fundamental<T>::value) { free(); }
            _allocator.deallocate(_ptr, _capacity);
        }

        constexpr vector &operator=(const vector &rhs) {
            if (this != &rhs) {
                for (auto i = begin(); i != end(); i++) {
                    i->~value_type();
                }
                _allocator.deallocate(_ptr, _capacity);
                _ptr = _allocator.allocate(rhs.capacity());
                for (size_type i = 0; i < rhs.size(); i++) {
                    new(_ptr + i)value_type{};
                }
                std::copy(rhs.begin(), rhs.end(), begin());
                _size = rhs.size();
                _capacity = rhs.capacity();
            }
            return *this;
        }

        constexpr vector &operator=(vector &&rhs) noexcept {
            if (this != &rhs) {
                for (auto i = begin(); i != end(); i++) {
                    i->~value_type();
                }
                _ptr = rhs._ptr;
                rhs._ptr = nullptr;
                _size = rhs._size;
                rhs._size = 0;
                _capacity = rhs._capacity;
                rhs._capacity = 0;
            }
            return *this;
        }

        template<typename InputIt>
        constexpr void assign(InputIt first, InputIt last) {
            difference_type len = last - first;
            reserve(len);
            _size = _capacity;
            std::copy(first, last, begin());
        }

        constexpr void assign(size_type n, const value_type &u) {
            reserve(n);
            while (_size != _capacity) {
                new(_ptr + _size)T(std::move(u));
                _size++;
            }
        }

        constexpr void assign(std::initializer_list<T> rhs) {
            reserve(rhs.size());
            _size = _capacity;
            std::copy(rhs.begin(), rhs.end(), begin());
        }

        //迭代器
        constexpr iterator begin() noexcept {
            return vector_iterator{_ptr};
        }

        constexpr const_iterator begin() const noexcept {
            return const_iterator{_ptr};
        }

        constexpr iterator end() noexcept {
            return vector_iterator{_ptr + _size};
        }

        constexpr const_iterator end() const noexcept {
            return vector_iterator{_ptr + _size};
        }

        constexpr reverse_iterator rbegin() noexcept {
            return reverse_iterator{end()};
        }

        constexpr const_reverse_iterator rbegin() const noexcept {
            return const_reverse_iterator{end()};
        }

        constexpr reverse_iterator rend() noexcept {
            return reverse_iterator{begin()};
        }

        constexpr const_reverse_iterator rend() const noexcept {
            return const_reverse_iterator{begin()};
        }

        constexpr const_iterator cbegin() const noexcept {
            return const_iterator{begin()};
        }

        constexpr const_iterator cend() const noexcept {
            return const_iterator{end()};
        }

        //容量
        [[nodiscard]]constexpr bool empty() const noexcept {
            return _size == 0;
        }

        constexpr size_type capacity() const noexcept {
            return _capacity;
        }

        constexpr size_type size() const noexcept {
            return _size;
        }

        constexpr void resize(size_type count) {
            reserve(count);
            _size = count;
        }

        constexpr void resize(size_type count, const value_type &value) {
            size_type cur_size = _size;
            resize(count);
            if (cur_size < _size) {
                std::fill(end() - count, end(), value);
            }
        }

        constexpr void reserve(size_type new_capacity) {
            if (new_capacity < capacity()) return;
            pointer tmp = _ptr;
            _ptr = _allocator.allocate(new_capacity);
            if (_ptr != nullptr && tmp != nullptr) {
                for (size_type i = 0; i < size(); i++) {
                    new(_ptr + i)value_type{};
                }
                std::copy(tmp, tmp + size(), _ptr);
                for (auto i = tmp; i < tmp + _size; i++) {
                    i->~value_type();
                }
                _allocator.deallocate(tmp, _capacity);
            }
            _capacity = new_capacity;
        }

        //元素访问
        constexpr reference operator[](size_type n) {
            return _ptr[n];
        }

        constexpr const_reference operator[](size_type n) const {
            return _ptr[n];
        }

        constexpr const_reference at(size_type n) const {
            if (n > _size) throw std::out_of_range{""};
            return _ptr[n];
        }

        constexpr reference at(size_type n) {
            if (n > _size) throw std::out_of_range{""};
            return _ptr[n];
        }

        constexpr reference front() {
            return *_ptr;
        }

        constexpr const_reference front() const {
            return *_ptr;
        }

        constexpr reference back() {
            return *(_ptr + _size - 1);
        }

        constexpr const_reference back() const {
            return *(_ptr + _size - 1);
        }

        //数据访问

        constexpr pointer data() noexcept {
            return _ptr;
        }

        constexpr const_pointer data() const noexcept {
            return _ptr;
        }

        //修改器
        template<typename...Args>
        constexpr reference emplace_back(Args &&...args) {
            if (_size == _capacity) {
                reserve(_capacity * 2 + 1);
            }
            new(_ptr + _size)value_type(std::forward<Args>(args)...);
            _size++;
            return *(_ptr + _size - 1);
        }

        constexpr void push_back(const T &x) {
            if (_size == _capacity) {
                reserve(_capacity * 2 + 1);
            }
            new(_ptr + _size)T(std::move(x));
            _size++;
        }

        constexpr void push_back(T &&x) {
            if (_size == _capacity) {
                reserve(_capacity * 2 + 1);
            }
            new(_ptr + _size)T(std::move(x));
            _size++;
        }

        constexpr void pop_back() {
            if (_size > 0) {
                _size--;
                (_ptr + _size)->~value_type();
            }
        }

        constexpr void clear() {
            if constexpr (std::is_fundamental<T>::value) { free(); }
            _ptr = nullptr;
            _size = _capacity = 0;
        }

        template<typename...Args>
        constexpr iterator emplace(iterator pos, Args &&...args) {
            size_type index = (pos - begin());
            if (_size == _capacity) {
                reserve(_capacity * 2 + 1);
            }

            if (index <= _size) {
                new(_ptr + _size)T;
                for (int i = _size; i > index; i--) {
                    _ptr[i] = _ptr[i - 1];
                }
            }
            _size++;
            pos->~value_type();
            new(_ptr + index)value_type(std::forward<Args>(args)...);
            return pos;
        }

        constexpr iterator insert(const_iterator position, const value_type &x) {
            size_type index = (position - begin());
            if (_size == _capacity) {
                reserve(_capacity * 2 + 1);
            }
            new(_ptr + _size)T;

            for (int i = _size; i > index; i--) {
                _ptr[i] = _ptr[i - 1];
            }
            _size++;
            _ptr[index] = x;
            return position;
        }

        constexpr iterator insert(const_iterator position, value_type &&x) {
            size_type index = (position - begin());
            if (_size == _capacity) {
                reserve(_capacity * 2 + 1);
            }
            new(_ptr + _size)T;

            for (int i = _size; i > index; i--) {
                _ptr[i] = _ptr[i - 1];
            }
            _size++;
            _ptr[index] = std::move(x);
            return position;
        }

        constexpr iterator insert(const_iterator pos, size_type n, T value) {
            if (n == 0) return pos;
            std::ptrdiff_t dis = std::distance(begin(), pos);
            reserve(_size + n);
            std::vector tmp(begin() + dis, end());
            std::copy(tmp.begin(), tmp.end(), cbegin() + dis + n);
            std::fill(_ptr + dis, _ptr + dis + n, value);
            _size += n;
            return iterator{_ptr + dis};
        }

        template<typename InputIt, typename =std::enable_if_t<std::is_same_v<InputIt, iterator>>>
        constexpr iterator insert(const_iterator pos, InputIt first, InputIt last) {
            if (std::distance(first, last) == 0) {
                return pos;
            }

            std::ptrdiff_t dis = std::distance(cbegin(), pos);
            std::ptrdiff_t count = std::distance(first, last);
            reserve(_size + count);
            std::vector tmp(begin() + dis, end());
            std::copy(tmp.begin(), tmp.end(), cbegin() + dis + count);
            std::copy(first, last, cbegin() + dis);

            _size += count;
            return iterator{_ptr + dis};
        }

        constexpr iterator insert(const_iterator pos, std::initializer_list<value_type> rhs) {
            insert(pos, rhs.begin(), rhs.end());
        }

        constexpr iterator erase(const_iterator pos) {
            std::ptrdiff_t dis = std::distance(pos, cbegin());
            std::copy(begin() + dis + 1, end(), begin() + dis);
            _size--;
            return vector_iterator{_ptr + dis};
        }

        constexpr iterator erase(const_iterator first, const_iterator last) {
            std::ptrdiff_t dis = std::distance(first, cbegin());
            std::ptrdiff_t count = std::distance(first, last);
            if (count == 0) return last;
            std::copy(last, end(), first);
            _size -= count;
            return vector_iterator{_ptr + dis};
        }

    private:

        void free() {
            if constexpr (std::is_fundamental<T>::value) return;
            for (auto i = begin(); i != end(); i++) {
                i->~value_type();
            }
        }

        pointer _ptr;
        size_type _size;
        size_type _capacity;
        allocator_type _allocator;
    };

}
#endif //MYLIB_VECTOR_HPP
