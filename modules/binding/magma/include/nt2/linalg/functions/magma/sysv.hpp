//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_MAGMA_SYSV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_MAGMA_SYSV_HPP_INCLUDED

#if defined(NT2_USE_MAGMA)

#include <nt2/linalg/functions/sysv.hpp>
#include <nt2/sdk/magma/magma.hpp>

#include <nt2/include/functions/width.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

#include <magma.h>
#include <iostream>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY - Compute the workspace
  BOOST_DISPATCH_IMPLEMENT  ( sysv_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(A2)(S2)(site)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))  // A
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >)) // PIV
                              ((container_< nt2::tag::table_, double_<A2>, S2 >))  // B
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        result_type that;
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  ldb = a2.leading_size();
        nt2_la_int  nhrs = nt2::width(a2);
        magma_uplo_t uplo = MagmaLower;

        magma_dsysv( uplo, n, nhrs, a0.data(), ld, a1.data(), a2.data()
                           , ldb, &that
                            );

        return that;
     }
  };


  /// INTERNAL ONLY - Compute the workspace
  BOOST_DISPATCH_IMPLEMENT  ( sysv_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(A2)(S2)(site)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))  // A
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >)) // PIV
                              ((container_< nt2::tag::table_, single_<A2>, S2 >))  // B
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        result_type that;
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  ldb = a2.leading_size();
        nt2_la_int  nhrs = nt2::width(a2);
        magma_uplo_t uplo = MagmaLower;

        magma_ssysv( uplo, n, nhrs, a0.data(), ld, a1.data(), a2.data()
                           , ldb, &that
                            );
        return that;
     }
  };


//--------------------------------------------Complex-----------------------------------------//

  /// INTERNAL ONLY - Compute the workspace
  BOOST_DISPATCH_IMPLEMENT  ( sysv_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(A2)(S2)(site)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))  // A
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >)) // PIV
                              ((container_< nt2::tag::table_, complex_<double_<A2> >, S2 >))  // B
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        result_type that;
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  ldb = a2.leading_size();
        nt2_la_int  nhrs = nt2::width(a2);
        magma_uplo_t uplo = MagmaLower;

      magma_zsysv ( uplo, n, nhrs, a0.data(), ld, a1.data(), a2.data()
                           , ldb, &that
                            );

        return that;
     }
  };


  /// INTERNAL ONLY - Compute the workspace
  BOOST_DISPATCH_IMPLEMENT  ( sysv_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(A2)(S2)(site)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))  // A
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >)) // PIV
                              ((container_< nt2::tag::table_, complex_<single_<A2> >, S2 >))  // B
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        result_type that;
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  ldb = a2.leading_size();
        nt2_la_int  nhrs = nt2::width(a2);
        magma_uplo_t uplo = MagmaLower;

        magma_csysv ( uplo, n, nhrs, a0.data(), ld, a1.data(), a2.data()
                           , ldb, &that
                            );

        return that;
     }
  };

}
}

#endif
#endif

