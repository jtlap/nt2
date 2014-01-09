//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/aligned_store.hpp>
#include <boost/simd/include/functions/aligned_load.hpp>
#include <boost/simd/include/functions/store.hpp>
#include <boost/simd/include/functions/stream.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <boost/simd/include/native.hpp>
#include <vector>
#include <cstring>

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/unit/details/prng.hpp>
#include <nt2/sdk/bench/metric/gb_per_second.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/setup/fixed.hpp>
#include <nt2/sdk/bench/stat/median.hpp>
#include <nt2/sdk/bench/stat/min.hpp>
#include <nt2/sdk/bench/stat/max.hpp>

using namespace nt2::bench;

//==============================================================================
// memcpy bandwidth benchmark
//==============================================================================
template<typename T>
struct memcpy_bandwidth
{
  public:
  memcpy_bandwidth( std::size_t s = 0 )
                  : size_(s/sizeof(T))
                  , out(size_), in(size_)
  {}

  void operator()()
  {
    std::memcpy(&out[0], &in[0], size_*sizeof(T));
  }

  std::size_t size() const { return size_*sizeof(T); }

  private:
  std::size_t                                 size_;
  std::vector<T, boost::simd::allocator<T> >  out,in;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, memcpy_bandwidth<T> const& p)
{
  return os << "(" << p.size() << ")";
}

NT2_REGISTER_BENCHMARK_TPL( memcpy_bandwidth, BOOST_SIMD_SIMD_TYPES )
{
  std::size_t bytes = args("bytes", 1<<20 );

  run_during_with< memcpy_bandwidth<T> >( 3.
                                        , fixed(bytes)
                                        , gb_per_second<stat::min_>(2)
                                        , gb_per_second<stat::median_>(2)
                                        , gb_per_second<stat::max_>(2)
                                        );
}


//==============================================================================
// raw C bandwidth benchmark
//==============================================================================
template<typename T>
struct C_bandwidth
{
  public:
  C_bandwidth ( std::size_t s = 0 )
              : size_(s/sizeof(T)), out(size_), in(size_)
  {}

  void operator()()
  {
    for( std::size_t i=0; i<size_; ++i)
    {
      out[i] = in[i];
    }
  }

  std::size_t size() const { return size_*sizeof(T); }

  private:
  std::size_t                                 size_;
  std::vector<T, boost::simd::allocator<T> >  out,in;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, C_bandwidth<T> const& p)
{
  return os << "(" << p.size() << ")";
}

NT2_REGISTER_BENCHMARK_TPL( C_bandwidth, BOOST_SIMD_SIMD_TYPES )
{
  std::size_t bytes = args("bytes", 1<<20 );

  run_during_with< C_bandwidth<T> > ( 3.
                                    , fixed(bytes)
                                    , gb_per_second<stat::min_>(2)
                                    , gb_per_second<stat::median_>(2)
                                    , gb_per_second<stat::max_>(2)
                                    );
}

//==============================================================================
// SIMD bandwidth benchmark
//==============================================================================
template<typename T>
struct aligned_simd_bandwidth
{
  public:
  typedef boost::simd::native<T,BOOST_SIMD_DEFAULT_EXTENSION> vT;

  aligned_simd_bandwidth( std::size_t s = 0 )
                        : size_(s/sizeof(T))
                        , out(size_), in(size_)
  {}

  void operator()()
  {
    for( std::size_t i=0
       ; i<size_
       ; i+=boost::simd::meta::cardinal_of<vT>::value
       )
   {
     boost::simd::aligned_store( boost::simd::aligned_load<vT>(&in[i])
                               , &out[i]
                               );
   }
  }

  std::size_t size() const { return size_*sizeof(T); }

  private:
  std::size_t                                 size_;
  std::vector<T, boost::simd::allocator<T> >  out,in;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, aligned_simd_bandwidth<T> const& p)
{
  return os << "(" << p.size() << ")";
}

NT2_REGISTER_BENCHMARK_TPL( aligned_simd_bandwidth, BOOST_SIMD_SIMD_TYPES )
{
  std::size_t bytes = args("bytes", 1<<20 );

  run_during_with< aligned_simd_bandwidth<T> >( 3.
                                              , fixed(bytes)
                                              , gb_per_second<stat::min_>(2)
                                              , gb_per_second<stat::median_>(2)
                                              , gb_per_second<stat::max_>(2)
                                              );
}

//==============================================================================
// SIMD unaligned bandwidth benchmark
//==============================================================================
template<typename T>
struct unaligned_simd_bandwidth
{
  public:
  typedef boost::simd::native<T,BOOST_SIMD_DEFAULT_EXTENSION> vT;

  unaligned_simd_bandwidth( std::size_t s = 0 )
                          : size_(s/sizeof(T)), out(size_), in(size_)
  {}

  void operator()()
  {
    for( std::size_t i=0
       ; i<size_
       ; i+=boost::simd::meta::cardinal_of<vT>::value
       )
   {
     boost::simd::store( boost::simd::load<vT>(&in[i]), &out[i] );
   }
  }

  std::size_t size() const { return size_*sizeof(T); }

  private:
  std::size_t     size_;
  std::vector<T>  out,in;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, unaligned_simd_bandwidth<T> const& p)
{
  return os << "(" << p.size() << ")";
}

NT2_REGISTER_BENCHMARK_TPL( unaligned_simd_bandwidth, BOOST_SIMD_SIMD_TYPES )
{
  std::size_t bytes = args("bytes", 1<<20 );

  run_during_with< unaligned_simd_bandwidth<T> >( 3.
                                                , fixed(bytes)
                                                , gb_per_second<stat::min_>(2)
                                                , gb_per_second<stat::median_>(2)
                                                , gb_per_second<stat::max_>(2)
                                                );
}

//==============================================================================
// SIMD non-temporal bandwidth benchmark
//==============================================================================
template<typename T>
struct non_temporal_simd_bandwidth
{
  public:
  typedef boost::simd::native<T,BOOST_SIMD_DEFAULT_EXTENSION> vT;

  non_temporal_simd_bandwidth ( std::size_t s = 0 )
                              : size_(s/sizeof(T)), out(size_), in(size_)
  {}

  void operator()()
  {
    for( std::size_t i=0
       ; i<size_
       ; i+=boost::simd::meta::cardinal_of<vT>::value
       )
   {
     boost::simd::stream( boost::simd::aligned_load<vT>(&in[i]), &out[i] );
   }
  }

  std::size_t size() const { return size_*sizeof(T); }

  private:
  std::size_t     size_;
  std::vector<T, boost::simd::allocator<T> >  out,in;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, non_temporal_simd_bandwidth<T> const& p)
{
  return os << "(" << p.size() << ")";
}

NT2_REGISTER_BENCHMARK_TPL( non_temporal_simd_bandwidth, BOOST_SIMD_SIMD_TYPES )
{
  std::size_t bytes = args("bytes", 1<<20 );

  run_during_with< non_temporal_simd_bandwidth<T> > ( 3.
                                                    , fixed(bytes)
                                                    , gb_per_second<stat::min_>(2)
                                                    , gb_per_second<stat::median_>(2)
                                                    , gb_per_second<stat::max_>(2)
                                                    );
}
