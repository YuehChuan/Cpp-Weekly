#ifndef __ALLOCATOR_H_
#define __ALLOCATOR_H_

#include <cstdlib>   // std::malloc, std::free
#include <cstring>   // atoi
#include <exception> // throw
#include <iomanip>   // std::setw
#include <iostream>  // std::cout, std::endl;

#include <inc/beta.hpp>

template <class T>
class beta::allocator {
  void log_status(const char* const signature) {
    std::cout << "[log] " << signature << std::endl;
  }

public:
  using value_type = T;
  using size_type  = std::size_t;

  struct rebind {
    using other = allocator<T>;
  };

  allocator() throw() = default;

  allocator(const allocator&) throw() = default;

  ~allocator() throw() = default;

  T* allocate(size_t num_of_object) {
    log_status(__PRETTY_FUNCTION__);
    return static_cast<T*>(operator new(sizeof(T) * num_of_object));
  }

  void deallocate(T* ptr, size_t size) noexcept {
    operator delete(ptr);
    log_status(__PRETTY_FUNCTION__);
  }

  void construct(T* ptr) {
    new ((void*)ptr) T();
    log_status(__PRETTY_FUNCTION__);
  }

  void construct(T* ptr, const T& value) {
    new ((void*)ptr) T(value);
    log_status(__PRETTY_FUNCTION__);
  }

  template <class... Args>
  void construct(T* ptr, Args&&... args) {
    new (ptr) T(std::forward<Args>(args)...);
    log_status(__PRETTY_FUNCTION__);
  }

  void destory(T* ptr) noexcept {
    ptr->~T();
    log_status(__PRETTY_FUNCTION__);
  }
};

#endif
