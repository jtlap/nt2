//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_MAGMA_MSV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_MAGMA_MSV_HPP_INCLUDED

#if defined(NT2_USE_MAGMA)

#include <nt2/linalg/functions/msv.hpp>
#include <nt2/linalg/details/magma_buffer.hpp>
#include <nt2/sdk/magma/magma.hpp>

#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/core/container/table/category.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>

#include <nt2/table.hpp>

#include <magma.h>
#include <cublas.h>
#include <stdio.h>


namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::msv_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(A2)(S2)(site)
                            , ((expr_ < table_< double_<A0>, S0 >     //A
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< double_<A1>, S1 >     //B
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
        nt2_la_int  n  = std::min(nt2::height(a0),nt2::width(a0));
        nt2_la_int  lda = n;
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = a2.leading_size();
        nt2_la_int iter,info;
        char trans = 'N';

        nt2::table<nt2_la_int> ipiv(nt2::of_size(n,1));

        details::magma_buffer<float>      swork(n*(n+nhrs),1);
        details::magma_buffer<double>     dwork(n*nhrs,1);
        details::magma_buffer<nt2_la_int> dipiv(n,1);

        details::magma_buffer<double>     dA(n,n   ,a0.raw());
        details::magma_buffer<double>     dB(n,nhrs, a1.raw());
        details::magma_buffer<double>     dX(n,nhrs);

        magma_dsgesv_gpu( trans             , n          , nhrs
                        , dA.raw()          , lda        , ipiv.raw()
                        , dipiv.raw()       , dB.raw()   , ldb
                        , dX.raw()          , ldb        , dwork.raw()
                        , swork.raw()       , &iter      , &info
                        );

        dX.raw( a2.raw() );
        return iter;
     }
  };

} }

#endif

#endif
