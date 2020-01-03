#ifndef __NONCOPYABLE_HPP__
#define __NONCOPYABLE_HPP__

class noncopyable {
  noncopyable(const noncopyable&) = delete;
  void operator=(const noncopyable&) = delete;

public:
  noncopyable() = default;
};

#endif
