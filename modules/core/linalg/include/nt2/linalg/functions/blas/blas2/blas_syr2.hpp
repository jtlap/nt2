//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapreste
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_BLAS2_SYR2_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_BLAS2_SYR2_HPP_INCLUDED

#include <nt2/linalg/functions/blas_syr2.hpp>
#include <nt2/linalg/details/blas/blas2.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{

//---------------------------------------------Real-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_syr2_, tag::cpu_
                            , (UPLO)(ALPHA)(X)(SX)(INCX)(Y)(SY)(INCY)(A)(SA)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<single_<ALPHA>>)// alpha
                              ((container_<nt2::tag::table_,  single_<X>, SX >)) //x
                              (scalar_<integer_<INCX>>)// incx
                              ((container_<nt2::tag::table_,  single_<Y>, SY >)) //y
                              (scalar_<integer_<INCY>>)// incy
                              ((container_<nt2::tag::table_,  single_<A>, SA >)) //a
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const ALPHA& alpha
                                     , const X& x, const INCX & incx
                                     , const Y& y, const INCY & incy
                                     , A& a) const
    {
      nt2_la_int n = width(a);
      nt2_la_int lda = n;
      nt2_la_int ix = incx;
      nt2_la_int iy = incy;
      NT2_F77NAME(ssyr2) (&uplo, &n, &alpha, x.raw(), &ix, y.raw(), &iy, a.raw(), &lda);
    }
  };

//---------------------------------------------Real-double------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_syr2_, tag::cpu_
                            , (UPLO)(ALPHA)(X)(SX)(INCX)(Y)(SY)(INCY)(A)(SA)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<double_<ALPHA>>)// alpha
                              ((container_<nt2::tag::table_,  double_<X>, SX >)) //x
                              (scalar_<integer_<INCX>>)// incx
                              ((container_<nt2::tag::table_,  double_<Y>, SY >)) //y
                              (scalar_<integer_<INCY>>)// incy
                              ((container_<nt2::tag::table_,  double_<A>, SA >)) //a
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const ALPHA& alpha
                                     , const X& x, const INCX & incx
                                     , const Y& y, const INCY & incy
                                     , A& a) const
    {
      nt2_la_int n = width(a);
      nt2_la_int lda = n;
      nt2_la_int ix = incx;
      nt2_la_int iy = incy;
      NT2_F77NAME(dsyr2) (&uplo, &n, &alpha, x.raw(), &ix, y.raw(), &iy, a.raw(), &lda);
    }
  };

//---------------------------------------------Complex-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_syr2_, tag::cpu_
                            , (UPLO)(ALPHA)(X)(SX)(INCX)(Y)(SY)(INCY)(A)(SA)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<complex_<single_<ALPHA>>>)// n
                              ((container_<nt2::tag::table_,  complex_<single_<X>>, SX >)) //x
                              (scalar_<integer_<INCX>>)// incx
                              ((container_<nt2::tag::table_,  complex_<single_<Y>>, SY >)) //y
                              (scalar_<integer_<INCY>>)// incy
                              ((container_<nt2::tag::table_,  complex_<single_<A>>, SA >)) //a
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const ALPHA& alpha
                                     , const X& x, const INCX & incx
                                     , const Y& y, const INCY & incy
                                     , A& a) const
    {
      nt2_la_int n = width(a);
      nt2_la_int lda = n;
      nt2_la_int ix = incx;
      nt2_la_int iy = incy;
      NT2_F77NAME(cher2)(&uplo, &n, &alpha, x.raw(), &ix, y.raw(), &iy, a.raw(), &lda);
    }
  };

//---------------------------------------------Complex-double------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_syr2_, tag::cpu_
                            , (UPLO)(ALPHA)(X)(SX)(INCX)(Y)(SY)(INCY)(A)(SA)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<complex_<double_<ALPHA>>>)// n
                              ((container_<nt2::tag::table_,  complex_<double_<X>>, SX >)) //x
                              (scalar_<integer_<INCX>>)// incx
                              ((container_<nt2::tag::table_,  complex_<double_<Y>>, SY >)) //y
                              (scalar_<integer_<INCY>>)// incy
                              ((container_<nt2::tag::table_,  complex_<double_<A>>, SA >)) //a
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const ALPHA& alpha
                                     , const X& x, const INCX & incx
                                     , const Y& y, const INCY & incy
                                     , A& a) const
    {
      nt2_la_int n = width(a);
      nt2_la_int lda = n;
      nt2_la_int ix = incx;
      nt2_la_int iy = incy;
      NT2_F77NAME(zher2) (&uplo, &n, &alpha, x.raw(), &ix, y.raw(), &iy, a.raw(), &lda);
    }
  };

} }

#endif
