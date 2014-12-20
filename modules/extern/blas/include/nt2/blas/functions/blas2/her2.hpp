//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapreste
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BLAS_FUNCTIONS_BLAS2_HER2_HPP_INCLUDED
#define NT2_BLAS_FUNCTIONS_BLAS2_HER2_HPP_INCLUDED

#include <nt2/blas/functions/her2.hpp>
#include <nt2/blas/details/blas2.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/blas/details/wrapper.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace blas { namespace ext
{

//---------------------------------------------Real-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( her2_, tag::cpu_
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
      nt2_la_int lda = a.leading_size();
      nt2_la_int ix = incx;
      nt2_la_int iy = incy;
      NT2_F77NAME(ssyr2) (&uplo, &n, &alpha, x.data(), &ix, y.data(), &iy, a.data(), &lda);
    }
  };

//---------------------------------------------Real-double------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( her2_, tag::cpu_
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
      nt2_la_int lda = a.leading_size();
      nt2_la_int ix = incx;
      nt2_la_int iy = incy;
      NT2_F77NAME(dsyr2) (&uplo, &n, &alpha, x.data(), &ix, y.data(), &iy, a.data(), &lda);
    }
  };

//---------------------------------------------Complex-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( her2_, tag::cpu_
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
      nt2_la_int lda = a.leading_size();
      nt2_la_int ix = incx;
      nt2_la_int iy = incy;
      NT2_F77NAME(cher2)(&uplo, &n, &alpha, x.data(), &ix, y.data(), &iy, a.data(), &lda);
    }
  };

//---------------------------------------------Complex-double------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( her2_, tag::cpu_
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
      nt2_la_int lda = a.leading_size();
      nt2_la_int ix = incx;
      nt2_la_int iy = incy;
      NT2_F77NAME(zher2) (&uplo, &n, &alpha, x.data(), &ix, y.data(), &iy, a.data(), &lda);
    }
  };

}  } }

#endif
