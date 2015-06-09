//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_OPERATOR_FUNCTIONS_GENERIC_IFNOTADD_HPP_INCLUDED
#define NT2_AD_OPERATOR_FUNCTIONS_GENERIC_IFNOTADD_HPP_INCLUDED

#include <nt2/include/functions/ifnotadd.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/ad/functions/ad.hpp>
#include <nt2/ad/details/booleangen.hpp>

namespace nt2
{
  namespace ad
  {
    template < class L, class T1, class T2>
    BOOST_FORCEINLINE
    valder<T1> ifnotadd(const L & l
                   , const valder<T1>&u
                   , const valder<T2>&v)
    {
      return valder<T1>(nt2::ifnotadd(l, u.val(), v.val())
                       , nt2::ifnotadd(l, u.der(), v.der())
                       );
    };
    template < class L, class T1, class T2>
    BOOST_FORCEINLINE
    valder<T2> ifnotadd(const L & l
                   , const T1&u
                   , const valder<T2>&v)
    {
      return valder<T2>(nt2::ifnotadd(l, u, v.val())
                      , nt2::if_zero_else(l, v.der())
                      );
    };
    template < class L, class T1, class T2>
    BOOST_FORCEINLINE
    valder<T1> ifnotadd(const L & l
                   , const valder<T1>&u
                   , const T2&v)
    {
      return valder<T1>(nt2::ifnotadd(l, u.val(), v)
                       , u.der()
                       );
    };
    template < class L, class T1, class T2>
    BOOST_FORCEINLINE
    valder<T1> ifnotadd(const valder<L> & l
                   , const valder<T1>&u
                   , const valder<T2>&v)
    {
      return ifnotadd(l.val(), u, v);
    };
    template < class L, class T1, class T2>
    BOOST_FORCEINLINE
    valder<T2> ifnotadd(const valder<L> & l
                   , const T1&u
                   , const valder<T2>&v)
    {
      return  ifnotadd(l.val(), u, v);
    };
    template < class L, class T1, class T2>
    BOOST_FORCEINLINE
    valder<T1> ifnotadd(const valder<L> & l
                   , const valder<T1>&u
                   , const T2&v)
    {
      return ifnotadd(l.val(), u, v);
    };
      template < class L, class T1, class T2>
    BOOST_FORCEINLINE
    T1 ifnotadd( const valder<L> & l
           , const T1&u
           , const T2&v)
    {
      return nt2::ifnotadd(l.val(), u, v);
    };

  }
}

#endif
