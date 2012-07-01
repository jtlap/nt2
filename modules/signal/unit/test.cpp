//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 signal processing - test"

#include <nt2/signal/static_fft.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/details/helpers.hpp>

#include <boost/simd/sdk/memory/allocator.hpp>

NT2_TEST_CASE( test )
{
  typedef float T;
  typedef nt2::static_fft<128, 8192, T> FFT;
  static const std::size_t N = 4096;

  typedef std::vector<T, boost::simd::memory::allocator<T> > aligned_vector;

  aligned_vector real_time_data(N);
  for(std::size_t i=0; i!=N; ++i)
    real_time_data[i] = roll<T>(0, 1);

  aligned_vector real_frequency_data(N);
  aligned_vector imag_frequency_data(N);
  FFT::real_forward_transform(&real_time_data[0], &real_frequency_data[0], &imag_frequency_data[0], N);

  aligned_vector real_time_data2(N);
  FFT::real_inverse_transform(&real_frequency_data[0], &imag_frequency_data[0], &real_time_data2[0], N);

  for(std::size_t i=0; i!=N; ++i)
    NT2_TEST_ULP_EQUAL( real_time_data[i], real_time_data2[i], 1000 );
}
