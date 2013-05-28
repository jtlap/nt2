//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_LANGE_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_LANGE_HPP_INCLUDED

#include <nt2/linalg/functions/lange.hpp>
#include <nt2/core/container/table/category.hpp>
#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

extern "C"
{
  double NT2_F77NAME(dlange)( const char* norm     , const nt2_la_int* m
                          , const nt2_la_int* n    , const double* a
                          , const nt2_la_int* lda  , double* work
                          );

  float NT2_F77NAME(slange)( const char* norm      , const nt2_la_int* m
                          , const nt2_la_int* n    , const float* a
                          , const nt2_la_int* lda  , float* work
                          );
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lange_, tag::cpu_
                            , (A0)(S0)(A1)
                            , ((expr_ < table_< double_<A0>, S0 >
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
      result_type norm;
      nt2_la_int m = nt2::height(a0);
      nt2_la_int n = nt2::width(a0);
      nt2_la_int ld = m;

     if(a1 =='I')
     {
        nt2::table<result_type> work(nt2::of_size(m,1));
        norm = NT2_F77NAME(dlange)( &a1, &m, &n, a0.raw(), &ld, work.raw());
      }
      else
      {
        norm = NT2_F77NAME(dlange)( &a1, &m, &n, a0.raw(), &ld, 0);
      }

      return norm;
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lange_, tag::cpu_
                            , (A0)(S0)(A1)
                            , ((expr_ < table_< single_<A0>, S0 >
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
      result_type norm;
      nt2_la_int m = nt2::height(a0);
      nt2_la_int n = nt2::width(a0);
      nt2_la_int ld = m;

      if(a1 =='I')
      {
        nt2::table<result_type> work(nt2::of_size(m,1));
        norm = NT2_F77NAME(slange)( &a1, &m, &n, a0.raw(), &ld, work.raw());
      }
      else
      {
        norm = NT2_F77NAME(slange)( &a1, &m, &n, a0.raw(), &ld, 0);
      }

      return norm;
    }
  };
} }

#endif
