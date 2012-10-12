//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/sdk/timing/now.hpp>
#include <nt2/sdk/config/types.hpp>

#include <boost/dispatch/attributes.hpp>

#include <boost/array.hpp>
#include <boost/assert.hpp>
#include <boost/foreach.hpp>
/// \note std::rand() does not produce portably reproducible numbers so we
/// resort to Boost.Random.
///                                           (24.10.2012.) (Domagoj Saric)
/// \note NT2Bench configuration has exceptions disabled and Boost.Random
/// fails to compile then because it uses naked throw statements.
/// https://svn.boost.org/trac/boost/ticket/7497
///                                           (12.10.2012.) (Domagoj Saric)
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/range/iterator_range_core.hpp>

#include <algorithm>
#include <vector>


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//...zzz...begin temporary content...move to a separate cpp module(s)...
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
namespace nt2
{
namespace details
{
    template <typename T> inline
    BOOST_NOTHROW BOOST_DISPATCH_NOINLINE
    T median_impl( boost::iterator_range<T *> const data )
    {
        typedef typename boost::iterator_range<T *>::iterator iterator;

        std::size_t const data_size( data.size()                  );
        iterator    const target   ( data.begin() + data_size / 2 );
        std::nth_element( data.begin(), target, data.end() );

        T const result1( *target );
        if ( data_size % 2 )
            return result1;
        else
        {
            T const result2( *( target - 1 ) );
            return ( result1 + result2 ) / 2;
        }
    }

    template NT2_SDK_TIMING_DECL unsigned int  median_impl<unsigned int >( boost::iterator_range<unsigned int  *> );
    template NT2_SDK_TIMING_DECL nt2::uint64_t median_impl<nt2::uint64_t>( boost::iterator_range<nt2::uint64_t *> );
    template NT2_SDK_TIMING_DECL double        median_impl<double       >( boost::iterator_range<double        *> );


    static boost::random::rand48 prng_singleton;
    NT2_SDK_TIMING_DECL BOOST_NOTHROW void prng_reset() { prng_singleton.seed( 42 ); }

    template <typename T>
    BOOST_NOTHROW void prng_fill_impl( boost::iterator_range<T *> const data, T const rnd_range_minimum, T const rnd_range_maximum )
    {
        boost::random::uniform_real_distribution<T> const distribution( rnd_range_minimum, rnd_range_maximum );
        BOOST_FOREACH( T & scalar, data )
            scalar = distribution( prng_singleton );
    }

    template NT2_SDK_TIMING_DECL BOOST_NOTHROW void prng_fill_impl( boost::iterator_range<int    *>, int   , int    );
    template NT2_SDK_TIMING_DECL BOOST_NOTHROW void prng_fill_impl( boost::iterator_range<float  *>, float , float  );
    template NT2_SDK_TIMING_DECL BOOST_NOTHROW void prng_fill_impl( boost::iterator_range<double *>, double, double );
} // namespace details

namespace unit
{
  typedef std::pair<nt2::details::cycles_t, nt2::details::microseconds_t> benchmark_result_t;

  static std::vector<nt2::details::cycles_t      > individual_measurement_cycles       ;
  static std::vector<nt2::details::time_quantum_t> individual_measurement_time_quantums;

  typedef std::pair<nt2::details::cycles_t, nt2::details::time_quantum_t> intermediate_benchmark_result_t;

