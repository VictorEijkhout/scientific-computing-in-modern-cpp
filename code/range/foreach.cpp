/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2023 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** foreach.cpp : an iterator that can be ranged
 ****
 ****************************************************************/

#include <cstddef>
#include <algorithm>
#include <functional>
#include <ranges>
#include <utility>

template <typename R>
class Cache {
private:
  R* thecache;
  size_t cachesize_in_words{4096};
public:
  Cache( size_t cachesize_in_words )
    : cachesize_in_words(cachesize_in_words) {
    thecache = new R[cachesize_in_words]; };
  ~Cache() { delete []thecache; }; // new[] => delete[] with brackets!
                                   // Don't forget the https://en.cppreference.com/w/cpp/language/rule_of_three
  R* data() { return thecache; };
public:
  class iter {
  private:
    R* seek{0};
  public:
    iter(R* s) : seek(s) {};
    iter& operator++() { seek++; return *this; };
    iter operator++(int i) { return std::exchange( *this,operator++() ); };
    //    iter operator++(int i) { iter tmp(*this); operator++(); return tmp; };

    // typedefs
    using iterator_category = std::forward_iterator_tag; // for completeness
    using value_type = R; // std::iter_value_t required by std::indirectly_readable <= std::input_iterator <= std::input_range
    using difference_type = std::ptrdiff_t; // for completeness
    using pointer = R*; // for completeness
    using reference = R&; // for completeness

    iter() = default; // std::default_initializable required by std::semiregular <= std::sentinel_for

    R& operator*() const { return *seek; }; // const, required by std::indirectly_readable <= std::input_iterator <= std::input_range
    bool operator==( const iter& other ) const { return seek==other.seek; }; // const, required by std::equality_comparable <= std::sentinel_for
    ptrdiff_t operator-( const iter& other ) const { return seek-other.seek; }; // const also added, not required for an std::input_iterator, but needed for OpenMP
  };
  iter begin() { return iter(thecache); };
  iter end() { return iter(thecache+cachesize_in_words); };
  void transform_in_place( std::function< void(R&) > f ) {
    static_assert(std::ranges::input_range<Cache<R>>);
    static_assert(std::input_iterator<Cache<R>::iter>);
    static_assert(std::sentinel_for<iter, Cache<R>::iter>);
    std::ranges::for_each( *this,f );
  };
};

int main() {
  Cache<float> memory(4096);
  memory.transform_in_place( [](float &x){ x+=1.f; } );
  return 0;
}
