//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DERIVATION_FUNCTIONS_SCALAR_VAND_HPP_INCLUDED
#define NT2_DERIVATION_FUNCTIONS_SCALAR_VAND_HPP_INCLUDED

#include <nt2/derivation/functions/vand.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/mul_minus_i.hpp>
#include <nt2/include/functions/tocomplex.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/derivation/options.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( vand_, tag::cpu_
                            , (F)(X)
                            , (unspecified_<F>)
                              (scalar_<floating_<X> >)
                            )
  {
    typedef X result_type; // f must C->C but f|R R -> R

    BOOST_FORCEINLINE
    result_type operator()(F f, const X& x) const
    {
      return imag(f(tocomplex(x, Eps<result_type>())))/Eps<result_type>();
    }
  };

} }

#endif
