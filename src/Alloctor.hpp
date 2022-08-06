// https://en.cppreference.com/w/cpp/named_req/Allocator
#pragma once

#include <cstdlib>
#include <new>
#include <limits>
#include <iostream>
#include <vector>

#if defined(ESP_PLATFORM)
#include "esp_heap_caps.h"
#endif

namespace FEmbed 
{
template <class T>
struct Eallocator
{
  typedef T value_type;
 
  Eallocator () = default;
  template <class U> constexpr Eallocator (const Eallocator <U>&) noexcept {}
  
  static Eallocator<T> &get() {
    static Eallocator<T> instance;
    return instance;
  }

  [[nodiscard]] T* allocate(std::size_t n) {
  #if defined(ESP_PLATFORM)
    return static_cast<T*>(heap_caps_malloc(n*sizeof(T), MALLOC_CAP_SPIRAM));
  #else
    return static_cast<T*>(std::malloc(n*sizeof(T));    
  #endif
  }
 
  void deallocate(T* p, std::size_t n) noexcept {
    std::free(p);
  }
};
 
template <class T, class U>
bool operator==(const Eallocator <T>&, const Eallocator <U>&) { return true; }
template <class T, class U>
bool operator!=(const Eallocator <T>&, const Eallocator <U>&) { return false; }

}