//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapreste
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_BLAS_DOTU_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_BLAS_DOTU_HPP_INCLUDED

#include <nt2/linalg/functions/blas_dotu.hpp>
#include <nt2/linalg/details/blas/blas1.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/core/container/table/table.hpp>
#include <complex>
#include <iostream>

namespace nt2 { namespace ext
{

//---------------------------------------------Real-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_dotu_, tag::cpu_
                            , (N)(A0)(S0)(INCX)(A1)(S1)(INCY)
                            , (scalar_<integer_<N>>)// n
                              ((container_<nt2::tag::table_,  single_<A0>, S0 >)) //x
                              (scalar_<integer_<INCX>>)// incx
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >)) //y
                              (scalar_<integer_<INCY>>)// incy
                            )
  {
    typedef float result_type;

    BOOST_FORCEINLINE result_type operator()( const N& n
                                     , const A0& x, const INCX & incx
                                     , const A1& y, const INCY & incy) const
     {
       nt2_la_int in = n;
       nt2_la_int ix = incx;
       nt2_la_int iy = incy;
       return NT2_F77NAME(sdot) (&in, x.raw(), &ix, y.raw(), &iy);
     }
  };

//---------------------------------------------Real-double------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_dotu_, tag::cpu_
                            , (N)(A0)(S0)(INCX)(A1)(S1)(INCY)
                            , (scalar_<integer_<N>>)// n
                              ((container_<nt2::tag::table_,  double_<A0>, S0 >)) //x
                              (scalar_<integer_<INCX>>)// incx
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >)) //y
                              (scalar_<integer_<INCY>>)// incy
                            )
  {
    typedef double result_type;

    BOOST_FORCEINLINE result_type operator()( const N& n
                                     , const A0& x, const INCX & incx
                                     , const A1& y, const INCY & incy) const
    {
      nt2_la_int in = n;
      nt2_la_int ix = incx;
      nt2_la_int iy = incy;
      return NT2_F77NAME(ddot) (&in, x.raw(), &ix, y.raw(), &iy);
    }
  };

//---------------------------------------------Complex-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_dotu_, tag::cpu_
                            , (N)(A0)(S0)(INCX)(A1)(S1)(INCY)
                            , (scalar_<integer_<N>>)// n
                              ((container_<nt2::tag::table_,  complex_<single_<A0>>, S0 >)) //x
                              (scalar_<integer_<INCX>>)// incx
                              ((container_<nt2::tag::table_,  complex_<single_<A1>>, S1 >)) //y
                              (scalar_<integer_<INCY>>)// incy
                            )
  {
    typedef typename A0::value_type result_type;

    BOOST_FORCEINLINE result_type operator()( const N& n
                                     , const A0& x, const INCX & incx
                                     , const A1& y, const INCY & incy) const
     {
       nt2_la_int in = n;
       nt2_la_int ix = incx;
       nt2_la_int iy = incy;
       result_type r;
       NT2_F77NAME(cdotu) (&r, &in, x.raw(), &ix, y.raw(), &iy);
       return r;
     }
  };

//---------------------------------------------Complex-double------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_dotu_, tag::cpu_
                            , (N)(A0)(S0)(INCX)(A1)(S1)(INCY)
                            , (scalar_<integer_<N>>)// n
                              ((container_<nt2::tag::table_,  complex_<double_<A0>>, S0 >)) //x
                              (scalar_<integer_<INCX>>)// incx
                              ((container_<nt2::tag::table_,  complex_<double_<A1>>, S1 >)) //y
                              (scalar_<integer_<INCY>>)// incy
                            )
  {
    typedef typename A0::value_type result_type;

    BOOST_FORCEINLINE result_type operator()( const N& n
                                     , const A0& x, const INCX & incx
                                     , const A1& y, const INCY & incy) const
    {
      nt2_la_int in = n;
      nt2_la_int ix = incx;
      nt2_la_int iy = incy;
      result_type r;
      NT2_F77NAME(zdotu) (&r, &in, x.raw(), &ix, y.raw(), &iy);
      return r;
    }
  };

} }

#endif
