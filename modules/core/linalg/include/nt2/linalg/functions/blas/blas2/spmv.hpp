//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_BLAS2_SPMV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_BLAS2_SPMV_HPP_INCLUDED

#include <nt2/linalg/functions/blas_spmv.hpp>
#include <nt2/linalg/details/blas/blas2.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/iround.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/constants/eight.hpp>
namespace nt2 { namespace ext
{
// /---------------------------------------------Real-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_spmv_, tag::cpu_
                            , (UPLO)(ALPHA)(A)(SA)(X)(SX)(INCX)(BETA)(Y)(SY)(INCY)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<single_<ALPHA>>)//alpha
                              ((container_<nt2::tag::table_,  single_<A>, SA >)) //a
                              ((container_<nt2::tag::table_,  single_<X>, SX >)) //x
                              (scalar_<integer_<INCX>>)// incx
                              (scalar_<single_<BETA>>)// beta
                              ((container_<nt2::tag::table_,  single_<Y>, SY >)) //y
                              (scalar_<integer_<INCY>>)// incy
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const ALPHA& alpha
                                     , const A& a
                                     , const X& x, const INCX & incx
                                     , const BETA beta
                                     , Y& y, const INCY & incy
                                     ) const
    {
      size_t nn = numel(a);
      nt2_la_int n = iround(sqrt(oneplus(Eight<size_t>()*nn))) >> 1;
      nt2_la_int ix= incx;
      nt2_la_int iy= incy;
      NT2_F77NAME(sspmv) (&uplo, &n, &alpha, a.raw(), x.raw(), &ix, &beta, y.raw(), &iy);
    }
  };

// /---------------------------------------------Real-double------------------------------------------------//
  BOOST_DISPATCH_IMPLEMENT  ( blas_spmv_, tag::cpu_
                            , (UPLO)(ALPHA)(A)(SA)(X)(SX)(INCX)(BETA)(Y)(SY)(INCY)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<double_<ALPHA>>)//alpha
                              ((container_<nt2::tag::table_,  double_<A>, SA >)) //a
                              ((container_<nt2::tag::table_,  double_<X>, SX >)) //y
                              (scalar_<integer_<INCX>>)// incx
                              (scalar_<double_<BETA>>)// beta
                              ((container_<nt2::tag::table_,  double_<Y>, SY >)) //dparam
                              (scalar_<integer_<INCY>>)// incy
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const ALPHA& alpha
                                     , const A& a
                                     , const X& x, const INCX & incx
                                     , const BETA& beta
                                     , Y& y, const INCY & incy
                                     ) const
    {
      size_t nn = numel(a);
      nt2_la_int n = iround(sqrt(oneplus(Eight<size_t>()*nn))) >> 1;
      nt2_la_int ix= incx;
      nt2_la_int iy= incy;
      NT2_F77NAME(dspmv) (&uplo, &n, &alpha, a.raw(), x.raw(), &ix, &beta, y.raw(), &iy);
    }
  };



// /---------------------------------------------Complex-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_spmv_, tag::cpu_
                            , (UPLO)(ALPHA)(A)(SA)(X)(SX)(INCX)(BETA)(Y)(SY)(INCY)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<complex_<single_<ALPHA>>>)//alpha
                              ((container_<nt2::tag::table_,  complex_<single_<A>>, SA >)) //a
                              ((container_<nt2::tag::table_,  complex_<single_<X>>, SX >)) //y
                              (scalar_<integer_<INCX>>)// incx
                              (scalar_<complex_<single_<BETA>>>)// beta
                              ((container_<nt2::tag::table_,  complex_<single_<Y>>, SY >)) //dparam
                              (scalar_<integer_<INCY>>)// incy
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const ALPHA& alpha
                                     , const A& a
                                     , const X& x, const INCX & incx
                                     , const BETA& beta
                                     , Y& y, const INCY & incy
                                     ) const
    {
      size_t nn = numel(a);
      nt2_la_int n = iround(sqrt(oneplus(Eight<size_t>()*nn))) >> 1;
      nt2_la_int ix= incx;
      nt2_la_int iy= incy;
      NT2_F77NAME(cspmv) (&uplo, &n, &alpha, a.raw(), x.raw(), &ix, &beta, y.raw(), &iy);
    }
  };

// /---------------------------------------------Complex-double------------------------------------------------//
  BOOST_DISPATCH_IMPLEMENT  ( blas_spmv_, tag::cpu_
                            , (UPLO)(ALPHA)(A)(SA)(X)(SX)(INCX)(BETA)(Y)(SY)(INCY)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<complex_<double_<ALPHA>>>)//alpha
                              ((container_<nt2::tag::table_,  complex_<double_<A>>, SA >)) //a
                              ((container_<nt2::tag::table_,  complex_<double_<X>>, SX >)) //y
                              (scalar_<integer_<INCX>>)// incx
                              (scalar_<complex_<double_<BETA>>>)// beta
                              ((container_<nt2::tag::table_,  complex_<double_<Y>>, SY >)) //dparam
                              (scalar_<integer_<INCY>>)// incy
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const ALPHA& alpha
                                     , const A& a
                                     , const X& x, const INCX & incx
                                     , const BETA& beta
                                     , Y& y, const INCY & incy
                                     ) const
    {
      size_t nn = numel(a);
      nt2_la_int n = iround(sqrt(oneplus(Eight<size_t>()*nn))) >> 1;
      nt2_la_int ix= incx;
      nt2_la_int iy= incy;
      NT2_F77NAME(zspmv) (&uplo, &n, &alpha, a.raw(), x.raw(), &ix, &beta, y.raw(), &iy);
    }
  };


} }

#endif
