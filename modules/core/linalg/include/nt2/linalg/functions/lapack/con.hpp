//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_CON_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_CON_HPP_INCLUDED

#include <nt2/linalg/functions/con.hpp>
#include <nt2/core/container/table/category.hpp>
#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

#include <nt2/table.hpp>

extern "C"
{
  void NT2_F77NAME(dgecon)( const char* norm     , const nt2_la_int* n
                          , double* a            , const nt2_la_int* lda
                          , const double* anorm  , double* rcond
                          , double* work         , nt2_la_int* iwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(sgecon)( const char* norm     , const nt2_la_int* n
                          , float* a             , const nt2_la_int* lda
                          , const float* anorm  , float* rcond
                          , float* work          , nt2_la_int* iwork
                          , nt2_la_int* info
                          );
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::con_, tag::cpu_
                            , (A0)(S0)(A1)(A2)
                            , ((expr_ < table_< double_<A0>, S0 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              (scalar_< ints8_<A1> >)            //  norm
                              (scalar_< floating_<A2> >)            //  anorm
                            )
  {
    typedef double  result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1 a1, A2 a2) const
    {
      result_type rcond;
      nt2_la_int n = nt2::height(a0);
      nt2_la_int ld = n;
      nt2_la_int info;

      nt2::table<result_type> work(nt2::of_size(4*n,1));
      nt2::table<nt2_la_int>  iwork(nt2::of_size(n,1));

      NT2_F77NAME(dgecon) ( &a1, &n, a0.raw(), &ld, &a2, &rcond , work.raw()
                          , iwork.raw(), &info
                          );

      return rcond;
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::con_, tag::cpu_
                            , (A0)(S0)(A1)(A2)
                            , ((expr_ < table_< single_<A0>, S0 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              (scalar_< ints8_<A1> >)             //  norm
                              (scalar_< floating_<A2> >)            //  anorm
                            )
  {
    typedef float result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1 a1, A2 a2) const
    {
      result_type rcond;
      nt2_la_int n = nt2::height(a0);
      nt2_la_int ld = n;
      nt2_la_int info;

      nt2::table<result_type> work(nt2::of_size(4*n,1));
      nt2::table<nt2_la_int>  iwork(nt2::of_size(n,1));

      NT2_F77NAME(sgecon) ( &a1, &n, a0.raw(), &ld, &a2, &rcond , work.raw()
                          , iwork.raw(), &info
                          );

      return rcond;
    }
  };
} }

#endif
