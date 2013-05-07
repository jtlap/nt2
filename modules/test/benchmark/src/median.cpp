//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//         Copyright 2012        Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/bench/config.hpp>
#include <nt2/sdk/bench/details/median.hpp>
#include <boost/dispatch/attributes.hpp>
#include <algorithm>

namespace nt2{ namespace details
{
  template <typename T> inline
  BOOST_DISPATCH_NOTHROW BOOST_DISPATCH_NOINLINE
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

  template  NT2_TEST_BENCHMARK_DECL nt2::uint32_t
  median_impl<nt2::uint32_t>(boost::iterator_range<nt2::uint32_t*>);

  template  NT2_TEST_BENCHMARK_DECL nt2::uint64_t
  median_impl<nt2::uint64_t>(boost::iterator_range<nt2::uint64_t*>);

  template  NT2_TEST_BENCHMARK_DECL double
  median_impl<double       >(boost::iterator_range<double*> );
} }
