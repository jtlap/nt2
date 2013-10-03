//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_LANGB_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_LANGB_HPP_INCLUDED

#include <nt2/linalg/functions/langb.hpp>
#include <nt2/core/container/table/kind.hpp>
#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/table.hpp>

#include <stdio.h>

extern "C"
{
  double NT2_F77NAME(dlangb)( const char* norm     , const nt2_la_int* n
                          , const nt2_la_int* KL   , const nt2_la_int* KB
                          , const double* ab
                          , const nt2_la_int* ldab , double* work
                          );

  double NT2_F77NAME(slangb)( const char* norm     , const nt2_la_int* n
                          , const nt2_la_int* KL   , const nt2_la_int* KB
                          , const float* ab
                          , const nt2_la_int* ldab , float* work
                          );
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::langb_, tag::cpu_
                            , (A0)(S0)(A1)
                            , ((expr_ < container_< nt2::tag::table_, double_<A0>, S0 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              (scalar_< ints8_<A1> >)             //  norm
                            )
  {
    typedef double  result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1 a1) const
    {

      typedef typename meta::option<typename A0::settings_type,nt2::tag::shape_>::type shape;
      result_type norm;
      nt2_la_int n = nt2::width(a0);
      nt2_la_int ku = shape::ud;
      nt2_la_int kl = shape::ld;
      nt2_la_int ld = kl+ku+1;

     if(a1 =='I')
     {
        nt2::table<result_type> work(nt2::of_size(n,1));
        norm = NT2_F77NAME(dlangb)( &a1, &n, &kl, &ku, a0.raw(), &ld, work.raw());
      }
      else
      {
        norm = NT2_F77NAME(dlangb)( &a1, &n, &kl, &ku, a0.raw(), &ld, 0);
      }

      return norm;
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::langb_, tag::cpu_
                            , (A0)(S0)(A1)
                            , ((expr_ < container_< nt2::tag::table_, single_<A0>, S0 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              (scalar_< ints8_<A1> >)             //  norm
                            )
  {
    typedef float result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1 a1) const
    {

      typedef typename meta::option<typename A0::settings_type,nt2::tag::shape_>::type shape;
      result_type norm;
      nt2_la_int n = nt2::width(a0);
      nt2_la_int ku = shape::ud;
      nt2_la_int kl = shape::ld;
      nt2_la_int ld = kl+ku+1;

     if(a1 =='I')
     {
        nt2::table<result_type> work(nt2::of_size(n,1));
        norm = NT2_F77NAME(slangb)( &a1, &n, &kl, &ku, a0.raw(), &ld, work.raw());
      }
      else
      {
        norm = NT2_F77NAME(slangb)( &a1, &n, &kl, &ku, a0.raw(), &ld, 0);
      }

      return norm;
    }
  };

} }

#endif
