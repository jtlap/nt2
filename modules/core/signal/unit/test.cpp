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
#include <boost/simd/sdk/memory/aligned_array.hpp>
#include <boost/array.hpp>
#include <boost/assert.hpp>
#include <boost/foreach.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>

#ifdef __APPLE__
    #include "Accelerate/Accelerate.h" //vDSP.h
#endif // __APPLE__

#include <fstream>
#include <vector>


namespace
{
    namespace constants
    {
        static std::size_t const minimum_dft_size = 128 ;
        static std::size_t const maximum_dft_size = 8192;
        static std::size_t const test_dft_size    = 4096;

        static int const test_data_range_minimum = -1;
        static int const test_data_range_maximum = +1;

        /// \todo The maximum error values should be made dependent on the:
        ///  - value type (float, double, ...)
        ///  - size of the transform
        ///  - transform type (complex, real-through-complex, pure real)
        ///  - used algorithm or more precisely, its arithmetic operation count
        ///    (currently this is the split-radix algorithm)
        ///  - used complex multiplication implementation (2 multiplies + 4
        ///    additions or 3 multiplies + 3 additions) and whether FMA is used
        ///  (see the "accuracy/precision" links in static_fft.hpp).
        ///                                   (17.07.2012.) (Domagoj Saric)

        /// \todo More extensive testing:
        ///  - test multiple sizes (requires the above theoretical-limit
        ///    function)
        ///  - log/graph our actual error "response" ( f_err( N ) )
        ///  - consider/investigate maximum allowed average ULPD thresholds
        ///  - forward complex transform of real data (result must be conjugated
        ///    symmetric)
        ///  - inverse complex transform of conjugated symmetric data (result
        ///    must be pure real
        ///  - http://en.wikipedia.org/wiki/Parseval's_theorem test
        ///  - more fixed/predefined test vectors which have known/expected
        ///    results/transforms (like sawtooth, pulse, sines...)
        ///                                   (19.07.2012.) (Domagoj Saric)

        /// \todo Investigate why testing with NDEBUG defined gives much better
        /// results (on MSVC10). Without NDEBUG MSVC10, Clang3 and GCC 4.x give
        /// exactly the same results.
        ///                                   (24.07.2012.) (Domagoj Saric)

        static unsigned int const maximum_allowed_complex_nt2_ulpd   = 1030;
#if defined(BOOST_SIMD_ARCH_X86) && !defined(BOOST_SIMD_HAS_FMA4_SUPPORT)
        static unsigned int const maximum_allowed_real_nt2_ulpd      =  580;
#else
        static unsigned int const maximum_allowed_real_nt2_ulpd      = 1290;
#endif

        static unsigned int const maximum_allowed_complex_apple_ulpd = 1290;
        static unsigned int const maximum_allowed_real_apple_ulpd    =  770;
    } // namespace constants

    static std::size_t const N = constants::test_dft_size;
    #if 0 //defined( BOOST_SIMD_HAS_LRB_SUPPORT ) || defined( BOOST_SIMD_HAS_AVX_SUPPORT )
        typedef double T;
    #else //...zzz...cardinal-must-be-4 limitation...
        typedef float T;
    #endif // BOOST_SIMD_HAS_LRB_SUPPORT || BOOST_SIMD_HAS_AVX_SUPPORT
    typedef boost::simd::memory::aligned_array<T, N, BOOST_SIMD_CONFIG_ALIGNMENT> aligned_array;
    typedef boost::simd::memory::aligned_array<T, N/2 + 1, BOOST_SIMD_CONFIG_ALIGNMENT> aligned_half_complex_array;
    typedef nt2::static_fft<constants::minimum_dft_size, constants::maximum_dft_size, T> FFT;

    void randomize( aligned_array & data )
    {
        /// \note Portably reproducible pseudo "random" values.
        ///                                   (24.07.2012.) (Domagoj Saric)
        boost::random::mt19937                            prng        ( 42                                                                     );
        boost::random::uniform_real_distribution<T> const distribution( constants::test_data_range_minimum, constants::test_data_range_maximum );
        BOOST_FOREACH( T & scalar, data )
            scalar = distribution( prng );
    }

    void scale( aligned_array & data, T const scale_factor )
    {
        BOOST_FOREACH( T & scalar, data ) { scalar *= scale_factor; }
    }

    struct failed_value_t
    {
        T           value        ;
        T           desired_value;
        T           ulp_error    ;
        std::size_t index        ;
    };

    std::vector<failed_value_t> failed_values;

    //#define NT2_PSIHA_AUX_TESTING
#ifdef NT2_PSIHA_AUX_TESTING
    std::ofstream outputfile_aux( "nt_fft_test.log", std::ios_base::out | std::ios_base::trunc );
    std::ostream & debug_output( outputfile_aux );
#else
    std::ostream & debug_output( std::cout );
#endif // NT2_PSIHA_AUX_TESTING

