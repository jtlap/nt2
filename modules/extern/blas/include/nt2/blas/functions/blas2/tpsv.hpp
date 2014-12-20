//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BLAS_FUNCTIONS_BLAS2_TPSV_HPP_INCLUDED
#define NT2_BLAS_FUNCTIONS_BLAS2_TPSV_HPP_INCLUDED

#include <nt2/blas/functions/tpsv.hpp>
#include <nt2/blas/details/blas2.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/blas/details/wrapper.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/iround.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/constants/eight.hpp>

namespace nt2 { namespace blas { namespace ext
{

// /---------------------------------------------Real-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( tpsv_, tag::cpu_
                            , (UPLO)(TRANS)(DIAG)(A)(SA)(X)(SX)(INCX)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<int8_<TRANS>>)// trans
                              (scalar_<int8_<DIAG>>)//diag
                              ((container_<nt2::tag::table_,  single_<A>, SA >)) //a
                              ((container_<nt2::tag::table_,  single_<X>, SX >)) //x
                              (scalar_<integer_<INCX>>)// incx
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const TRANS& trans
                                     , const DIAG& diag
                                     , const A& a
                                     , X& x, const INCX & incx
                                     ) const
    {
      nt2_la_int n = iround(sqrt(oneplus(Eight<size_t>()*numel(a)))) >> 1;
      nt2_la_int ix= incx;
      NT2_F77NAME(stpsv)  (&uplo, &trans, &diag, &n, a.data(), x.data(), &ix);
    }
  };

// /---------------------------------------------Real-double------------------------------------------------//
  BOOST_DISPATCH_IMPLEMENT  ( tpsv_, tag::cpu_
                            , (UPLO)(TRANS)(DIAG)(A)(SA)(X)(SX)(INCX)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<int8_<TRANS>>)// trans
                              (scalar_<int8_<DIAG>>)//diag
                              ((container_<nt2::tag::table_,  double_<A>, SA >)) //a
                              ((container_<nt2::tag::table_,  double_<X>, SX >)) //y
                              (scalar_<integer_<INCX>>)// incx
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const TRANS& trans
                                     , const DIAG& diag
                                     , const A& a
                                     , X& x, const INCX & incx
                                     ) const
    {
      nt2_la_int n = iround(sqrt(oneplus(Eight<size_t>()*numel(a)))) >> 1;
      nt2_la_int ix= incx;
      NT2_F77NAME(dtpsv) (&uplo, &trans, &diag, &n, a.data(), x.data(), &ix);
    }
  };



// /---------------------------------------------Complex-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( tpsv_, tag::cpu_
                            , (UPLO)(TRANS)(DIAG)(A)(SA)(X)(SX)(INCX)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<int8_<TRANS>>)// trans
                              (scalar_<int8_<DIAG>>)//diag
                              ((container_<nt2::tag::table_,  complex_<single_<A>>, SA >)) //a
                              ((container_<nt2::tag::table_,  complex_<single_<X>>, SX >)) //y
                              (scalar_<integer_<INCX>>)// incx
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const TRANS& trans
                                     , const DIAG& diag
                                     , const A& a
                                     , X& x, const INCX & incx
                                     ) const
    {
      nt2_la_int n = iround(sqrt(oneplus(Eight<size_t>()*numel(a)))) >> 1;
      nt2_la_int ix= incx;
      NT2_F77NAME(ctpsv) (&uplo, &trans, &diag, &n, a.data(), x.data(), &ix);
    }
  };

// /---------------------------------------------Complex-double------------------------------------------------//
  BOOST_DISPATCH_IMPLEMENT  ( tpsv_, tag::cpu_
                            , (UPLO)(TRANS)(DIAG)(A)(SA)(X)(SX)(INCX)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<int8_<TRANS>>)// trans
                              (scalar_<int8_<DIAG>>)//diag
                              ((container_<nt2::tag::table_,  complex_<double_<A>>, SA >)) //a
                              ((container_<nt2::tag::table_,  complex_<double_<X>>, SX >)) //y
                              (scalar_<integer_<INCX>>)// incx
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const TRANS& trans
                                     , const DIAG& diag
                                     , const A& a
                                     , X& x, const INCX & incx
                                     ) const
    {
      nt2_la_int n = iround(sqrt(oneplus(Eight<size_t>()*numel(a)))) >> 1;
      nt2_la_int ix= incx;
      NT2_F77NAME(ztpsv) (&uplo, &trans, &diag, &n, a.data(), x.data(), &ix);
    }
  };


}  } }

#endif