  BOOST_DISPATCH_NOINLINE
  intermediate_benchmark_result_t
  perform_benchmark_impl( benchmark_t & test, nt2::details::seconds_t const total_duration_in_seconds )
  {
    individual_measurement_cycles       .clear();
    individual_measurement_time_quantums.clear();

    using namespace nt2::details;

    time_quantum_t const total_duration( to_timequantums( total_duration_in_seconds * 1000000 ) );
    time_quantum_t       duration      ( 0                                                      );

    while ( duration < total_duration )
    {
        time_quantum_t const time_start  ( now        () );
        cycles_t       const cycles_start( read_cycles() );
        test.run();
        cycles_t       const cycles_end  ( read_cycles() );
        time_quantum_t const time_end    ( now        () );

        cycles_t       const burned_cycles( cycles_end - cycles_start );
        time_quantum_t const elapsed_time ( time_end   - time_start   );

    /* "other" version:
        cycles_t       const cycles_start( read_cycles() );
        time_quantum_t const time_start  ( now        () );
        test();
        time_quantum_t const time_stop    ( now        () );
        cycles_t       const cycles_stop  ( read_cycles() );

        time_quantum_t const elapsed_time ( time_stop   - time_start   - now_overhead                                       );
        cycles_t       const burned_cycles( cycles_stop - cycles_start - read_cycles_plus_virtual_overhead_in_cycles - ( 2 * now_overhead_cycles ) );
    */
        duration += elapsed_time;

        individual_measurement_cycles       .push_back( burned_cycles );
        individual_measurement_time_quantums.push_back( elapsed_time  );
        test.reset();
        /// \todo Consider flushing the CPU cache(s) here (the pipeline
        /// presumably gets flushed this loop's code).
        ///                                   (05.11.2012.) (Domagoj Saric)
    }

    return intermediate_benchmark_result_t
    (
        median( individual_measurement_cycles        ),
        median( individual_measurement_time_quantums ) 
    );
  }

  NT2_SDK_TIMING_DECL
  BOOST_DISPATCH_NOINLINE
  benchmark_result_t perform_benchmark( benchmark_t & test, nt2::details::seconds_t const total_duration_in_seconds )
  {
      using namespace nt2::details;

      intermediate_benchmark_result_t const intermediate_results( perform_benchmark_impl( test, total_duration_in_seconds ) );
      return benchmark_result_t
      (
                         intermediate_results.first  - read_cycles_plus_virtual_overhead_in_cycles,
        to_microseconds( intermediate_results.second - now_plus_read_cycles_plus_virtual_overhead_in_time_quantums )
      );
  }
} // namespace unit
} // namespace nt2
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//...zzz...begin temporary content...move to a separate cpp module(s)...
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


//==============================================================================
// gettimeofday systems
//==============================================================================
#if defined( BOOST_HAS_GETTIMEOFDAY )
#include <sys/resource.h>
#include <sys/time.h>

namespace nt2 { namespace details
{
  unsigned int const timer_ticks_per_microsecond( 1 );

  NT2_SDK_TIMING_DECL time_quantum_t now()
  {
    /// \todo Investigate:
    /// http://www.gamasutra.com/view/feature/171774/getting_high_precision_timing_on_.php
    /// http://pubs.opengroup.org/onlinepubs/009695399/functions/clock_gettime.html
    /// http://gruntthepeon.free.fr/blog/index.php/2011/05/30/56-clock_gettime-is-slow
    ///                                     (18.10.2012.) (Domagoj Saric)
    timeval tp;
    BOOST_VERIFY( ::gettimeofday( &tp, NULL ) == 0 );
    return static_cast<time_quantum_t>( tp.tv_sec ) * 1000000 + tp.tv_usec;
  }

  struct priority_booster_t
  {
      priority_booster_t()
      {
          /*BOOST_VERIFY*/( ::setpriority(  PRIO_PROCESS      , 0, -20 ) /*== 0*/ );
        #ifdef __APPLE__
          /*BOOST_VERIFY*/( ::setpriority(  PRIO_DARWIN_THREAD, 0, -20 ) /*== 0*/ );
        #endif // __APPLE__
      }
  };
} }

#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
//==============================================================================
// QueryPerformanceCounter systems
//==============================================================================
#include <windows.h>

namespace nt2 { namespace details
{
    static unsigned long long get_timer_resolution()
    {
        LARGE_INTEGER frequency;
        BOOST_VERIFY( ::QueryPerformanceFrequency( &frequency ) );
        return frequency.QuadPart;
    }

    static double const timer_ticks_per_microsecond( get_timer_resolution() / 1000000.0 );