    void analyze_values
    (
        aligned_array const &       results           ,
        aligned_array const &       desired_results   ,
        double                const max_ulp_distance  ,
        char          const * const result_description,
        char          const * const calling_function  ,
        unsigned int          const source_file_line
    )
    {
        failed_values.clear();

        double average_ulpd( 0 );
        double max_ulpd    ( 0 );

        for ( std::size_t i( 0 ); i != N; ++i )
        {
            T      const value_a( results        [ i ] );
            T      const value_b( desired_results[ i ] );
            double const ulpd   ( nt2::ulpdist( nt2::details::smallest_a( value_a, value_b ), nt2::details::smallest_b( value_a, value_b ) ) );
            average_ulpd += ulpd;
            max_ulpd      = std::max( max_ulpd, ulpd );
            if ( ulpd > max_ulp_distance )
            {
                failed_value_t const failed_value = { value_a, value_b, static_cast<T>( ulpd ), i };
                failed_values.push_back( failed_value );
            }
        }

        debug_output << std::endl;

        nt2::unit::test_count()++;
        if ( failed_values.empty() )
        {
            nt2::unit::pass( result_description );
            debug_output
                << "   * average ULPD: " << static_cast<T>( average_ulpd / N ) << std::endl
                << "   * max     ULPD: " << static_cast<T>( max_ulpd         ) << " (allowed: " << max_ulp_distance << ")" << std::endl;
        }
        else
        {
            nt2::unit::fail( result_description, source_file_line, calling_function );

            debug_output << "   because the ULP distance for the following "
                         << failed_values.size()
                         << " " << result_description
                         << " values was too large:"
                         << std::endl;

            BOOST_FOREACH( failed_value_t const & failed_value, failed_values )
            {
                debug_output << "\tvalue: "         << failed_value.value
                             << ", desired value: " << failed_value.desired_value
                             << ", ULP distance: "  << failed_value.ulp_error
                             << ", value index: "   << failed_value.index
                             << std::endl;
            }

            debug_output
                << "   * average ULPD: " << static_cast<T>( average_ulpd / N ) << std::endl
                << "   * max     ULPD: " << static_cast<T>( max_ulpd         ) << " (allowed: " << max_ulp_distance << ")" << std::endl;
        }
    } // analyze_values

    #define NT2_FFT_ANALYZE_VALUES( results, desired_results, max_ulp_distance, result_description ) \
        analyze_values( results, desired_results, max_ulp_distance, result_description, BOOST_CURRENT_FUNCTION, __LINE__ )

} // anonymous namespace

NT2_TEST_CASE( test )
{
    // Test complex transform(s):
    {
        aligned_array real_data;
        aligned_array imag_data;

        randomize( real_data );
        randomize( imag_data );

        aligned_array const original_real_data( real_data );
        aligned_array const original_imag_data( imag_data );

        FFT::forward_transform( &real_data[ 0 ], &imag_data[ 0 ], N );
        FFT::inverse_transform( &real_data[ 0 ], &imag_data[ 0 ], N );

        T const norm( nt2::complex_fft_normalization_factor<T>( N ) );
        scale( real_data, norm );
        scale( imag_data, norm );

        NT2_FFT_ANALYZE_VALUES( real_data, original_real_data, constants::maximum_allowed_complex_nt2_ulpd, "complex real data"      );
        NT2_FFT_ANALYZE_VALUES( imag_data, original_imag_data, constants::maximum_allowed_complex_nt2_ulpd, "complex imaginary data" );


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
            scale( real_data, norm );
            scale( imag_data, norm );

            NT2_FFT_ANALYZE_VALUES( real_data, original_real_data, constants::maximum_allowed_complex_apple_ulpd, "apple complex real data"      );
            NT2_FFT_ANALYZE_VALUES( imag_data, original_imag_data, constants::maximum_allowed_complex_apple_ulpd, "apple complex imaginary data" );
        }
    #endif // __APPLE__
    }

    // Test real transform(s):
    {
        aligned_array real_time_data;
        randomize( real_time_data );

        aligned_half_complex_array real_frequency_data;
        aligned_half_complex_array imag_frequency_data;
        FFT::real_forward_transform( &real_time_data[ 0 ], &real_frequency_data[ 0 ], &imag_frequency_data[ 0 ], N );

        aligned_array real_time_data2;
        FFT::real_inverse_transform( &real_frequency_data[ 0 ], &imag_frequency_data[ 0 ], &real_time_data2[ 0 ], N );

        T const norm( nt2::real_fft_normalization_factor<T>( N ) );
        scale( real_time_data2, norm );

        NT2_FFT_ANALYZE_VALUES( real_time_data2, real_time_data, constants::maximum_allowed_real_nt2_ulpd, "real data" );

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
            scale( real_time_data2, norm );

            NT2_FFT_ANALYZE_VALUES( real_time_data, real_time_data2, constants::maximum_allowed_real_apple_ulpd, "apple real data" );
        }
    #endif // __APPLE__
    }
}
