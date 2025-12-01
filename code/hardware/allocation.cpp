/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2025
 ****
 **** allocation.cpp : general allocation stuff. not used?
 ****
 ****************************************************************/

#include <cstring> // for memcpy

#include <iterator>
using std::ostream_iterator;

#include <iostream>
#include <ranges>
#include <span>
using std::span;
#include <string>
#include <vector>
using std::vector;

#include <numeric>
#include <random>
using std::default_random_engine,std::random_device,std::mt19937,
  std::uniform_real_distribution,std::uniform_int_distribution;

#include <algorithm>
#include <cassert>
#include <format>
using std::format;

#include "allocation.hpp"

/*! Constructor, single thread */
template <typename R>
Cache<R>::Cache( uint64_t stream_cache_in_words,bool trace ) 
  : Cache( stream_cache_in_words,1,trace ) {};

/*! Constructor, indicating how many threads */
template <typename R>
Cache<R>::Cache( uint64_t stream_cache_in_words,int nthreads,bool trace )
  : nstreams(nthreads)
  , stream_cache_in_words(stream_cache_in_words)
  , trace_(trace) { allocate(); };

template <typename R>
void Cache<R>::allocate() {
  auto allocated_size_in_words = padded_stream_cache_in_words()*nstreams;
  allocation_ = reinterpret_cast<R*>
    ( std::aligned_alloc( 4096,allocated_size_in_words*sizeof(R) ) );
  if (!allocation_) throw("Cache allocation failed");
  if (trace_) 
    std::cout << format("check 4k align: {}\n",
			reinterpret_cast<uintptr_t>(allocation_)%4096);
  thecache = std::span( allocation_,allocated_size_in_words );
  #pragma omp parallel for proc_bind(spread)
  for ( uint64_t i=0; i<allocated_size_in_words; ++i )
    thecache[i] = 0;
};

template< typename R >
uint64_t Cache<R>::padded_stream_cache_in_words() const {
  auto alignment_in_words = align_bytes/sizeof(R);
  auto padded_size=stream_cache_in_words;
  if (trace_) std::cout << std::format
		(" .. stream size requested: {}\n",padded_size);
  padded_size += alignment_in_words-1;
  padded_size -= padded_size%alignment_in_words;
  if (trace_) std::cout << std::format
		(" .. padded to: {}\n",padded_size );
  return padded_size;
};

/*! Destructor: de-allocate if you own the data */
template <typename R>
Cache<R>::~Cache() { if (allocation_!=NULL) delete []allocation_; };

/*! Constructor by extracting a stream from a parent */
template <typename R>
std::span<R> Cache<R>::get_stream( int istream) {
  if (istream<0 or istream>=nstreams)
    throw( format("invalid stream number {} out of {}",istream,nstreams) );
  auto stream_offset = istream*padded_stream_cache_in_words();
  if ( stream_offset + stream_cache_in_words> thecache.size() ) {
    std::string error = 
      format("stream end {}+{} beyond cache end {}",
             stream_offset,stream_cache_in_words,thecache.size()
            );
    std::cout << "Get stream error: " << error << '\n';
    throw(error); }
  return std::span
    ( // return an aligned starting point
      thecache.data()+stream_offset,
      // but return the intended size
      stream_cache_in_words );
};

template <typename R>
float Cache<R>::stream_bytes(int stride) {
  return stream_cache_in_words * sizeof(R)/stride; 
};

template <typename R>
void Cache<R>::set( R v ) {
  for ( auto &e : *this )
    e = v;
};

template <typename R>
void Cache<R>::transform_in_place
    ( std::function< void(R&) > f,int stride,int nrepeats ) {
  for ( int irepeat=0; irepeat<nrepeats; irepeat++ ) {
    for ( size_t i=0; i<stream_cache_in_words; i+=stride )
      f( thecache[i] );
  }
};

template <typename R>
void Cache<R>::setrandom( R v ) {
  static random_device rd;
  static std::default_random_engine random_generator{ rd() };
  uniform_real_distribution<R> fraction_dist(0,v);
  for ( auto &e : *this )
    e = v;
};

template <>
void Cache<int>::setrandom( int v ) {
  static random_device rd;
  static std::default_random_engine random_generator{ rd() };
  uniform_int_distribution<int> fraction_dist(0,v);
  for ( auto &e : *this )
    e = v;
};

template< typename R >
R sum_stream( span<R> stream ) {
  if (stream.size()==0)
    throw("unallocated stream in sum");
  R sum{static_cast<R>(0)};
#if 0 
  for ( const auto& e : stream )
    sum += e;
#else
  for ( size_t i=0; i<stream.size(); ++i )
    sum += stream[i];
#endif
  return sum;
};

template <typename R>
R Cache<R>::sumstream(int repeats,size_t length,size_t byte_offset /* =0 default */ ) const {
  R s{0};
  size_t loc_offset = byte_offset/sizeof(R);
  const R *start_point = thecache.data()+loc_offset;
  for (int r=0; r<repeats; r++)
    for (int w=0; w<length; w++)
      s += *( start_point+w ) * r;
  return s;
};

template <typename R>
void Cache<R>::make_linked_list( size_t length,bool random_traversal,bool tracing ) {
  if (random_traversal) {
    vector<R> indices(length);
    std::iota(indices.begin(),indices.end(),0);
    std::random_device r;
    std::mt19937 g(r());
    std::shuffle(indices.begin(), indices.end(), g);
    auto data = thecache;
    for (size_t i=0; i<indices.size(); i++)
      data[i] = indices[i];
    if (tracing) {
      std::cout << "Pointer chasing: ";
      std::copy(indices.begin(), indices.end(),
		ostream_iterator<R>(std::cout, " "));
      std::cout << "\n";
    }
  } else {
    span<R> dataspan( thecache.data(),stream_cache_in_words );
    std::iota(dataspan.begin(),dataspan.end(),1.);
    dataspan.back() = 0.;
  }
};

template <typename R>
R Cache<R>::traversal( size_t n_accesses,R res,bool tracing ) const {
  return res;
};
template <>
int Cache<int>::traversal( size_t n_accesses,int res,bool tracing ) const {
  auto data = thecache;
  for (size_t i=0; i<n_accesses; i++) {
    res = data[res];
    if (tracing)
      std::cout << res << " ";
  }
  if (tracing) std::cout << "\n";
  return res;
};

template <typename R>
void Cache<R>::force() {
  double s{0.};
  for ( auto c : *this )
    s += c;
  if (s<0) std::cout << s;
};

std::string human_size( uint64_t s ) {
  if ( s<1.e3 ) return std::format("{}",static_cast<int>(s));
  else if (s<1.e6 ) return std::format("{}K",static_cast<int>(s*1.e-3));
  else if (s<1.e9 ) return std::format("{}M",static_cast<int>(s*1.e-6));
  else return std::format("{}G",static_cast<int>(s*1.e-9));
  //  return "";
};

std::string kib_size( uint64_t s ) {
  if ( s<1024 )
    return std::format("{}B",static_cast<int>(s));
  s /= 1024;
  if ( s<1024 )
    return std::format("{}KiB",static_cast<int>(s));
  s /= 1024;
  if ( s<1024 )
    return std::format("{}MiB",static_cast<int>(s));
  s /= 1024;
  return std::format("{}GiB",static_cast<int>(s));
  //  return "";
};

template class Cache<int>;
template class Cache<float>;
template class Cache<double>;

template int sum_stream( span<int> );
template float sum_stream( span<float> );
template double sum_stream( span<double> );
