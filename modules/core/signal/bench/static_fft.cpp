//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012          Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_BENCH_MODULE "nt2 signal processing with Boost.SIMD - test"

#include <nt2/signal/static_fft.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/details/helpers.hpp>
#include <nt2/sdk/unit/perform_benchmark.hpp>

#include <boost/simd/sdk/memory/allocator.hpp>

#include <boost/array.hpp>
#include <boost/assert.hpp>
#include <boost/foreach.hpp>
#include <boost/noncopyable.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>

 
namespace bench
{
    namespace constants
    {
        static std::size_t const minimum_dft_size = 128 ;
        static std::size_t const maximum_dft_size = 8192;
        static std::size_t const test_dft_size    = 4096;

        static int const test_data_range_minimum = -1;
        static int const test_data_range_maximum = +1;
    }

    static std::size_t const N = constants::test_dft_size;
    #if defined( BOOST_SIMD_HAS_LRB_SUPPORT ) || defined( BOOST_SIMD_HAS_AVX_SUPPORT )
        typedef double T;
    #else //...zzz...cardinal-must-be-4 limitation...
        typedef float T;
    #endif // BOOST_SIMD_HAS_LRB_SUPPORT || BOOST_SIMD_HAS_AVX_SUPPORT

    typedef BOOST_SIMD_ALIGN_ON( BOOST_SIMD_ARCH_ALIGNMENT ) boost::array<T, N      > aligned_array;
    typedef BOOST_SIMD_ALIGN_ON( BOOST_SIMD_ARCH_ALIGNMENT ) boost::array<T, N/2 + 1> aligned_half_complex_array;
    typedef nt2::static_fft<constants::minimum_dft_size, constants::maximum_dft_size, T> FFT;

    template <class Range>
    void randomize( Range & data )
    {
        /// \note Portably reproducible pseudo "random" values.
        ///                                   (24.07.2012.) (Domagoj Saric)
        boost::random::mt19937                            prng        ( 42                                                                     );
        boost::random::uniform_real_distribution<T> const distribution( constants::test_data_range_minimum, constants::test_data_range_maximum );
        BOOST_FOREACH( T & scalar, data )
            scalar = distribution( prng );
    }

    struct test_fft_forward : boost::noncopyable
    {
        test_fft_forward() { reset(); }

        void operator()() const { FFT::forward_transform( &real_data[ 0 ], &imag_data[ 0 ], N ); }

        void reset()
        {
            randomize( real_data );
            randomize( imag_data );
        }

        mutable aligned_array real_data;
        mutable aligned_array imag_data;
    };

    struct test_fft_inverse : boost::noncopyable
    {
        test_fft_inverse() { reset(); }

        void operator()() const { FFT::inverse_transform( &real_data[ 0 ], &imag_data[ 0 ], N ); }

        void reset()
        {
            randomize( real_data );
            randomize( imag_data );
        }

        mutable aligned_array real_data;
        mutable aligned_array imag_data;
    };

    struct test_fft_real_forward : boost::noncopyable
    {
        test_fft_real_forward() { randomize( real_time_data ); }

        void operator()() const
        { 
            FFT::real_forward_transform( &real_time_data[ 0 ], &real_frequency_data[ 0 ], &imag_frequency_data[ 0 ], N );
        }

        static void reset() {}

                aligned_array              real_time_data     ;
        mutable aligned_half_complex_array real_frequency_data;
        mutable aligned_half_complex_array imag_frequency_data;
    };

    struct test_fft_real_inverse : boost::noncopyable
    {
        test_fft_real_inverse() { reset(); }

        void operator()() const
        {
            FFT::real_inverse_transform( &real_frequency_data[ 0 ], &imag_frequency_data[ 0 ], &real_time_data[ 0 ], N );
        }

        void reset()
        {
            /// \note FFT::real_inverse_transform destroys input data so it has
            /// to be regenerated.
            ///                               (10.10.2012.) (Domagoj Saric)
            randomize( real_frequency_data );
            randomize( imag_frequency_data );
        }

        mutable aligned_half_complex_array real_frequency_data;
        mutable aligned_half_complex_array imag_frequency_data;
        mutable aligned_array              real_time_data     ;
    };

    void do_test()
    {
        std::cout.precision(3);
        std::cout << "test_dft_size : " << N <<"\n";
        std::cout << "forward_transform" <<"\n";
      {
        nt2::unit::benchmark_result<nt2::details::cycles_t> dv;
        nt2::unit::benchmark_result<double> tv;
        test_fft_forward tff;
        nt2::unit::perform_benchmark( tff, 1., dv);
        nt2::unit::perform_benchmark( tff, 1., tv);
        std::cout << std::scientific << dv.median/tff.real_data.size() << "\t";
        std::cout << std::scientific << tv.median << "\n";
      }
      {
        std::cout << "inverse_transform" <<"\n";
        nt2::unit::benchmark_result<nt2::details::cycles_t> dv;
        nt2::unit::benchmark_result<double> tv;
        test_fft_inverse tfi;
        nt2::unit::perform_benchmark( tfi, 1., dv);
        nt2::unit::perform_benchmark( tfi, 1., tv);
        std::cout << std::scientific << dv.median/tfi.real_data.size() << "\t";
        std::cout << std::scientific << tv.median << "\n";
      }
      {
        std::cout << "real_forward_transform" <<"\n";
        nt2::unit::benchmark_result<nt2::details::cycles_t> dv;
        nt2::unit::benchmark_result<double> tv;
        test_fft_real_forward tfrf;
        nt2::unit::perform_benchmark( tfrf, 1., dv);
        nt2::unit::perform_benchmark( tfrf, 1., tv);
        std::cout << std::scientific << dv.median/tfrf.real_frequency_data.size() << "\t";
        std::cout << std::scientific << tv.median << "\n";
      }
      {
        std::cout << "real_inverse_transform" <<"\n";
        nt2::unit::benchmark_result<nt2::details::cycles_t> dv;
        nt2::unit::benchmark_result<double> tv;
        test_fft_real_inverse tfri;
        nt2::unit::perform_benchmark( tfri, 0.5, dv);
        nt2::unit::perform_benchmark( tfri, 0.5, tv);
        std::cout << std::scientific << dv.median/tfri.real_time_data.size() << "\t";
        std::cout << std::scientific << tv.median << "\n";
      }
    }
}

NT2_TEST_CASE( test_fft )
{
    bench::do_test();
}
