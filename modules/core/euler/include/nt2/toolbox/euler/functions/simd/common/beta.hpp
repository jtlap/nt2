//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_SIMD_COMMON_BETA_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_SIMD_COMMON_BETA_HPP_INCLUDED

#include <nt2/toolbox/euler/functions/beta.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>

#include <nt2/include/functions/simd/signgam.hpp>
#include <nt2/include/functions/simd/gammaln.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>

/**
 * \ingroup euler_beta
 * \defgroup euler_beta_simd Notes on the SIMD implementation
 *
 * \par Specificities
 *
 *  Some info on \c beta in SIMD mode
 **/

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::beta_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef typename meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return nt2::beta(tofloat(a0), tofloat(a1));
    }
  };
} }

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::beta_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))((simd_<floating_<A0>,X>))
                            )
  {

    typedef typename meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      const A0 y = a0+a1;
      const A0 sign = signgam(a0)*signgam(a1)*signgam(y);
      return sign*exp(gammaln(a0)+gammaln(a1)-gammaln(y));
    }
  };
} }


#endif
