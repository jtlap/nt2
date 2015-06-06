//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_OPERATOR_FUNCTIONS_GENERIC_IS_GREATER_HPP_INCLUDED
#define NT2_AD_OPERATOR_FUNCTIONS_GENERIC_IS_GREATER_HPP_INCLUDED

#include <nt2/include/functions/is_greater.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class T1, class T2> BOOST_FORCEINLINE
    auto is_greater(const valder<T1>&u, const valder<T2>&v)->decltype(nt2::is_greater(u.val(), v.val()))
    {
      return nt2::is_greater(u.val(), v.val());
    };
    template < class T1, class T2> BOOST_FORCEINLINE
    auto is_greater(const T1&u, const valder<T2>&v)->decltype(nt2::is_greater(u, v.val()))
    {
      return nt2::is_greater(u, v.val());
    };
    template < class T1, class T2 > BOOST_FORCEINLINE
    auto is_greater(const valder<T1>&u, const T2&v)->decltype(nt2::is_greater(u.val(), v))
    {
      return nt2::is_greater(u.val(), v);
    };
  }
}

#endif
