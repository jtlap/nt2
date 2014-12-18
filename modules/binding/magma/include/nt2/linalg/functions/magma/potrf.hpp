//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_MAGMA_POTRF_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_MAGMA_POTRF_HPP_INCLUDED

#if defined(NT2_USE_MAGMA)

#include <nt2/linalg/functions/potrf.hpp>
#include <nt2/include/functions/xerbla.hpp>
#include <nt2/sdk/magma/magma.hpp>

#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/core/container/table/kind.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

#include <magma.h>
#include <cctype>


namespace nt2 { namespace ext
{
  /// INTERNAL ONLY -
  BOOST_DISPATCH_IMPLEMENT  ( potrf_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(site)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))
                              (scalar_< ints8_<A1> >)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1 const a1) const
     {
        result_type that;
        nt2_la_int n   = nt2::width(a0);
        nt2_la_int lda = a0.leading_size();

        char c = std::toupper(a1);
        magma_uplo_t uplo = c == 'L' ? MagmaLower : c == 'U' ? MagmaUpper : (magma_uplo_t)0;

        magma_dpotrf(uplo,n,a0.data(),lda,&that);

        return that;
     }
  };


  /// INTERNAL ONLY -
  BOOST_DISPATCH_IMPLEMENT  ( potrf_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(site)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))
                              (scalar_< ints8_<A1> >)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1 const a1) const
     {
        result_type that;
        nt2_la_int n   = nt2::width(a0);
        nt2_la_int lda = a0.leading_size();

        char c = std::toupper(a1);
        magma_uplo_t uplo = c == 'L' ? MagmaLower : c == 'U' ? MagmaUpper : (magma_uplo_t)0;

        magma_spotrf(uplo,n,a0.data(),lda,&that);

        return that;
     }
  };


  /// INTERNAL ONLY -
  BOOST_DISPATCH_IMPLEMENT  ( potrf_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(site)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))
                              (scalar_< ints8_<A1> >)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1 const a1) const
     {
        result_type that;
        nt2_la_int n   = nt2::width(a0);
        nt2_la_int lda = a0.leading_size();

        char c = std::toupper(a1);
        magma_uplo_t uplo = c == 'L' ? MagmaLower : c == 'U' ? MagmaUpper : (magma_uplo_t)0;

        magma_zpotrf(uplo,n,(cuDoubleComplex*)a0.data(),lda,&that);

        return that;
     }
  };


  /// INTERNAL ONLY -
  BOOST_DISPATCH_IMPLEMENT  ( potrf_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(site)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))
                              (scalar_< ints8_<A1> >)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1 const a1) const
     {
        result_type that;
        nt2_la_int n   = nt2::width(a0);
        nt2_la_int lda = a0.leading_size();

        char c = std::toupper(a1);
        magma_uplo_t uplo = c == 'L' ? MagmaLower : c == 'U' ? MagmaUpper : (magma_uplo_t)0;

        magma_cpotrf(uplo,n,(cuFloatComplex*)a0.data(),lda,&that);

        return that;
     }
  };
} }

#endif

#endif
