//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_SYCON_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_SYCON_HPP_INCLUDED

#include <nt2/linalg/functions/sycon.hpp>
#include <nt2/core/container/table/kind.hpp>
#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

#include <nt2/table.hpp>

extern "C"
{
  void NT2_F77NAME(dsycon)( const char* uplo     , const nt2_la_int* n
                          , const double* a      , const nt2_la_int* lda
                          , const nt2_la_int* ipiv
                          , const double* anorm  , double* rcond
                          , double* work         , nt2_la_int* iwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(ssycon)( const char* uplo     , const nt2_la_int* n
                          , const float* a       , const nt2_la_int* lda
                          , const nt2_la_int* ipiv
                          , const float* anorm   , float* rcond
                          , float* work          , nt2_la_int* iwork
                          , nt2_la_int* info
                          );
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sycon_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)
                            , ((expr_ < container_< nt2::tag::table_, double_<A0>, S0 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < container_< nt2::tag::table_, integer_<A1>, S1 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              (scalar_< floating_<A2> >)            //  anorm
                            )
  {
    typedef double  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&a1, A2 const& a2) const
    {
      result_type rcond;
      nt2_la_int n = nt2::height(a0);
      nt2_la_int ld = n;
      nt2_la_int info;
      char uplo = 'L';

      nt2::table<result_type> work(nt2::of_size(4*n,1));
      nt2::table<nt2_la_int>  iwork(nt2::of_size(n,1));

      NT2_F77NAME(dsycon) ( &uplo, &n, a0.raw(), &ld, a1.raw(), &a2, &rcond
                          , work.raw(), iwork.raw(), &info
                          );

      return rcond;
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sycon_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)
                            , ((expr_ < container_< nt2::tag::table_, single_<A0>, S0 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < container_< nt2::tag::table_, integer_<A1>, S1 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              (scalar_< floating_<A2> >)            //  anorm
                            )
  {
    typedef float result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2 const& a2) const
    {
      result_type rcond;
      nt2_la_int n = nt2::height(a0);
      nt2_la_int ld = n;
      nt2_la_int info;
      char uplo = 'L';

      nt2::table<result_type> work(nt2::of_size(4*n,1));
      nt2::table<nt2_la_int>  iwork(nt2::of_size(n,1));

      NT2_F77NAME(ssycon) ( &uplo, &n, a0.raw(), &ld, a1.raw(), &a2, &rcond
                          , work.raw(), iwork.raw(), &info
                          );

      return rcond;
    }
  };
} }

#endif
