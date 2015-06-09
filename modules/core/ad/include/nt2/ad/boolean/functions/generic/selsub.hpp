//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_OPERATOR_FUNCTIONS_GENERIC_SELSUB_HPP_INCLUDED
#define NT2_AD_OPERATOR_FUNCTIONS_GENERIC_SELSUB_HPP_INCLUDED

#include <nt2/include/functions/selsub.hpp>
#include <nt2/include/functions/if_else_zero.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class L, class T1, class T2>
    BOOST_FORCEINLINE
    valder<T1> selsub(const L & l
                   , const valder<T1>&u
                   , const valder<T2>&v)
    {
      return valder<T1>(nt2::selsub(l, u.val(), v.val())
                       , nt2::selsub(l, u.der(), v.der())
                       );
    };
    template < class L, class T1, class T2>
    BOOST_FORCEINLINE
    valder<T2> selsub(const L & l
                   , const T1&u
                   , const valder<T2>&v)
    {
      return valder<T2>(nt2::selsub(l, u, v.val())
                      , nt2::if_else_zero(l, -v.der())
                      );
    };
    template < class L, class T1, class T2>
    BOOST_FORCEINLINE
    valder<T1> selsub(const L & l
                   , const valder<T1>&u
                   , const T2&v)
    {
      return valder<T1>(nt2::selsub(l, u.val(), v)
                       , u.der()
                       );
    };
    template < class L, class T1, class T2>
    BOOST_FORCEINLINE
    valder<T1> selsub(const valder<L> & l
                   , const valder<T1>&u
                   , const valder<T2>&v)
    {
      return selsub(l.val(), u, v);
    };
    template < class L, class T1, class T2>
    BOOST_FORCEINLINE
    valder<T2> selsub(const valder<L> & l
                   , const T1&u
                   , const valder<T2>&v)
    {
      return  selsub(l.val(), u, v);
    };
    template < class L, class T1, class T2>
    BOOST_FORCEINLINE
    valder<T1> selsub(const valder<L> & l
                   , const valder<T1>&u
                   , const T2&v)
    {
      return selsub(l.val(), u, v);
    };
      template < class L, class T1, class T2>
    BOOST_FORCEINLINE
    T1 selsub( const valder<L> & l
           , const T1&u
           , const T2&v)
    {
      return nt2::selsub(l.val(), u, v);
    };

  }
}

#endif
