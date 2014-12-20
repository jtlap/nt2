//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BLAS_FUNCTIONS_BLAS2_SYMV_HPP_INCLUDED
#define NT2_BLAS_FUNCTIONS_BLAS2_SYMV_HPP_INCLUDED

#include <nt2/blas/functions/symv.hpp>
#include <nt2/blas/details/blas2.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/blas/details/wrapper.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/sdk/memory/container.hpp>

namespace nt2 { namespace blas { namespace ext
{
// _SYMV (        UPLO,      M,         ALPHA, A, LDA, X, INCX, BETA,  Y, INCY ) S, D
// _HEMV (        UPLO,      M,         ALPHA, A, LDA, X, INCX, BETA,  Y, INCY ) C, Z

// /---------------------------------------------Real-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( symv_, tag::cpu_
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
      nt2_la_int n = height(a);
      nt2_la_int lda = a.leading_size();
      nt2_la_int ix= incx;
      nt2_la_int iy= incy;
      NT2_F77NAME(ssymv) (&uplo, &n, &alpha, a.data(), &lda, x.data(), &ix, &beta, y.data(), &iy);
    }
  };

// /---------------------------------------------Real-double------------------------------------------------//
  BOOST_DISPATCH_IMPLEMENT  ( symv_, tag::cpu_
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
      nt2_la_int n = height(a);
      nt2_la_int lda = a.leading_size();
      nt2_la_int ix= incx;
      nt2_la_int iy= incy;
      NT2_F77NAME(dsymv) (&uplo, &n, &alpha, a.data(), &lda, x.data(), &ix, &beta, y.data(), &iy);
    }
  };



// /---------------------------------------------Complex-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( symv_, tag::cpu_
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
      nt2_la_int n = height(a);
      nt2_la_int lda = a.leading_size();
      nt2_la_int ix= incx;
      nt2_la_int iy= incy;
      NT2_F77NAME(csymv) (&uplo, &n, &alpha, a.data(), &lda, x.data(), &ix, &beta, y.data(), &iy);
    }
  };

// /---------------------------------------------Complex-double------------------------------------------------//
  BOOST_DISPATCH_IMPLEMENT  ( symv_, tag::cpu_
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
      nt2_la_int n = height(a);
      nt2_la_int lda = a.leading_size();
      nt2_la_int ix= incx;
      nt2_la_int iy= incy;
      NT2_F77NAME(zsymv) (&uplo, &n, &alpha, a.data(), &lda, x.data(), &ix, &beta, y.data(), &iy);
    }
  };


}  } }

#endif
