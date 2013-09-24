//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_GBCON_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_GBCON_HPP_INCLUDED

#include <nt2/linalg/functions/gbcon.hpp>
#include <nt2/core/container/table/category.hpp>
#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

#include <iostream>
#include <nt2/table.hpp>

extern "C"
{
  void NT2_F77NAME(dgbcon)( const char* norm     , const nt2_la_int* n
                          , const nt2_la_int* kl , const nt2_la_int* ku
                          , const double* a      , const nt2_la_int* lda
                          , const nt2_la_int* ipiv
                          , const double* anorm  , double* rcond
                          , double* work         , nt2_la_int* iwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(sgbcon)( const char* norm     , const nt2_la_int* n
                          , const nt2_la_int* kl , const nt2_la_int* ku
                          , const float* a       , const nt2_la_int* lda
                          , const nt2_la_int* ipiv
                          , const float * anorm  , float* rcond
                          , float* work          , nt2_la_int* iwork
                          , nt2_la_int* info
                          );

}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gbcon_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)
                            , ((expr_ < table_< double_<A0>, S0 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< integer_<A1>, S1 >  // ipiv
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              (scalar_< floating_<A2> >)            //  anorm
                            )
  {
    typedef double  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&a1, A2 const& a2) const
    {

      typedef typename meta::option<typename A0::settings_type,nt2::tag::shape_>::type shape;
      result_type rcond;
      nt2_la_int n = nt2::width(a0);
      nt2_la_int ku = shape::ud;
      nt2_la_int kl = shape::ld;
      nt2_la_int ld = n;
      nt2_la_int info;
      char norm = '1';

      nt2::table<result_type> work(nt2::of_size(3*n,1));
      nt2::table<nt2_la_int>  iwork(nt2::of_size(n,1));

      NT2_F77NAME(dgbcon) ( &norm, &n, &ku, &kl, a0.raw(), &ld, a1.raw(), &a2, &rcond
                          , work.raw(), iwork.raw(), &info
                          );

      return rcond;
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gbcon_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)
                            , ((expr_ < table_< single_<A0>, S0 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< integer_<A1>, S1 >  // ipiv
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              (scalar_< floating_<A2> >)            //  anorm
                            )
  {
    typedef float  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&a1, A2 const& a2) const
    {

      typedef typename meta::option<typename A0::settings_type,nt2::tag::shape_>::type shape;
      result_type rcond;
      nt2_la_int n = nt2::width(a0);
      nt2_la_int ku = shape::ud;
      nt2_la_int kl = shape::ld;
      nt2_la_int ld = n;
      nt2_la_int info;
      char norm = '1';

      nt2::table<result_type> work(nt2::of_size(3*n,1));
      nt2::table<nt2_la_int>  iwork(nt2::of_size(n,1));

      NT2_F77NAME(sgbcon) ( &norm, &n, &ku, &kl, a0.raw(), &ld, a1.raw(), &a2, &rcond
                          , work.raw(), iwork.raw(), &info
                          );

      return rcond;
    }
  };

} }

#endif
