#ifndef __BETA_VECTOR_HPP__
#define __BETA_VECTOR_HPP__

#define log_enable false

#include <cstdlib>
#include <exception>
#include <iomanip>
#include <iostream>
#include <noncopyable.hpp>

template <typename T>
class beta_vector : public noncopyable {
  using size_type = size_t;

  size_type m_capacity = 0;
  size_type m_size     = 0;
  T* m_data            = nullptr;

  void log_capacity([[maybe_unused]] const char* const signature);

public:
  explicit beta_vector(size_type init_capacity);

  ~beta_vector() noexcept;

  void reserve(size_type new_size);

  void resize(size_type new_size);

  size_type capacity(void);

  size_type size() const;

  T& at(int idx);

  template <typename... ARGS>
  void emplace_back(ARGS&&... args);
};

template <typename T>
beta_vector<T>::beta_vector(size_type init_capacity) {
  resize(init_capacity);
  log_capacity(__FUNCTION__);
}

template <typename T>
beta_vector<T>::~beta_vector() noexcept {
  if (m_data != nullptr) {
    std::free(m_data);
  }
}

template <typename T>
__attribute__((always_inline)) void beta_vector<T>::reserve(size_type request_capacity) {
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
__attribute__((always_inline)) void beta_vector<T>::resize(size_type new_size) {
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
__attribute__((always_inline)) typename beta_vector<T>::size_type beta_vector<T>::capacity(void) {
  return m_capacity;
}

template <typename T>
__attribute__((always_inline)) typename beta_vector<T>::size_type beta_vector<T>::size(void) const {
  return m_size;
}

template <typename T>
__attribute__((always_inline)) T& beta_vector<T>::at(int idx) {
  return m_data[idx];
}

template <typename T>
template <typename... ARGS>
__attribute__((always_inline)) void beta_vector<T>::emplace_back(ARGS&&... args) {
  reserve(m_size + 1);
  new (m_data + m_size) T(std::forward<ARGS>(args)...);
  m_size++;
}

template <typename T>
void beta_vector<T>::log_capacity([[maybe_unused]] const char* const signature) {
#if log_enable
  std::cout << "[log][" << std::setw(11) << std::left << signature << "] capacity = " << capacity() << std::endl;
#endif
}

#endif
