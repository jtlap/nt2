//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_MAGMA_POSV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_MAGMA_POSV_HPP_INCLUDED

#if defined(NT2_USE_MAGMA)

#include <nt2/linalg/functions/posv.hpp>
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
  BOOST_DISPATCH_IMPLEMENT  ( posv_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(site)
                            , ((container_<nt2::tag::table_,  double_<A0>, S0 >))
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >))
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
     {
        result_type that;
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  ldb = a1.leading_size();
        nt2_la_int  nhrs = nt2::width(a1);

        magma_dposv( MagmaLower, n, nhrs, a0.data(), ld, a1.data(), ldb, &that);

        return that;
     }
  };

  BOOST_DISPATCH_IMPLEMENT  ( posv_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(site)
                            , ((container_<nt2::tag::table_,  single_<A0>, S0 >))
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >))
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
     {
        result_type that;
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  ldb = a1.leading_size();
        nt2_la_int  nhrs = nt2::width(a1);

        magma_sposv( MagmaLower, n, nhrs, a0.data(), ld, a1.data(), ldb , &that );

        return that;
     }
  };

  /// INTERNAL ONLY
  BOOST_DISPATCH_IMPLEMENT  ( posv_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(site)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))   // A
                              ((container_< nt2::tag::table_, complex_<double_<A1> >, S1 >))   // B
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
     {
        result_type that;
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  ldb = a1.leading_size();
        nt2_la_int  nhrs = nt2::width(a1);

        magma_zposv( MagmaLower, n, nhrs, (cuDoubleComplex*)a0.data(), ld, (cuDoubleComplex*)a1.data(), ldb , &that );

        return that;
     }
  };

  /// INTERNAL ONLY
  BOOST_DISPATCH_IMPLEMENT  ( posv_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(site)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))   // A
                              ((container_< nt2::tag::table_, complex_<single_<A1> >, S1 >))   // B
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
     {
        result_type that;
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  ldb = a1.leading_size();
        nt2_la_int  nhrs = nt2::width(a1);

        magma_cposv( MagmaLower, n, nhrs, (cuFloatComplex*)a0.data(), ld, (cuFloatComplex*) a1.data(), ldb, &that);

        return that;
     }
  };

} }

#endif
#endif

