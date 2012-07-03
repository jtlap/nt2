//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012          Domagoj Saric, Little Endian Ltd.
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

#include <boost/array.hpp>
#include <boost/assert.hpp>
#include <boost/foreach.hpp>

#ifdef __APPLE__
    // FIXME: this requires "-framework Accelerate" to be added to linker flags
    #include "Accelerate/Accelerate.h" //vDSP.h
#endif // __APPLE__


NT2_TEST_CASE( test )
{
    static const std::size_t N = 4096;
    typedef float T;
    typedef BOOST_SIMD_ALIGN_ON( BOOST_SIMD_ARCH_ALIGNMENT ) boost::array<T, N> aligned_array;
    typedef nt2::static_fft<128, 8192, T> FFT;

    // Test complex transform(s):
    {
        aligned_array real_data;
        aligned_array imag_data;

        BOOST_FOREACH( T & scalar, real_data ) { scalar = roll<T>( -1, 1 ); }
        BOOST_FOREACH( T & scalar, imag_data ) { scalar = roll<T>( -1, 1 ); }

        aligned_array const original_real_data( real_data );
        aligned_array const original_imag_data( imag_data );

        FFT::forward_transform( &real_data[ 0 ], &imag_data[ 0 ], N );
        FFT::inverse_transform( &real_data[ 0 ], &imag_data[ 0 ], N );

        T const norm( nt2::complex_fft_normalization_factor<T>( N ) );
        BOOST_FOREACH( T & scalar, real_data ) { scalar *= norm; }
        BOOST_FOREACH( T & scalar, imag_data ) { scalar *= norm; }

        for ( std::size_t i( 0 ); i != N; ++i )
        {
            NT2_TEST_ULP_EQUAL( real_data[ i ], original_real_data[ i ], 1000 );
            NT2_TEST_ULP_EQUAL( imag_data[ i ], original_imag_data[ i ], 1000 );
        }


    #ifdef __APPLE__
        { // Accelerate framework FFT
            real_data = original_real_data;
            imag_data = original_imag_data;

            FFTSetup const fft_instance( vDSP_create_fftsetup( boost::static_log2<N>::value, kFFTRadix2 ) );
            BOOST_ASSERT( fft_instance );
            DSPSplitComplex complex_data = { &real_data[ 0 ], &imag_data[ 0 ] };
            vDSP_fft_zip( fft_instance, &complex_data, 1, boost::static_log2<N>::value, FFT_FORWARD );
            vDSP_fft_zip( fft_instance, &complex_data, 1, boost::static_log2<N>::value, FFT_INVERSE );
            vDSP_destroy_fftsetup( fft_instance );

            T const norm( static_cast<T>( 1 ) / N );
            BOOST_FOREACH( T & scalar, real_data ) { scalar *= norm; }
            BOOST_FOREACH( T & scalar, imag_data ) { scalar *= norm; }

            for ( std::size_t i( 0 ); i != N; ++i )
            {
                NT2_TEST_ULP_EQUAL( real_data[ i ], original_real_data[ i ], 1000 );
                NT2_TEST_ULP_EQUAL( imag_data[ i ], original_imag_data[ i ], 1000 );
            }
        }
    #endif // __APPLE__
    }

    // Test real transform(s):
    {
        aligned_array real_time_data;
        BOOST_FOREACH( T & scalar, real_time_data ) { scalar = roll<T>( -1, 1 ); }

        aligned_array real_frequency_data;
        aligned_array imag_frequency_data;
        FFT::real_forward_transform( &real_time_data[ 0 ], &real_frequency_data[ 0 ], &imag_frequency_data[ 0 ], N );

        aligned_array real_time_data2;
        FFT::real_inverse_transform( &real_frequency_data[ 0 ], &imag_frequency_data[ 0 ], &real_time_data2[ 0 ], N );

        T const norm( nt2::real_fft_normalization_factor<T>( N ) );
        BOOST_FOREACH( T & scalar, real_time_data2 ) { scalar *= norm; }

        for ( std::size_t i( 0 ); i != N; ++i )
            NT2_TEST_ULP_EQUAL( real_time_data[ i ], real_time_data2[ i ], 1000 );


    #ifdef __APPLE__
        { // Accelerate framework FFT
            FFTSetup const fft_instance( vDSP_create_fftsetup( boost::static_log2<N>::value, kFFTRadix2 ) );
            BOOST_ASSERT( fft_instance );
            aligned_array split_real_data_storage;
            DSPSplitComplex split_real_data =
            {
                &split_real_data_storage[ 0     ],
                &split_real_data_storage[ N / 2 ]
            };
            vDSP_ctoz    ( reinterpret_cast<DSPComplex const *>( &real_time_data[ 0 ] ), 2, &split_real_data, 1, N / 2 );
            vDSP_fft_zrip( fft_instance, &split_real_data, 1, boost::static_log2<N>::value, FFT_FORWARD );
            vDSP_fft_zrip( fft_instance, &split_real_data, 1, boost::static_log2<N>::value, FFT_INVERSE );
            vDSP_ztoc    ( &split_real_data, 1, reinterpret_cast<DSPComplex *>( &real_time_data2[ 0 ] ), 2, N / 2 );
            vDSP_destroy_fftsetup( fft_instance );

            T const norm( static_cast<T>( 1 ) / ( 2 * N ) );
            BOOST_FOREACH( T & scalar, real_time_data2 ) { scalar *= norm; }

            for ( std::size_t i( 0 ); i != N; ++i )
                NT2_TEST_ULP_EQUAL( real_time_data[ i ], real_time_data2[ i ], 1000 );
        }
    #endif // __APPLE__
    }
}
