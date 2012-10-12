//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_TIMING_NOW_HPP_INCLUDED
#define NT2_SDK_TIMING_NOW_HPP_INCLUDED

#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/timing/config.hpp>

#include <boost/noncopyable.hpp>
#include <boost/range/iterator_range_core.hpp>

namespace nt2 { namespace details
{
  typedef nt2::uint64_t cycles_t      ;
  typedef nt2::uint64_t time_quantum_t;
  typedef double        seconds_t     ;
  typedef double        microseconds_t;

  #if defined( _MSC_VER )
      #define BOOST_NOTHROW  __declspec( nothrow )
      #define BOOST_OVERRIDE override
  #elif defined( __GNUC__ )
      #define BOOST_NOTHROW __attribute__(( nothrow ))
      #define BOOST_OVERRIDE
  #else
      #define BOOST_NOTHROW
      #define BOOST_OVERRIDE
  #endif // compiler

  NT2_SDK_TIMING_DECL BOOST_NOTHROW time_quantum_t now        ();
                      BOOST_NOTHROW cycles_t       read_cycles();

  NT2_SDK_TIMING_DECL BOOST_NOTHROW microseconds_t to_microseconds( time_quantum_t );
  NT2_SDK_TIMING_DECL BOOST_NOTHROW time_quantum_t to_timequantums( microseconds_t );


  NT2_SDK_TIMING_DECL extern unsigned int const read_cycles_plus_virtual_overhead_in_cycles                ;
  NT2_SDK_TIMING_DECL extern unsigned int const now_plus_read_cycles_plus_virtual_overhead_in_time_quantums;
  
  NT2_SDK_TIMING_DECL /*deprecated*/ BOOST_NOTHROW seconds_t now_in_seconds();

  //////////////////////////////////////////////////////////////////////////////
  //...zzz...begin temporary content...move to a separate cpp module...
  //////////////////////////////////////////////////////////////////////////////

  /// \note Portably reproducible pseudo "random" values.
  ///                                         (24.07.2012.) (Domagoj Saric)
  NT2_SDK_TIMING_DECL BOOST_NOTHROW void prng_reset();
  template <typename T>
  NT2_SDK_TIMING_DECL BOOST_NOTHROW void prng_fill_impl( boost::iterator_range<T *> data, T rnd_range_minimum, T rnd_range_maximum );
  template <class Range>
  void prng_fill( Range & data, typename Range::value_type const rnd_range_minimum, typename Range::value_type const rnd_range_maximum )
  {
      prng_fill_impl<typename Range::value_type>
      (
        boost::iterator_range<typename Range::value_type *>( &*data.begin(), ( &*( data.end() - 1 ) ) + 1 ),
        rnd_range_minimum, rnd_range_maximum
      );
  }

  template <typename T>
  NT2_SDK_TIMING_DECL BOOST_NOTHROW T median_impl( boost::iterator_range<T *> data );

  template <class Range>
  typename Range::value_type median( Range & data )
  {
      return median_impl<typename Range::value_type>
      (
        boost::iterator_range<typename Range::value_type *>( &*data.begin(), ( &*( data.end() - 1 ) ) + 1 )
      );
  }
} // namespace details

namespace unit
{
    class
    #ifdef _MSC_VER
    __declspec( novtable )
    #endif // _MSC_ER
    benchmark_t : private boost::noncopyable
    {
    public:
        virtual BOOST_NOTHROW void run  () const = 0   ;
        virtual BOOST_NOTHROW void reset()           {};

    protected:
        BOOST_NOTHROW ~benchmark_t() {}
    };
  //////////////////////////////////////////////////////////////////////////////
  //...zzz...end temporary content...move to a separate cpp module...
  //////////////////////////////////////////////////////////////////////////////
} // namespace unit
} // namespace nt2

#include <nt2/sdk/timing/details/cycles.hpp>

#endif
