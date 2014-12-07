//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapreste
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_BLAS_ROTMG_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_BLAS_ROTMG_HPP_INCLUDED

#include <nt2/linalg/functions/blas_rotmg.hpp>
#include <nt2/linalg/details/blas/blas1.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/sdk/memory/container.hpp>

namespace nt2 { namespace ext
{

//---------------------------------------------Real-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_rotmg_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)(S)
                            , (scalar_<single_<A0>>) //d1
                              (scalar_<single_<A1>>) //d2
                              (scalar_<single_<A2>>) //x1
                              (scalar_<single_<A3>>) //x2
                              ((container_<nt2::tag::table_,  single_<A4>, S >)) //dparam
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( A0& d1, A1& d2
                                     , A2& x1, A3& y1
                                     , A4& dparam) const
     {
       NT2_F77NAME(srotmg) (&d1, &d2, &x1, &y1, dparam.raw());
     }
  };

//---------------------------------------------Real-double------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_rotmg_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)(S)
                            , (scalar_<double_<A0>>) //d1
                              (scalar_<double_<A1>>) //d2
                              (scalar_<double_<A2>>) //x1
                              (scalar_<double_<A3>>) //x2
                              ((container_<nt2::tag::table_,  double_<A4>, S >)) //dparam
                             )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( A0& d1, A1& d2
                                     , A2& x1, A3& y1
                                     , A4& dparam) const
     {
       NT2_F77NAME(drotmg) (&d1, &d2, &x1, &y1, dparam.raw());
     }
  };

} }

#endif
