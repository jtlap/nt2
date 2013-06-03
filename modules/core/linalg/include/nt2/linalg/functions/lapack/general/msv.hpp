//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_MSV_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_MSV_HPP_INCLUDED

#include <nt2/linalg/functions/msv.hpp>
#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/core/container/table/category.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>

#include <nt2/table.hpp>

extern "C"
{
  void NT2_F77NAME(dsgesv)( const nt2_la_int* n, const nt2_la_int* nrhs
                         , double* a           , const nt2_la_int* lda
                         , nt2_la_int* ipiv
                         , double* b           , const nt2_la_int* ldb
                         , double* x           , const nt2_la_int* ldx
                         , double* work        , float* swork
                         , nt2_la_int* iter    , nt2_la_int* info
                         );
}

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::msv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((expr_ < table_< double_<A0>, S0 >     //A
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< double_<A1>, S1 >    //B
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< double_<A2>, S2 >     //X
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        details::workspace<typename A2::value_type> w;
        nt2_la_int  n  = std::min(nt2::height(a0),nt2::width(a0));
        nt2_la_int  lda = n;
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = a2.leading_size();
        nt2_la_int iter,info;

        nt2::table<float> swork(nt2::of_size(n*(n+nhrs),1));
        nt2::table<nt2_la_int> ipiv(nt2::of_size(n,1));
        w.resize_main(n*nhrs);

        NT2_F77NAME(dsgesv)( &n, &nhrs, a0.raw(), &lda, ipiv.raw() , a1.raw()
                           , &ldb, a2.raw(), &ldb , w.main(), swork.raw()
                           , &iter, &info
                           );

        return iter;
     }
  };

} }

#endif