    NT2_SDK_TIMING_DECL time_quantum_t now()
    {
        // http://support.microsoft.com/kb/172338
        BOOST_ASSERT_MSG
        (
            timer_ticks_per_microsecond == get_timer_resolution(),
            "MSDN explicitly states for QueryPerformanceFrequency: 'The frequency cannot change while the system is running.'"
        );
        /// \todo Also add http://msdn.microsoft.com/en-us/library/ms684208(VS.85).aspx.
        ///                                   (18.10.2012.) (Domagoj Saric)
        /// \todo Assert these no longer apply:
        /// http://support.microsoft.com/kb/274323 (http://bullet.googlecode.com/svn/tags/bullet-2.72-release/src/LinearMath/btQuickprof.h)
        /// http://www.virtualdub.org/blog/pivot/entry.php?id=106.
        ///                                   (18.10.2012.) (Domagoj Saric)
        ::_ReadWriteBarrier();
        LARGE_INTEGER result;
        BOOST_VERIFY( ::QueryPerformanceCounter( &result ) );
        ::_ReadWriteBarrier();
        return result.QuadPart;
    }

    struct priority_booster_t
    {
        priority_booster_t()
        {
            BOOST_VERIFY( ::SetProcessAffinityMask( ::GetCurrentProcess(),                             1 ) );
            BOOST_VERIFY( ::SetPriorityClass      ( ::GetCurrentProcess(), REALTIME_PRIORITY_CLASS       ) );
            BOOST_VERIFY( ::SetThreadPriority     ( ::GetCurrentThread (), THREAD_PRIORITY_TIME_CRITICAL ) );

            /// \todo Try and disable SpeedStep/TurboBoost/<whatever> or at
            /// least add some dummy form of initial burn-in to force the CPU
            /// frequency to max out before measurements begin.
            ///                               (23.10.2012.) (Domagoj Saric)
        }
    };
} }

#else
//==============================================================================
// Other systems
//==============================================================================
#include <ctime>

namespace nt2 { namespace details
{
    /// \todo Invesitgate boost/std::chrono.
    ///                                       (18.10.2012.) (Domagoj Saric)

    static double const timer_ticks_per_microsecond( CLOCKS_PER_SEC / 1000000.0 );

    NT2_SDK_TIMING_DECL time_quantum_t now() { return std::clock(); }

    struct priority_booster_t {};
} }

#endif

namespace nt2 { namespace details
{
    static priority_booster_t const priority_booster;

    static microseconds_t const inverse_timer_ticks_per_microsecond_microseconds_type( static_cast<microseconds_t>( 1 ) / timer_ticks_per_microsecond );

    NT2_SDK_TIMING_DECL microseconds_t to_microseconds( time_quantum_t const time )
    {
        return static_cast<microseconds_t>( time ) * inverse_timer_ticks_per_microsecond_microseconds_type;
    }

    NT2_SDK_TIMING_DECL time_quantum_t to_timequantums( microseconds_t const time )
    {
        return static_cast<time_quantum_t>( time * timer_ticks_per_microsecond );
    }


    static std::pair<unsigned int, unsigned int> calculate_overhead()
    {
        // Overhead offsets:
        // http://www.motherboardpoint.com/rdtsc-performance-different-x86-archs-t166722.html

        struct null_benchmark_t : nt2::unit::benchmark_t { BOOST_NOTHROW void run() const BOOST_OVERRIDE {} };
        null_benchmark_t null_benchmark;
        volatile nt2::unit::benchmark_t & optimizer_wall_benchmark( null_benchmark );

        nt2::unit::intermediate_benchmark_result_t const result( perform_benchmark_impl( const_cast<nt2::unit::benchmark_t &>( optimizer_wall_benchmark ), 0.25 ) );
        return std::make_pair
        (
            static_cast<unsigned int>( result.first  ),
            static_cast<unsigned int>( result.second )
        );
    }
    static std::pair<unsigned int, unsigned int> const intermediate_overhead_results( calculate_overhead() );

    NT2_SDK_TIMING_DECL unsigned int const read_cycles_plus_virtual_overhead_in_cycles                ( intermediate_overhead_results.first  );
    NT2_SDK_TIMING_DECL unsigned int const now_plus_read_cycles_plus_virtual_overhead_in_time_quantums( intermediate_overhead_results.second );


    NT2_SDK_TIMING_DECL double now_in_seconds()
    {
        return static_cast<double>( to_microseconds( now() ) * 1000000 );
    }
} }
