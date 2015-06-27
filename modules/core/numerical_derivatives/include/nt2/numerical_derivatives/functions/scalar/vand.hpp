//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_NUMERICAL_DERIVATIVES_FUNCTIONS_SCALAR_VAND_HPP_INCLUDED
#define NT2_NUMERICAL_DERIVATIVES_FUNCTIONS_SCALAR_VAND_HPP_INCLUDED

#include <nt2/numerical_derivatives/functions/vand.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/mul_minus_i.hpp>
#include <nt2/include/functions/tocomplex.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/inveps.hpp>
#include <nt2/numerical_derivatives/options.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( vand_, tag::cpu_
                            , (F)(X)
                            , (unspecified_<F>)
                              (scalar_<floating_<X> >)
                            )
  {
    typedef decltype(std::declval<F>()(std::declval<X>()))         v_type;
    typedef typename meta::as_real<v_type>::type              result_type;
    // f must C->C but f|R R -> R

    BOOST_FORCEINLINE
    result_type operator()(F f, const X& x) const
    {
      return imag(f(tocomplex(x, Eps<result_type>())))/Eps<result_type>();
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( vand_, tag::cpu_
                            , (F)(X)(EPSI)(DUMMY)
                            , (unspecified_<F>)
                              (scalar_<floating_<X> >)
                              (scalar_<floating_<EPSI>>)
                              (unspecified_<DUMMY>)
                            )
  {
    typedef decltype(std::declval<F>()(std::declval<X>()))         v_type;
    typedef typename meta::as_real<v_type>::type              result_type;
    // f must C->C but f|R R -> R

    BOOST_FORCEINLINE
    result_type operator()(F f, const X& x, const EPSI& ,  const DUMMY &) const
    {
      return imag(f(tocomplex(x, Eps<result_type>())))*Inveps<result_type>();
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( vand_, tag::cpu_
                            , (F)(X)(DUMMY)
                            , (unspecified_<F>)
                              (scalar_<floating_<X> >)
                              (unspecified_<DUMMY>)
                            )
  {
    typedef decltype(std::declval<F>()(std::declval<X>()))         v_type;
    typedef typename meta::as_real<v_type>::type              result_type;
    // f must C->C but f|R R -> R

    BOOST_FORCEINLINE
    result_type operator()(F f, const X& x,  const DUMMY &) const
    {
      return imag(f(tocomplex(x, Eps<result_type>())))*Inveps<result_type>();
    }
  };
} }

#endif
