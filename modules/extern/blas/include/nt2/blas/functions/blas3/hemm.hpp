//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BLAS_FUNCTIONS_BLAS3_HEMM_HPP_INCLUDED
#define NT2_BLAS_FUNCTIONS_BLAS3_HEMM_HPP_INCLUDED

#include <nt2/blas/functions/hemm.hpp>
#include <nt2/blas/details/blas3.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/blas/details/wrapper.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/sdk/memory/container.hpp>

namespace nt2 { namespace blas { namespace ext
{

// /---------------------------------------------Real-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( hemm_, tag::cpu_
                            , (SIDE)(UPLO)(ALPHA)(A)(SA)(B)(SB)(BETA)(C)(SC)
                            , (scalar_<int8_<SIDE>>)// side
                              (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<single_<ALPHA>>)//alpha
                              ((container_<nt2::tag::table_,  single_<A>, SA >)) //a
                              ((container_<nt2::tag::table_,  single_<B>, SB >)) //b
                              (scalar_<single_<BETA>>)// beta
                              ((container_<nt2::tag::table_,  single_<C>, SC >)) //c
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const SIDE& side
                                     , const UPLO& uplo
                                     , const ALPHA& alpha
                                     , const A& a
                                     , const B& b
                                     , const BETA beta
                                     , C& c
                                     ) const
    {
      nt2_la_int m = height(c); //((side == 'N')||(side == 'n')) ? height(a) : width(a);
      nt2_la_int n = width(c);  //((uplo == 'N')||(uplo == 'n')) ? height(b) : width(b);
      nt2_la_int lda = a.leading_size();
      nt2_la_int ldb = b.leading_size();
      nt2_la_int ldc = c.leading_size();
      NT2_F77NAME(ssymm) (&side, &uplo, &m, &n, &alpha, a.data(), &lda, b.data(), &ldb, &beta, c.data(), &ldc);
    }
  };

// /---------------------------------------------Real-double------------------------------------------------//
  BOOST_DISPATCH_IMPLEMENT  ( hemm_, tag::cpu_
                            , (SIDE)(UPLO)(ALPHA)(A)(SA)(B)(SB)(BETA)(C)(SC)
                            , (scalar_<int8_<SIDE>>)// side
                              (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<double_<ALPHA>>)//alpha
                              ((container_<nt2::tag::table_,  double_<A>, SA >)) //a
                              ((container_<nt2::tag::table_,  double_<B>, SB >)) //b
                              (scalar_<double_<BETA>>)// beta
                              ((container_<nt2::tag::table_,  double_<C>, SC >)) //c
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const SIDE& side
                                     , const UPLO& uplo
                                     , const ALPHA& alpha
                                     , const A& a
                                     , const B& b
                                     , const BETA& beta
                                     , C& c
                                     ) const
    {
      nt2_la_int m = height(c); //((side == 'N')||(side == 'n')) ? height(a) : width(a);
      nt2_la_int n = width(c);  //((uplo == 'N')||(uplo == 'n')) ? height(b) : width(b);
      nt2_la_int lda = a.leading_size();
      nt2_la_int ldb = b.leading_size();
      nt2_la_int ldc = c.leading_size();
      NT2_F77NAME(dsymm)  (&side, &uplo, &m, &n, &alpha, a.data(), &lda, b.data(), &ldb, &beta, c.data(), &ldc);
    }
  };



// /---------------------------------------------Complex-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( hemm_, tag::cpu_
                            , (SIDE)(UPLO)(ALPHA)(A)(SA)(B)(SB)(BETA)(C)(SC)
                            , (scalar_<int8_<SIDE>>)// side
                              (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<complex_<single_<ALPHA>>>)//alpha
                              ((container_<nt2::tag::table_, complex_<single_<A>>, SA >)) //a
                              ((container_<nt2::tag::table_, complex_<single_<B>>, SB >)) //b
                              (scalar_<complex_<single_<BETA>>>)// beta
                              ((container_<nt2::tag::table_, complex_<single_<C>>, SC >)) //c
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const SIDE& side
                                     , const UPLO& uplo
                                     , const ALPHA& alpha
                                     , const A& a
                                     , const B& b
                                     , const BETA& beta
                                     , C& c
                                     ) const
    {
      nt2_la_int m = height(c); //((side == 'N')||(side == 'n')) ? height(a) : width(a);
      nt2_la_int n = width(c);  //((uplo == 'N')||(uplo == 'n')) ? height(b) : width(b);
      nt2_la_int lda = a.leading_size();
      nt2_la_int ldb = b.leading_size();
      nt2_la_int ldc = c.leading_size();
      NT2_F77NAME(chemm) (&side, &uplo, &m, &n, &alpha, a.data(), &lda, b.data(), &ldb, &beta, c.data(), &ldc);
    }
  };

// /---------------------------------------------Complex-double------------------------------------------------//
  BOOST_DISPATCH_IMPLEMENT  ( hemm_, tag::cpu_
                            , (SIDE)(UPLO)(ALPHA)(A)(SA)(B)(SB)(BETA)(C)(SC)
                            , (scalar_<int8_<SIDE>>)// side
                              (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<complex_<double_<ALPHA>>>)//alpha
                              ((container_<nt2::tag::table_, complex_<double_<A>>, SA >)) //a
                              ((container_<nt2::tag::table_, complex_<double_<B>>, SB >)) //b
                              (scalar_<complex_<double_<BETA>>>)// beta
                              ((container_<nt2::tag::table_, complex_<double_<C>>, SC >)) //c
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const SIDE& side
                                     , const UPLO& uplo
                                     , const ALPHA& alpha
                                     , const A& a
                                     , const B& b
                                     , const BETA& beta
                                     , C& c
                                     ) const
    {
      nt2_la_int m = height(c); //((side == 'N')||(side == 'n')) ? height(a) : width(a);
      nt2_la_int n = width(c);  //((uplo == 'N')||(uplo == 'n')) ? height(b) : width(b);
      nt2_la_int lda = a.leading_size();
      nt2_la_int ldb = b.leading_size();
      nt2_la_int ldc = c.leading_size();
      NT2_F77NAME(zhemm) (&side, &uplo, &m, &n, &alpha, a.data(), &lda, b.data(), &ldb, &beta, c.data(), &ldc);
    }
  };


}  } }

#endif
