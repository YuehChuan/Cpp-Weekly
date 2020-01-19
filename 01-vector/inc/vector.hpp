/** @file      vector.hpp
 *
 *  @mainpage  vector.hpp
 *
 *  @brief     build your own vector like std::vector from scratch
 *
 *  @author    Gapry
 *
 *  @date      2020
 *
 *  @copyright MIT License
 */

#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#define log_enable false

#include <cstdlib>
#include <exception>
#include <iomanip>
#include <iostream>

#include <inc/beta.hpp>
#include <inc/noncopyable.hpp>

template <typename T>
class beta::vector : public beta::noncopyable {
  using size_type = size_t;

  size_type m_capacity = 0;
  size_type m_size     = 0;
  T* m_data            = nullptr;

  void log_capacity([[maybe_unused]] const char* signature);

public:
  /**
   * @brief ctor
   */
  explicit vector(size_type init_capacity);

  /**
   * @brief dtor
   */
  ~vector() noexcept;

  /**
   * @brief manage the capacity of beta::vector
   */
  void reserve(size_type request_capacity);

  /**
   * @brief manage the size of beta::vector
   */
  void resize(size_type new_size);

  /**
   * @brief return the capacity of beta::vector
   */
  auto capacity() -> size_type;

  /**
   * @brief the size of beta::vector
   */
  [[nodiscard]] auto size() const -> size_type;

  /**
   * @brief access the element of array
   */
  auto at(int idx) -> T&;

  /**
   * @brief use array subscript operator to access the element of array
   */
  auto operator[](int i) -> T&;

  /**
   * @brief return a reference to the last element
   */
  auto back() -> T&;

  /**
   * @brief appends a new element to the end of the container
   */
  template <typename... ARGS>
  void emplace_back(ARGS&&... args);
};

template <typename T>
beta::vector<T>::vector(size_type init_capacity) {
  resize(init_capacity);
  log_capacity(__FUNCTION__);
}

template <typename T>
beta::vector<T>::~vector() noexcept {
  if (m_data != nullptr) {
    std::free(m_data);
  }
}

template <typename T>
__attribute__((always_inline)) void beta::vector<T>::reserve(size_type request_capacity) {
  if (m_capacity >= request_capacity) {
    return;
  }
  auto new_capacity = m_capacity + (m_capacity >> 1);
  if (new_capacity < request_capacity) {
    new_capacity = request_capacity;
  }
  auto* new_chunk = reinterpret_cast<T*>(std::malloc(new_capacity * sizeof(T)));
  try {
    auto* const buff  = new_chunk;
    auto* const begin = m_data;
    auto* const end   = m_data + m_size;
    for (auto *iterator = begin, *bptr = buff; iterator < end; ++iterator, ++bptr) {
      new (bptr) T(std::move(*iterator));
      iterator->~T();
    }
    if (m_data != nullptr) {
      std::free(m_data);
    }
  } catch (...) {
    if (new_chunk != nullptr) {
      std::free(new_chunk);
    }
    throw;
  }
  m_data     = new_chunk;
  m_capacity = new_capacity;
  log_capacity(__FUNCTION__);
}

template <typename T>
__attribute__((always_inline)) void beta::vector<T>::resize(size_type new_size) {
  if (m_size == new_size) {
    return;
  }
  reserve(new_size);
  if (new_size > m_size) {
    auto* const begin = m_data + m_size;
    auto* const end   = m_data + new_size;
    for (auto* iterator = begin; iterator < end; ++iterator) {
      new (iterator) T();
    }
  }
  m_size = new_size;
  log_capacity(__FUNCTION__);
}

template <typename T>
__attribute__((always_inline)) auto beta::vector<T>::capacity() -> typename beta::vector<T>::size_type {
  return m_capacity;
}

template <typename T>
__attribute__((always_inline)) auto beta::vector<T>::size() const -> typename beta::vector<T>::size_type {
  return m_size;
}

template <typename T>
__attribute__((always_inline)) auto beta::vector<T>::at(int idx) -> T& {
  return m_data[idx];
}

template <typename T>
__attribute__((always_inline)) auto beta::vector<T>::operator[](int idx) -> T& {
  return at(idx);
}

template <typename T>
__attribute__((always_inline)) auto beta::vector<T>::back() -> T& {
  return at(m_size - 1);
}

template <typename T>
template <typename... ARGS>
__attribute__((always_inline)) void beta::vector<T>::emplace_back(ARGS&&... args) {
  reserve(m_size + 1);
  new (m_data + m_size) T(std::forward<ARGS>(args)...);
  m_size++;
}

template <typename T>
void beta::vector<T>::log_capacity([[maybe_unused]] const char* const signature) {
#if log_enable
  std::cout << "[log][" << std::setw(11) << std::left << signature << "] capacity = " << capacity() << std::endl;
#endif
}

#endif
