//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_LASWP_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_LASWP_HPP_INCLUDED

#include <nt2/linalg/functions/laswp.hpp>
#include <nt2/core/container/table/category.hpp>
#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

extern "C"
{
  void NT2_F77NAME(dlaswp)( const nt2_la_int* n     , double* a
                          , const nt2_la_int* lda   , const nt2_la_int* k1
                          , const nt2_la_int* k2    , const nt2_la_int* ipiv
                          , const nt2_la_int* incx
                          );

  void NT2_F77NAME(slaswp)( const nt2_la_int* n     , float* a
                          , const nt2_la_int* lda   , const nt2_la_int* k1
                          , const nt2_la_int* k2    , const nt2_la_int* ipiv
                          , const nt2_la_int* incx
                          );
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::laswp_, tag::cpu_
                            , (A0)(S0)(A1)(S1)
                            , ((expr_ < table_< double_<A0>, S0 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< integer_<A1>, S1 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                            )
  {
    typedef void  result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      nt2_la_int n = nt2::width(a0);
      nt2_la_int ld = a0.leading_size();
      nt2_la_int k1 = 1;
      nt2_la_int k2 = a1.leading_size();
      nt2_la_int incx = 1;

      NT2_F77NAME(dlaswp) ( &n, a0.raw(), &ld, &k1, &k2 , a1.raw(), &incx);
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::laswp_, tag::cpu_
                            , (A0)(S0)(A1)(S1)
                            , ((expr_ < table_< single_<A0>, S0 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< integer_<A1>, S1 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                            )
  {
    typedef void  result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      nt2_la_int n = nt2::width(a0);
      nt2_la_int ld = a0.leading_size();
      nt2_la_int k1 = 1;
      nt2_la_int k2 = a1.leading_size();
      nt2_la_int incx = 1;


      NT2_F77NAME(slaswp) ( &n, a0.raw(), &ld, &k1, &k2 , a1.raw(), &incx);
    }
  };
} }

#endif
