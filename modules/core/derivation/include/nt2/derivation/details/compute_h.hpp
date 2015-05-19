//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_MODULES_CORE_DERIVATION_UNIT_DETAILS_COMPUTE_H_HPP_INCLUDED
#define NT2_MODULES_CORE_DERIVATION_UNIT_DETAILS_COMPUTE_H_HPP_INCLUDED
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/exponent.hpp>
#include <nt2/include/functions/fast_ldexp.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/constants/one.hpp>
#include <boost/mpl/int.hpp>

namespace nt2 { namespace details
{
  template < class R>
  struct compute
  {
    template < class X, class C>
    static BOOST_FORCEINLINE auto h(const X & x, R epsi
                                           , const boost::mpl::long_<2> &
                                           , const C&)
      -> decltype(max(epsi*abs(x), epsi))
    {
      return max(epsi*abs(x), epsi);
    }
    template < class X >
      static BOOST_FORCEINLINE auto h(const X & x, R epsi
                                             , const boost::mpl::long_<3> &
                                             ,  const boost::mpl::true_&)
      -> decltype(max(epsi*abs(x), epsi))
    {
      return max(epsi*abs(x), epsi);
    }
    template < class X >
    static BOOST_FORCEINLINE auto h(const X & x, R epsi
                                             , const boost::mpl::long_<3> &
                                             ,  const boost::mpl::false_&)
      ->  decltype(max(epsi*fast_ldexp(One<R>(), exponent(x)), epsi))
    {
      return max(epsi*fast_ldexp(One<R>(), exponent(x)), epsi);
    }

    template < class X, class C>
    static BOOST_FORCEINLINE auto _h(const X & x, R epsi
                                           , const boost::mpl::long_<4> &
                                           , const C&)
      -> decltype(max(epsi*fast_ldexp(One<R>(), exponent(x)), epsi))
    {
      return max(epsi*fast_ldexp(One<R>(), exponent(x)), epsi);
    }
  };

} }


#endif

