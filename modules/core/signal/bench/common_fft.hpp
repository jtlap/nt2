//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//         Copyright 2012          Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef COMMON_FFT_INCLUDED
#define COMMON_FFT_INCLUDED

#include <nt2/sdk/unit/details/prng.hpp>
#include <boost/simd/memory/allocator.hpp>

#ifdef __APPLE__
#include <boost/simd/include/functions/scalar/ilog2.hpp>
#include "Accelerate/Accelerate.h" //vDSP.h
#endif

#ifdef _WIN32
#include "windows.h"
#endif

#include <cstdlib>
#include <cstdio>
#include <vector>

#if defined( BOOST_SIMD_HAS_LRB_SUPPORT ) || defined( BOOST_SIMD_HAS_AVX_SUPPORT )
typedef double T;
#else //...zzz...cardinal-must-be-4 limitation...
typedef float T;
#endif

namespace constants
{
  static std::size_t const minimum_dft_log = 5;
  static std::size_t const maximum_dft_log = 14;

  static std::size_t const minimum_dft_size = 1 << minimum_dft_log;
  static std::size_t const maximum_dft_size = 1 << maximum_dft_log;

  static T const test_data_range_minimum = -1;
  static T const test_data_range_maximum = +1;
}

typedef std::vector<T, boost::simd::allocator<T> > dynamic_aligned_array;
typedef nt2::static_fft < constants::minimum_dft_size
                        , constants::maximum_dft_size
                        , T>                       FFT;

//==============================================================================
// Base Real FFT Experiment
//==============================================================================
struct real_fft
{
  real_fft( std::size_t n )
          : size_(n)
          , real_time_data_(size_)
          , real_frequency_data_(size_/2+1)
          , imag_frequency_data_(size_/2+1)
  {
    nt2::roll ( real_frequency_data_
              , constants::test_data_range_minimum
              , constants::test_data_range_maximum
              );

    nt2::roll ( imag_frequency_data_
              , constants::test_data_range_minimum
              , constants::test_data_range_maximum
              );
  }

  std::size_t size() const { return size_; }

  friend std::ostream& operator<<(std::ostream& os, real_fft const& p)
  {
    return os << "(" << p.size_ << ")";
  }

  std::size_t           size_;
  dynamic_aligned_array real_time_data_;
  dynamic_aligned_array real_frequency_data_;
  dynamic_aligned_array imag_frequency_data_;
};

//==============================================================================
// Base Complex FFT experiment
//==============================================================================
struct complex_fft
{
  complex_fft ( std::size_t n )
              : size_(n)
              , real_data_(size_)
              , imag_data_(size_)
  {
    nt2::roll ( real_data_
              , constants::test_data_range_minimum
              , constants::test_data_range_maximum
              );

    nt2::roll ( imag_data_
              , constants::test_data_range_minimum
              , constants::test_data_range_maximum
              );
  }

  std::size_t size() const { return size_*2; }

  friend std::ostream& operator<<(std::ostream& os, complex_fft const& p)
  {
    return os << "(" << p.size_ << ")";
  }

  std::size_t           size_;
  dynamic_aligned_array real_data_;
  dynamic_aligned_array imag_data_;
};

#ifdef __APPLE__
//==============================================================================
// Base Apple vDSP Complex FFT experiment
//==============================================================================
FFTSetup fft_instance_ = 0;

struct apple_fft
{
  apple_fft( std::size_t n )
           : log2length_( boost::simd::ilog2( n ) )
  {
  }

  std::size_t log2length() const  { return log2length_  ; }
  std::size_t log2length_;
};

//==============================================================================
// Base Apple vDSP Real FFT experiment
//==============================================================================
struct apple_real_fft : public apple_fft, public real_fft
{
  apple_real_fft( std::size_t n ) : apple_fft(n), real_fft(n) {}

  DSPSplitComplex split_data()
  {
    DSPSplitComplex complex_data =  { &real_frequency_data_[0]
                                    , &imag_frequency_data_[0]
                                    };
    return complex_data;
  }
};

#endif

#endif
