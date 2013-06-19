//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_YSV_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_YSV_HPP_INCLUDED

#include <nt2/linalg/functions/ysv.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/core/container/table/category.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

#include <nt2/table.hpp>

extern "C"
{
  void NT2_F77NAME(dsysv)(  const char* uplo         , const nt2_la_int* n
                          , const nt2_la_int* nhrs   , double* a
                          , const nt2_la_int* lda    , nt2_la_int* ipiv
                          , double* b                , const nt2_la_int* ldb
                          , double* work             , const nt2_la_int* lwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(ssysv)(  const char* uplo         , const nt2_la_int* n
                          , const nt2_la_int* nhrs   , float* a
                          , const nt2_la_int* lda    , nt2_la_int* ipiv
                          , float* b                 , const nt2_la_int* ldb
                          , float* work              , const nt2_la_int* lwork
                          , nt2_la_int* info
                          );
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ysv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)
                            , ((expr_ < table_< double_<A0>, S0 >     // A
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< integer_<A1>, S1 >    // PIV
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< double_<A2>, S2 >     // B
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< double_<A3>, S3 >     // X
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  ldb = a2.leading_size();
        nt2_la_int  nhrs = nt2::width(a2);
        char uplo = 'L';

        NT2_F77NAME(dsysv) (&uplo, &n, &nhrs, 0, &ld, 0, 0, &ldb, w.main()
                            , details::query(), &that
                            );

          a1 = nt2::zeros<nt2_la_int>(n,1);
          w.prepare_main();
          nt2::ysv(a0,a1,a2,a3,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ysv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)
                            , ((expr_ < table_< double_<A0>, S0 >   // A
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< integer_<A1>, S1 >  // PIV
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< double_<A2>, S2 >   // B
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< double_<A3>, S3 >   // X
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                             (unspecified_<A4>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2, A3& a3, A4& a4) const
     {
        result_type that;
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  ldb = a2.leading_size();
        nt2_la_int  nhrs = nt2::width(a2);
        char uplo = 'L';
        nt2_la_int  wn = a4.main_size();

        a1 = nt2::zeros<nt2_la_int>(n,1);

        NT2_F77NAME(dsysv) ( &uplo, &n, &nhrs, a0.raw(), &ld, a1.raw(), a3.raw()
                           , &ldb, a4.main(), &wn, &that
                            );
        return that;
     }
  };

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ysv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)
                            , ((expr_ < table_< single_<A0>, S0 >     // A
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< integer_<A1>, S1 >    // PIV
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< single_<A2>, S2 >     // B
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< single_<A3>, S3 >     // X
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  ldb = a2.leading_size();
        nt2_la_int  nhrs = nt2::width(a2);
        char uplo = 'L';

        NT2_F77NAME(ssysv) (&uplo, &n, &nhrs, 0, &ld, 0, 0, &ldb, w.main()
                            , details::query(), &that
                            );

          a1 = nt2::zeros<nt2_la_int>(n,1);
          w.prepare_main();
          nt2::ysv(a0,a1,a2,a3,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ysv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)
                            , ((expr_ < table_< single_<A0>, S0 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< integer_<A1>, S1 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< single_<A2>, S2 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< single_<A3>, S3 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                             (unspecified_<A4>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2, A3& a3, A4& a4) const
     {
        result_type that;
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  ldb = a2.leading_size();
        nt2_la_int  nhrs = nt2::width(a2);
        char uplo = 'L';
        nt2_la_int  wn = a4.main_size();

        a1 = nt2::zeros<nt2_la_int>(n,1);

        NT2_F77NAME(ssysv) ( &uplo, &n, &nhrs, a0.raw(), &ld, a1.raw(), a3.raw()
                           , &ldb, a4.main(), &wn, &that
                            );
        return that;
     }
  };
} }

#endif
