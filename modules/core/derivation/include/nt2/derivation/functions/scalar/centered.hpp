//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DERIVATION_FUNCTIONS_SCALAR_CENTERED_HPP_INCLUDED
#define NT2_DERIVATION_FUNCTIONS_SCALAR_CENTERED_HPP_INCLUDED

#include <nt2/derivation/functions/centered.hpp>
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
#include <utility>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( centered_, tag::cpu_
                            , (F)(X)(EPSI)
                            , (unspecified_<F>)
                              (scalar_<floating_<X> >)
                              (scalar_<floating_<EPSI> >)
                            )
  {
    typedef decltype(std::declval<F>()(std::declval<X>())) result_type;
    typedef typename meta::as_real<X>::type                    rtype_t;

    BOOST_FORCEINLINE
    result_type operator()(F f, const X& x, const EPSI& epsi) const
    {
      rtype_t h = max(epsi*abs(x), epsi);
      return (f(x+h)-f(x-h))/(h+h);
    }
  };


   BOOST_DISPATCH_IMPLEMENT  ( centered_, tag::cpu_
                            , (F)(X)
                            , (unspecified_<F>)
                              (scalar_<floating_<X> >)
                            )
  {
    typedef decltype(std::declval<F>()(std::declval<X>())) result_type;
    typedef typename meta::as_real<X>::type                    rtype_t;

    BOOST_FORCEINLINE
    result_type operator()(const F& f, const X& x) const
    {
      return centered(f, x, Derivinc<rtype_t>());
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( centered_, tag::cpu_
                            , (F)(X)(EPSI)(POW2DEN)
                            , (unspecified_<F>)
                              (scalar_<floating_<X> >)
                              (scalar_<floating_<EPSI> >)
                              (unspecified_<POW2DEN>)
                            )
  {
    typedef decltype(std::declval<F>()(std::declval<X>())) result_type;
    typedef typename meta::as_real<X>::type                    rtype_t;

    BOOST_FORCEINLINE
    result_type operator()(const F& f, const X& x, const EPSI& epsi
                          , const POW2DEN&) const
    {
      rtype_t e = fast_ldexp(One<rtype_t>(), exponent(epsi));
      rtype_t h = max(e*fast_ldexp(One<rtype_t>(), exponent(x)), e);
      return  (f(x+h)-f(x-h))/(h+h);
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( centered_, tag::cpu_
                            , (F)(X)(POW2DEN)
                            , (unspecified_<F>)
                              (scalar_<floating_<X> >)
                              (unspecified_<POW2DEN>)
                            )
  {
    typedef decltype(std::declval<F>()(std::declval<X>())) result_type;
    typedef typename meta::as_real<X>::type                    rtype_t;

    BOOST_FORCEINLINE
    result_type operator()(const F& f, const X& x,  const POW2DEN&) const
    {
      rtype_t h = max(Derivinc<rtype_t>()*fast_ldexp(One<rtype_t>(), exponent(x))
                          , Derivinc<rtype_t>());
      return  (f(x+h)-f(x-h))/(h+h);

    }
  };

} }

#endif
