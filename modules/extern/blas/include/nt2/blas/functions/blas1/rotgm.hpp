//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapreste
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BLAS_FUNCTIONS_BLAS1_ROTGM_HPP_INCLUDED
#define NT2_BLAS_FUNCTIONS_BLAS1_ROTGM_HPP_INCLUDED

#include <nt2/blas/functions/rotgm.hpp>
#include <nt2/blas/details/blas1.hpp>
#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace blas { namespace ext
{

//---------------------------------------------Real-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( rotgm_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , (scalar_<single_<A0>>) //a
                              (scalar_<single_<A1>>) //b
                              (scalar_<single_<A2>>) //c
                              (scalar_<single_<A3>>) //s
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( A0& a, A1& b
                                     , A2& c, A3& s) const
     {
       NT2_F77NAME(srotgm) (&a, &b, &c, &s);
     }
  };

//---------------------------------------------Real-double------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( rotgm_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , (scalar_<double_<A0>>) //a
                              (scalar_<double_<A1>>) //b
                              (scalar_<double_<A2>>) //c
                              (scalar_<double_<A3>>) //s
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( A0& a, A1& b
                                     , A2& c, A3& s) const
     {
       NT2_F77NAME(drotgm) (&a, &b, &c, &s);
     }
  };

}  } }

#endif
