//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_FASTNORMCDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_FASTNORMCDF_HPP_INCLUDED
#include <nt2/statistics/functions/fastnormcdf.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/invsqrt_2pi.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/splat.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fastnormcdf_, tag::cpu_
                            , (A0)
                            , (generic_< single_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      result_type l = abs(a0);
      result_type k = rec(fma(splat<result_type>(0.2316419f),l,One<result_type>()));
      result_type w = horner< NT2_HORNER_COEFF_T( typename meta::scalar_of<result_type>::type
                                                 , 5
                                                 , ( 0x3faa466f, 0xbfe91eea
                                                   , 0x3fe40778, 0xbeb68f87
                                                   , 0x3ea385fa
                                                   ))>(k);
      w*=Invsqrt_2pi<result_type>()*exp(-sqr(l)*Half<result_type>());
      return if_else(is_gtz(a0),oneminus(w),w);
    }
  };
} }

#endif