#pragma once
#ifndef C_VECTOR_HPP
#define C_VECTOR_HPP

#pragma pack(push, 1)

// C++
#include <iostream>

template <class T>
class c_vector
{
private:
   size_t m_size;
   size_t m_capacity;
   T *m_store;
   static const std::size_t m_space = 10;

   void realloc()
   {
      c_vector tmp(m_capacity + m_space);
      std::copy(m_store, m_store + m_size, tmp.m_store);
      swap(*this, tmp);
   }

public:
   using iterator = T *;
   using const_iterator = const T *;
   using reference = T &;
   using const_reference = const T &;

   c_vector()
       : m_size(0), m_capacity(m_space), m_store(new T[m_space])
   {
   }

   explicit c_vector(size_t count)
       : m_size(count),
         m_capacity(m_space * (static_cast<size_t>(count / m_space) + 1)),
         m_store(nullptr)
   {
      m_store = new T[m_capacity];
      for (auto &i : *this)
         i = T();
   }

   explicit c_vector(size_t count, const T &value)
       : m_size(count),
         m_capacity(m_space * (static_cast<size_t>(count / m_space) + 1)),
         m_store(nullptr)
   {
      m_store = new T[m_capacity];
      for (auto &i : *this)
         i = value;
   }

   explicit c_vector(const c_vector &other)
       : m_size(other.m_size), m_capacity(other.m_capacity), m_store(new T[other.m_capacity])
   {
      std::copy(other.m_store, other.m_store + m_size, m_store);
   }

   explicit c_vector(c_vector &&other) noexcept
       : c_vector()
   {
      swap(*this, other);
   }

   c_vector(std::initializer_list<T> l)
       : m_size(l.size()),
         m_capacity(m_space * (static_cast<size_t>(l.size() / m_space) + 1)),
         m_store(nullptr)
   {
      m_store = new T[m_capacity];
      std::copy(l.begin(), l.end(), m_store);
   }

   ~c_vector() noexcept { delete[] m_store; }

   c_vector &operator=(const c_vector &other) noexcept
   {
      c_vector v(other);
      swap(*this, v);
      return *this;
   }

   reference operator[](size_t pos) noexcept
   {
      return m_store[pos];
   }

   size_t size() const noexcept { return m_size; }
   size_t capacity() const noexcept { return m_capacity; }
   bool empty() const noexcept { return m_size == 0; }

   reference front() noexcept { return m_store[0]; }
   reference back() noexcept { return m_store[m_size - 1]; }

   void push_back(const T &value)
   {
      if (m_size == m_capacity)
         realloc();
      m_store[m_size++] = value;
   }

   void pop_back()
   {
      m_size = empty() ? 0 : m_size - 1;
   }

   void resize(size_t count)
   {
      c_vector tmp(count);
      std::copy(m_store,
                m_store + (count > m_size ? m_size : count),
                tmp.m_store);
      swap(*this, tmp);
   }

   void resize(size_t count, const T &value)
   {
      c_vector tmp(count, value);
      std::copy(m_store,
                m_store + (count > m_size ? m_size : count),
                tmp.m_store);
      swap(*this, tmp);
   }

   iterator begin() { return &m_store[0]; }
   const_iterator begin() const { return &m_store[0]; }
   iterator end() { return &m_store[m_size]; }
   const_iterator end() const { return &m_store[m_size]; }

   friend void swap(c_vector &first, c_vector &second) noexcept
   {
      using std::swap;

      swap(first.m_size, second.m_size);
      swap(first.m_capacity, second.m_capacity);
      swap(first.m_store, second.m_store);
   }
};

// CTAD idiom
template <typename T>
c_vector(std::initializer_list<T>) -> c_vector<T>;
template <typename T>
c_vector(const c_vector<T> &other) -> c_vector<T>;
template <typename T>
c_vector(c_vector<T> &&other) -> c_vector<T>;

#pragma pack(pop)

#endif //C_VECTOR_HPP