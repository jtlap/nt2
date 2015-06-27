//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_MODULES_CORE_NUMERICAL_DERIVATIVES_UNIT_DETAILS_GET_EPSI_HPP_INCLUDED
#define NT2_MODULES_CORE_NUMERICAL_DERIVATIVES_UNIT_DETAILS_GET_EPSI_HPP_INCLUDED
#include <boost/mpl/int.hpp>
#include <nt2/sdk/meta/is_scalar.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>

namespace nt2 { namespace details
{
  // if epsi is not a scalar a fallback is provided
  template <class A1, class R>
  struct get
  {
    static BOOST_FORCEINLINE R epsi(const A1&, const R & fallback
                                   , const boost::mpl::long_<2> & )
    {
      return fallback;
    }
    static BOOST_FORCEINLINE R epsi(const A1& in, const R & fallback
                                   , const boost::mpl::long_<3> & )
    {
      typedef typename boost::proto::result_of::child_c<A1&, 2>::value_type child2_t;
      typedef typename boost::dispatch::meta::semantic_of<child2_t>::type semantic_t;
      typedef typename meta::is_scalar<semantic_t>::type                    choose_t;
      return epsi(in, fallback, choose_t(), boost::mpl::long_<3>());
    }
    static BOOST_FORCEINLINE R epsi(const A1&, const R & fallback
                                   , boost::mpl::false_, const boost::mpl::long_<3> & )
    {
      return  fallback;
    }
    static BOOST_FORCEINLINE R epsi(const A1& in, const R &
                                   , boost::mpl::true_, const boost::mpl::long_<3> & )
    {
      return   boost::proto::value(boost::proto::child_c<2>(in));
    }
    static BOOST_FORCEINLINE R epsi(const A1& in, const R &
                                   , const boost::mpl::long_<4> & )
    {
      return  boost::proto::value(boost::proto::child_c<2>(in));
    }
  };

} }


#endif

