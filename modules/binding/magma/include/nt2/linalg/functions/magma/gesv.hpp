//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_MAGMA_GESV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_MAGMA_GESV_HPP_INCLUDED

#if defined(NT2_USE_MAGMA)

#include <nt2/linalg/functions/gesv.hpp>
#include <nt2/include/functions/xerbla.hpp>
#include <nt2/sdk/magma/magma.hpp>

#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/core/container/table/kind.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

#include <magma.h>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesv_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(A2)(S2)(site)
                            , ((container_<nt2::tag::table_,  double_<A0>, S0 >))
                              ((container_<nt2::tag::table_,  integer_<A1>, S1 >))
                              ((container_<nt2::tag::table_,  double_<A2>, S2 >))
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        result_type that;
        nt2_la_int  n  = std::min(nt2::height(a0),nt2::width(a0));
        nt2_la_int  lda = n;
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = a2.leading_size();

        a1.resize(nt2::of_size(n,1));
        magma_dgesv(n,nhrs,a0.raw(),lda,a1.raw(),a2.raw(),ldb,&that);

        return that;
     }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesv_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(A2)(S2)(site)
                            , ((container_<nt2::tag::table_,  single_<A0>, S0 >))
                              ((container_<nt2::tag::table_,  integer_<A1>, S1 >))
                              ((container_<nt2::tag::table_,  single_<A2>, S2 >))
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        result_type that;
        nt2_la_int  n  = std::min(nt2::height(a0),nt2::width(a0));
        nt2_la_int  lda = n;
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = a2.leading_size();

        a1.resize(nt2::of_size(n,1));

        magma_sgesv(n,nhrs,a0.raw(),lda,a1.raw(),a2.raw(),ldb,&that);

        return that;
     }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesv_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(A2)(S2)(site)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))  // A
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >)) // IPIV
                              ((container_< nt2::tag::table_, complex_<double_<A2> >, S2 >))   // B
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        result_type that;
        nt2_la_int  n  = std::min(nt2::height(a0),nt2::width(a0));
        nt2_la_int  lda = n;
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = a2.leading_size();

        a1.resize(nt2::of_size(n,1));

        magma_zgesv(n,nhrs,(cuDoubleComplex*)a0.raw(),lda,a1.raw()
                   ,(cuDoubleComplex*)a2.raw(),ldb,&that);

        return that;
     }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesv_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(A2)(S2)(site)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))  // A
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >)) // IPIV
                              ((container_< nt2::tag::table_, complex_<single_<A2> >, S2 >))   // B
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        result_type that;
        nt2_la_int  n  = std::min(nt2::height(a0),nt2::width(a0));
        nt2_la_int  lda = n;
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = a2.leading_size();

        a1.resize(nt2::of_size(n,1));

        magma_cgesv(n,nhrs,(cuFloatComplex*)a0.raw(),lda,a1.raw()
                   ,(cuDoubleComplex*)a2.raw(),ldb,&that);

        return that;
     }
  };
} }

#endif
#endif

