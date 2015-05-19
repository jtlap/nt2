//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DERIVATION_FUNCTIONS_SCALAR_FORWARD_HPP_INCLUDED
#define NT2_DERIVATION_FUNCTIONS_SCALAR_FORWARD_HPP_INCLUDED

#include <nt2/derivation/functions/forward.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/fast_ldexp.hpp>
#include <nt2/include/functions/exponent.hpp>
#include <nt2/include/constants/derivinc.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/derivation/options.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( forward_, tag::cpu_
                            , (F)(X)(EPSI)
                            , (unspecified_<F>)
                              (scalar_<floating_<X> >)
                              (scalar_<floating_<EPSI> >)
                            )
  {
    typedef X result_type;

    BOOST_FORCEINLINE
    result_type operator()(F f, const X& x, const EPSI& epsi) const
    {
      result_type  h = max(epsi*abs(x), epsi);
      return (f(x+h)-f(x))/h;
    }
  };


   BOOST_DISPATCH_IMPLEMENT  ( forward_, tag::cpu_
                            , (F)(X)
                            , (unspecified_<F>)
                              (scalar_<floating_<X> >)
                            )
  {
    typedef X result_type;

    BOOST_FORCEINLINE
    result_type operator()(const F& f, const X& x) const
    {
      return forward(f, x, Derivinc<result_type>());
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( forward_, tag::cpu_
                            , (F)(X)(EPSI)(POW2DEN)
                            , (unspecified_<F>)
                              (scalar_<floating_<X> >)
                              (scalar_<floating_<EPSI> >)
                              (unspecified_<POW2DEN>)
                            )
  {
    typedef X result_type;

    BOOST_FORCEINLINE
    result_type operator()(const F& f, const X& x, const EPSI& epsi
                          , const POW2DEN&) const
    {
      result_type  e = fast_ldexp(One<result_type>(), exponent(epsi));
      result_type  h = max(e*fast_ldexp(One<result_type>(), exponent(x)), e);
      return  (f(x+h)-f(x))/h;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( forward_, tag::cpu_
                            , (F)(X)(POW2DEN)
                            , (unspecified_<F>)
                              (scalar_<floating_<X> >)
                              (unspecified_<POW2DEN>)
                            )
  {
    typedef X result_type;

    BOOST_FORCEINLINE
    result_type operator()(const F& f, const X& x
                          ,  const POW2DEN&) const
    {
      result_type  h = max(Derivinc<result_type>()*fast_ldexp(One<result_type>(), exponent(x))
                          , Derivinc<result_type>());
      return  (f(x+h)-f(x))/h;

    }
  };

} }

#endif
