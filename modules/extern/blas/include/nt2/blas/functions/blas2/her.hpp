//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapreste
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BLAS_FUNCTIONS_BLAS2_HER_HPP_INCLUDED
#define NT2_BLAS_FUNCTIONS_BLAS2_HER_HPP_INCLUDED

#include <nt2/blas/functions/her.hpp>
#include <nt2/blas/details/blas2.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/blas/details/wrapper.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/core/container/table/table.hpp>
#include <complex>

namespace nt2 { namespace blas { namespace ext
{

//---------------------------------------------Real-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( her_, tag::cpu_
                            , (UPLO)(ALPHA)(X)(SX)(INCX)(A)(SA)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<single_<ALPHA>>)// alpha
                              ((container_<nt2::tag::table_,  single_<X>, SX >)) //x
                              (scalar_<integer_<INCX>>)// incx
                              ((container_<nt2::tag::table_,  single_<A>, SA >)) //a
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const ALPHA& alpha
                                     , const X& x, const INCX & incx
                                     , A& a) const
    {
      nt2_la_int n = width(a);
      nt2_la_int lda = a.leading_size();
      nt2_la_int ix = incx;
      NT2_F77NAME(ssyr) (&uplo, &n, &alpha, x.data(), &ix, a.data(), &lda);
    }
  };

//---------------------------------------------Real-double------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( her_, tag::cpu_
                            , (UPLO)(ALPHA)(X)(SX)(INCX)(A)(SA)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<double_<ALPHA>>)// alpha
                              ((container_<nt2::tag::table_,  double_<X>, SX >)) //x
                              (scalar_<integer_<INCX>>)// incx
                              ((container_<nt2::tag::table_,  double_<A>, SA >)) //a
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     ,  const ALPHA& alpha
                                     , const X& x, const INCX & incx
                                     , A& a) const
    {
      nt2_la_int n = width(a);
      nt2_la_int lda = a.leading_size();
      nt2_la_int ix = incx;
      NT2_F77NAME(dsyr) (&uplo, &n, &alpha, x.data(), &ix, a.data(), &lda);
    }
  };

//---------------------------------------------Complex-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( her_, tag::cpu_
                            , (UPLO)(ALPHA)(X)(SX)(INCX)(A)(SA)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<single_<ALPHA>>)// alpha
                              ((container_<nt2::tag::table_,  complex_<single_<X>>, SX >)) //x
                              (scalar_<integer_<INCX>>)// incx
                              ((container_<nt2::tag::table_,  complex_<single_<A>>, SA >)) //a
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const ALPHA& alpha
                                     , const X& x, const INCX & incx
                                     , A& a) const
    {
      nt2_la_int n = width(a);
      nt2_la_int lda = a.leading_size();
      nt2_la_int ix = incx;
      NT2_F77NAME(cher)(&uplo, &n, &alpha, x.data(), &ix, a.data(), &lda);
    }
  };

//---------------------------------------------Complex-double------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( her_, tag::cpu_
                            , (UPLO)(ALPHA)(X)(SX)(INCX)(A)(SA)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<double_<ALPHA>>)// alpha
                              ((container_<nt2::tag::table_,  complex_<double_<X>>, SX >)) //x
                              (scalar_<integer_<INCX>>)// incx
                              ((container_<nt2::tag::table_,  complex_<double_<A>>, SA >)) //a
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const ALPHA& alpha
                                     , const X& x, const INCX & incx
                                     , A& a) const
    {
      nt2_la_int n = width(a);
      nt2_la_int lda = a.leading_size();
      nt2_la_int ix = incx;
      NT2_F77NAME(zher) (&uplo, &n, &alpha, x.data(), &ix, a.data(), &lda);
    }
  };

}  } }

#endif
