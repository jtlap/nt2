//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_TRF_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_TRF_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/trf.hpp>

#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/core/container/table/category.hpp>
#include <nt2/toolbox/linalg/details/utility/f77_wrapper.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>

extern "C"
{
  void NT2_F77NAME(dgetrf)( const nt2_la_int* m , const nt2_la_int* n
                          , double* a           , const nt2_la_int* lda
                          , nt2_la_int* ipiv    , nt2_la_int* info
                          );

  void NT2_F77NAME(sgetrf)( const nt2_la_int* m , const nt2_la_int* n
                          , float* a            , const nt2_la_int* lda
                          , nt2_la_int* ipiv    , nt2_la_int* info
                          );
}

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::trf_, tag::cpu_
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
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();

        a1.resize( nt2::of_size(std::min(n, m), 1) );

        NT2_F77NAME(dgetrf)(&m, &n, a0.raw(), &ld, a1.raw(), &that);

        return that;
     }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::trf_, tag::cpu_
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
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();

        a1.resize( nt2::of_size(std::min(n, m), 1) );

        NT2_F77NAME(sgetrf)(&m, &n, a0.raw(), &ld, a1.raw(), &that);

        return that;
     }
  };
} }

#endif
