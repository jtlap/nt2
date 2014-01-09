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
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/metric/cycles_per_element.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/metric/absolute_time.hpp>
#include <nt2/sdk/bench/setup/geometric.hpp>
#include <nt2/sdk/bench/stat/median.hpp>
#include <nt2/signal/static_fft.hpp>
#include "common_fft.hpp"

using namespace nt2::bench;

//==============================================================================
// Complex Forward FFT
//==============================================================================
struct fft_forward : complex_fft
{
  fft_forward ( std::size_t n ) : complex_fft(n) {}

  void operator()()
  {
    FFT::forward_transform ( &real_data_[0], &imag_data_[0], size_ );
  }
};

NT2_REGISTER_BENCHMARK( fft_forward )
{
  run_during_with< fft_forward >( 0.6
                                , geometric ( constants::minimum_dft_size
                                            , constants::maximum_dft_size
                                            , 2
                                            )
                                , cycles_per_element<stat::median_>()
                                , absolute_time<stat::median_>()
                                );
}

//==============================================================================
// Complex Inverse FFT
//==============================================================================
struct fft_inverse : complex_fft
{
  fft_inverse ( std::size_t n ) : complex_fft(n) {}

  void operator()()
  {
    FFT::inverse_transform ( &real_data_[0], &imag_data_[0], size_ );
  }
};

NT2_REGISTER_BENCHMARK( fft_inverse )
{
  run_during_with< fft_inverse >( 0.6
                                , geometric ( constants::minimum_dft_size
                                            , constants::maximum_dft_size
                                            , 2
                                            )
                                , cycles_per_element<stat::median_>()
                                , absolute_time<stat::median_>()
                                );
}

//==============================================================================
// Real Forward FFT
//==============================================================================
struct fft_real_forward : real_fft
{
  fft_real_forward( std::size_t n ) : real_fft(n) { }

  void operator()()
  {
    FFT::real_forward_transform ( &real_frequency_data_[0]
                                , &imag_frequency_data_[0]
                                , &real_time_data_[0]
                                , size_
                                );
  }
};

NT2_REGISTER_BENCHMARK( fft_real_forward )
{
  run_during_with< fft_real_forward > ( 0.6
                                      , geometric ( constants::minimum_dft_size
                                                  , constants::maximum_dft_size
                                                  , 2
                                                  )
                                      , cycles_per_element<stat::median_>()
                                      , absolute_time<stat::median_>()
                                      );
}

//==============================================================================
// Real Inverse FFT
//==============================================================================
struct fft_real_inverse : real_fft
{
  fft_real_inverse( std::size_t n ) : real_fft(n) {}

  void operator()()
  {
    FFT::real_inverse_transform ( &real_frequency_data_[0]
                                , &imag_frequency_data_[0]
                                , &real_time_data_[0]
                                , size_
                                );
  }
};

NT2_REGISTER_BENCHMARK( fft_real_inverse )
{
  run_during_with< fft_real_inverse > ( 0.6
                                      , geometric ( constants::minimum_dft_size
                                                  , constants::maximum_dft_size
                                                  , 2
                                                  )
                                      , cycles_per_element<stat::median_>()
                                      , absolute_time<stat::median_>()
                                      );
}

#ifdef __APPLE__

//==============================================================================
// Apple Complex Forward/Inverse FFT
//==============================================================================
template <FFTDirection direction>
class apple_complex_fft : public apple_fft, public complex_fft
{
  public:
  apple_complex_fft( std::size_t n ): apple_fft(n), complex_fft(n) {}

  void operator()()
  {
    DSPSplitComplex complex_data( split_data() );
    ::vDSP_fft_zip( fft_instance_, &complex_data, 1, log2length(), direction );
  }

  DSPSplitComplex split_data()
  {
    DSPSplitComplex complex_data = { &real_data_[0], &imag_data_[0] };
    return complex_data;
  }
};

NT2_REGISTER_BENCHMARK( apple_fft_forward )
{
  fft_instance_  = ::vDSP_create_fftsetup( constants::maximum_dft_log, kFFTRadix2 );

  run_during_with< apple_complex_fft<FFT_FORWARD> >
                                    ( 0.6
                                    , geometric ( constants::minimum_dft_size
                                                , constants::maximum_dft_size
                                                , 2
                                                )
                                    , cycles_per_element<stat::median_>()
                                    , absolute_time<stat::median_>()
                                    );

  ::vDSP_destroy_fftsetup( fft_instance_ );
}

NT2_REGISTER_BENCHMARK( apple_fft_inverse )
{
  fft_instance_  = ::vDSP_create_fftsetup( constants::maximum_dft_log, kFFTRadix2 );

  run_during_with< apple_complex_fft<FFT_INVERSE> >
                                    ( 0.6
                                    , geometric ( constants::minimum_dft_size
                                                , constants::maximum_dft_size
                                                , 2
                                                )
                                    , cycles_per_element<stat::median_>()
                                    , absolute_time<stat::median_>()
                                    );

  ::vDSP_destroy_fftsetup( fft_instance_ );
}

//==============================================================================
// Apple Real Forward FFT
//==============================================================================
class apple_real_forward_fft : public apple_real_fft
{
  public:
  apple_real_forward_fft( std::size_t n ) : apple_real_fft(n) {}

  void operator()()
  {
    DSPSplitComplex split_real_data( split_data() );
    vDSP_ctoz( reinterpret_cast<DSPComplex const*>( &real_time_data_[0]), 2
                                                  , &split_real_data, 1, size_/2
                                                  );

    vDSP_fft_zrip( fft_instance_, &split_real_data, 1, log2length(), FFT_FORWARD );
  }
};

NT2_REGISTER_BENCHMARK( apple_fft_real_forward )
{
  fft_instance_  = ::vDSP_create_fftsetup( constants::maximum_dft_log, kFFTRadix2 );

  run_during_with< apple_real_forward_fft > ( 0.6
                                            , geometric ( constants::minimum_dft_size
                                                        , constants::maximum_dft_size
                                                        , 2
                                                        )
                                            , cycles_per_element<stat::median_>()
                                            , absolute_time<stat::median_>()
                                            );

  ::vDSP_destroy_fftsetup( fft_instance_ );
}

//==============================================================================
// Apple Real Inverse FFT
//==============================================================================
class apple_real_inverse_fft : public apple_real_fft
{
  public:
  apple_real_inverse_fft( std::size_t n ) : apple_real_fft(n) {}

  void operator()()
  {
    DSPSplitComplex split_real_data( split_data() );
    vDSP_fft_zrip( fft_instance_, &split_real_data, 1, log2length(), FFT_INVERSE );
    vDSP_ztoc ( &split_real_data, 1
              , reinterpret_cast<DSPComplex *>( &real_time_data_[0] ), 2
              , size_/2
              );
  }
};

NT2_REGISTER_BENCHMARK( apple_fft_real_inverse )
{
  fft_instance_  = ::vDSP_create_fftsetup( constants::maximum_dft_log, kFFTRadix2 );

  run_during_with< apple_real_inverse_fft > ( 0.6
                                            , geometric ( constants::minimum_dft_size
                                                        , constants::maximum_dft_size
                                                        , 2
                                                        )
                                            , cycles_per_element<stat::median_>()
                                            , absolute_time<stat::median_>()
                                            );

  ::vDSP_destroy_fftsetup( fft_instance_ );
}

#endif
