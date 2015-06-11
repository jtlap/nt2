//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <boost/simd/sdk/simd/algorithm.hpp>
#include <boost/simd/include/functions/sqrt.hpp>
#include <boost/simd/memory/allocator.hpp>

#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/unit/details/prng.hpp>
#include <nt2/sdk/bench/metric/cycles_per_element.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/setup/fixed.hpp>
#include <nt2/sdk/bench/stats/median.hpp>
#include <nt2/sdk/bench/stats/min.hpp>
#include <nt2/sdk/bench/stats/max.hpp>


#define BOOST_SIMD_FLOAT_DOUBLE (float)(double)

using namespace nt2::bench;

struct op_functor {
  template <typename U>
  BOOST_FORCEINLINE U operator()(U v) {
    return boost::simd::sqrt(v);
  }
};

template<typename T, typename Alloc = boost::simd::allocator<T>, bool force_unaligned = false>
struct transform_base
{
  typedef void experiment_is_immutable;

  std::size_t extra_size_ = force_unaligned ? 1 : 0;

  public:
  public:
  transform_base( std::size_t s = 0 )
                : size_(s) // Do not add `extra_size_` here
                , out(size_ + extra_size_), in(size_ + extra_size_)
  {
    // Just populate with random values
    std::srand(10);
    std::transform(in.begin(), in.end(), in.begin(), [](T) { return std::rand(); });
  }

  std::size_t size() const { return size_; } // Do not add `extra_size_` here

  protected:
  std::size_t                                 size_;
  std::vector<T, Alloc>  out,in;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, transform_base<T> const& p)
{
  return os << "(" << p.size() << ")";
}

//==============================================================================
// raw C transform benchmark
//==============================================================================
template<typename T>
struct C_transform : public transform_base<T>
{
  using transform_base<T>::transform_base;

  void operator()()
  {
      auto f = op_functor();
      auto iit = this->in.begin();
      auto oit = this->out.begin();
      for (; iit != this->in.end(); ++iit, ++oit) {
          *oit = f(*iit);
      }
  }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, C_transform<T> const& p)
{
  return os << "(" << p.size() << ")";
}

NT2_REGISTER_BENCHMARK_TPL( C_transform, BOOST_SIMD_FLOAT_DOUBLE )
{
  std::size_t bytes = args("bytes", 1<<20 );

  run_during_with< C_transform<T> >( 3.
                                   , fixed(bytes)
                                   , cycles_per_element<stats::min_>()
                                   , cycles_per_element<stats::median_>()
                                   , cycles_per_element<stats::max_>()
                                   );
}

//==============================================================================
// std::transform benchmark
//==============================================================================
template<typename T>
struct std_transform : public transform_base<T>
{
  using transform_base<T>::transform_base;

  void operator()()
  {
      std::transform(this->in.begin(), this->in.end(), this->out.begin(), op_functor());
  }
};

NT2_REGISTER_BENCHMARK_TPL( std_transform, BOOST_SIMD_FLOAT_DOUBLE )
{
  std::size_t bytes = args("bytes", 1<<20 );

  run_during_with< std_transform<T> >( 3.
                                     , fixed(bytes)
                                     , cycles_per_element<stats::min_>()
                                     , cycles_per_element<stats::median_>()
                                     , cycles_per_element<stats::max_>()
                                     );
}

//==============================================================================
// boost::simd::transform benchmark (unaligned)
//==============================================================================
template<typename T>
struct unaligned_simd_transform : public transform_base<T, std::allocator<T>, true /* force unaligned */ >
{
  using transform_base<T, std::allocator<T>, true>::transform_base;

  void operator()()
  {
      T* ptr_in = this->in.data();

      if (boost::simd::is_aligned(ptr_in, 16)) {
        ptr_in += 1;
      }
      boost::simd::transform(ptr_in, ptr_in + this->size(), this->out.data(), op_functor());
  }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, unaligned_simd_transform<T> const& p)
{
  return os << "(" << p.size() << ")";
}

NT2_REGISTER_BENCHMARK_TPL( unaligned_simd_transform, BOOST_SIMD_FLOAT_DOUBLE )
{
  std::size_t bytes = args("bytes", 1<<20 );

  run_during_with< unaligned_simd_transform<T> >( 3.
                                                , fixed(bytes)
                                                , cycles_per_element<stats::min_>()
                                                , cycles_per_element<stats::median_>()
                                                , cycles_per_element<stats::max_>()
                                                );
}

//==============================================================================
// boost::simd::transform benchmark (aligned)
//==============================================================================
template<typename T>
struct aligned_simd_transform : public transform_base<T>
{
  using transform_base<T>::transform_base;

  void operator()()
  {
      boost::simd::transform(this->in.data(), this->in.data() + this->in.size(), this->out.data(), op_functor());
  }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, aligned_simd_transform<T> const& p)
{
  return os << "(" << p.size() << ")";
}

NT2_REGISTER_BENCHMARK_TPL( aligned_simd_transform, BOOST_SIMD_FLOAT_DOUBLE )
{
  std::size_t bytes = args("bytes", 1<<20 );

  run_during_with< aligned_simd_transform<T> >( 3.
                                              , fixed(bytes)
                                              , cycles_per_element<stats::min_>()
                                              , cycles_per_element<stats::median_>()
                                              , cycles_per_element<stats::max_>()
                                              );
}
