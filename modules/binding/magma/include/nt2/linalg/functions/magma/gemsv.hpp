//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_MAGMA_GEMSV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_MAGMA_GEMSV_HPP_INCLUDED

#if defined(NT2_USE_MAGMA)

#include <nt2/linalg/functions/gemsv.hpp>
#include <nt2/linalg/details/magma_buffer.hpp>
#include <nt2/sdk/magma/magma.hpp>

#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/core/container/table/kind.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>

#include <nt2/core/container/table/table.hpp>

#include <magma.h>
#include <cublas.h>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( gemsv_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(A2)(S2)(site)
                            , ((container_<nt2::tag::table_,  double_<A0>, S0 >)) //A
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >)) //B
                              ((container_<nt2::tag::table_,  double_<A2>, S2 >)) //X
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1 const& a1, A2& a2) const
     {
        nt2_la_int  n  = std::min(nt2::height(a0),nt2::width(a0));
        nt2_la_int  lda = n;
        nt2_la_int  nhrs = nt2::width(a1);
        nt2_la_int  ldb = a1.leading_size();
        nt2_la_int iter,info;

        nt2::container::table<double> copyb(nt2::of_size(ldb,nhrs));
        copyb = a1;

        nt2::container::table<nt2_la_int> ipiv(nt2::of_size(n,1));

        details::magma_buffer<float>      swork(n*(n+nhrs),1);
        details::magma_buffer<double>     dwork(n*nhrs,1);
        details::magma_buffer<nt2_la_int> dipiv(n,1);



        details::magma_buffer<double>     dA(n,n   ,a0.data());
        details::magma_buffer<double>     dB(n,nhrs, copyb.data());
        details::magma_buffer<double>     dX(n,nhrs);

        magma_dsgesv_gpu( MagmaNoTrans       , n          , nhrs
                        , dA.data()          , lda        , ipiv.data()
                        , dipiv.data()       , dB.data()   , ldb
                        , dX.data()          , ldb        , dwork.data()
                        , swork.data()       , &iter      , &info
                        );

        dX.raw( a2.data() );
        return iter;
     }
  };


  BOOST_DISPATCH_IMPLEMENT  ( gemsv_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(A2)(S2)(site)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >)) // A
                              ((container_< nt2::tag::table_, complex_<double_<A1> >, S1 >)) // B
                              ((container_< nt2::tag::table_, complex_<double_<A2> >, S2 >)) // X
                            )
  {
     typedef nt2_la_int result_type;
     typedef std::complex<double> dComplex;
     typedef cuDoubleComplex* mT;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        nt2_la_int  n  = std::min(nt2::height(a0),nt2::width(a0));
        nt2_la_int  lda = n;
        nt2_la_int  nhrs = nt2::width(a1);
        nt2_la_int  ldb = a1.leading_size();
        nt2_la_int iter,info;

        nt2::container::table<nt2_la_int> ipiv(nt2::of_size(n,1));
        A1 copyb(a1);

        details::magma_buffer<std::complex<float> >      swork(n*(n+nhrs),1);
        details::magma_buffer<dComplex>                  dwork(n*nhrs,1);
        details::magma_buffer<nt2_la_int>                dipiv(n,1);

        details::magma_buffer<dComplex>     dA(n,n   ,a0.data());
        details::magma_buffer<dComplex>     dB(n,nhrs, copyb.data());
        details::magma_buffer<dComplex>     dX(n,nhrs);

        magma_zcgesv_gpu( MagmaNoTrans                  , n          , nhrs
                        , (cuDoubleComplex*)dA.data()   , lda        , ipiv.data()
                        , dipiv.data(), (cuDoubleComplex*)dB.data()   , ldb
                        , (cuDoubleComplex*)dX.data()   , ldb        , (cuDoubleComplex*)dwork.data()
                        , (cuFloatComplex*)swork.data(), &iter      , &info
                        );

        dX.raw( a2.data() );
        return iter;
     }
  };
} }

#endif

#endif
