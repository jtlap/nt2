//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_LSY_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_LSY_HPP_INCLUDED

#include <nt2/linalg/functions/lsy.hpp>
#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/core/container/table/category.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>


#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/constants/sqrteps.hpp>
#include <nt2/include/constants/eps.hpp>

#include <nt2/table.hpp>

extern "C"
{
  void NT2_F77NAME(dgelsy)( const nt2_la_int* m    , const nt2_la_int* n
                         ,  const nt2_la_int* nhrs , double* a
                         ,  const nt2_la_int* lda  , double* b
                         ,  const nt2_la_int* ldb  , nt2_la_int* jpvt
                         ,  const double* rcond    , nt2_la_int* rank
                         ,  double* work           , const nt2_la_int* lwork
                         ,  nt2_la_int* info
                         );

  void NT2_F77NAME(sgelsy)( const nt2_la_int* m    , const nt2_la_int* n
                         ,  const nt2_la_int* nhrs , float* a
                         ,  const nt2_la_int* lda  , float* b
                         ,  const nt2_la_int* ldb  , nt2_la_int* jpvt
                         ,  const float* rcond     , nt2_la_int* rank
                         ,  float* work            , const nt2_la_int* lwork
                         ,  nt2_la_int* info
                         );
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lsy_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((expr_ < table_< double_<A0>, S0 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< double_<A1>, S1 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< integer_<A2>, S2 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        result_type that;
        nt2_la_int rank;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  nhrs = nt2::width(a1);
        nt2_la_int  ldb = a1.leading_size();
        typedef  double T ;
        T rcond =  Sqrteps<T>() - (Sqrteps<T>() - Eps<T>())/2;

        NT2_F77NAME(dgelsy) (&m, &n, &nhrs, 0, &ld, 0, &ldb, 0, &rcond, &rank
                            , w.main(), details::query(), &that
                            );

          a2 = nt2::zeros<nt2_la_int>(n,1);
          w.prepare_main();
          nt2::lsy(a0,a1,a2,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Compute with rank as output
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lsy_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((expr_ < table_< double_<A0>, S0 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< double_<A1>, S1 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< integer_<A2>, S2 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              (scalar_< integer_<A3> > )   //rank
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  nhrs = nt2::width(a1);
        nt2_la_int  ldb = a1.leading_size();
        typedef  double T ;
        T rcond =  Sqrteps<T>() - (Sqrteps<T>() - Eps<T>())/2;

        NT2_F77NAME(dgelsy) (&m, &n, &nhrs, 0, &ld, 0, &ldb, 0, &rcond, &a3
                            , w.main(), details::query(), &that
                            );

        a2 = nt2::zeros<nt2_la_int>(n,1);
        w.prepare_main();
        nt2_la_int  wn = w.main_size();

        NT2_F77NAME(dgelsy) (&m, &n, &nhrs, a0.raw(), &ld, a1.raw(), &ldb
                            , a2.raw(), &rcond, &a3, w.main()
                            , &wn, &that
                            );

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lsy_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((expr_ < table_< double_<A0>, S0 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< double_<A1>, S1 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< integer_<A2>, S2 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                             (unspecified_<A3>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2, A3& a3) const
     {
        result_type that;
        nt2_la_int rank;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  wn = a3.main_size();
        nt2_la_int  nhrs = nt2::width(a1);
        nt2_la_int  ldb = a1.leading_size();
        typedef double T ;
        T rcond = Sqrteps<T>() - (Sqrteps<T>() - Eps<T>())/2;

        a2 = nt2::zeros<nt2_la_int>(n,1);

        NT2_F77NAME(dgelsy) (&m, &n, &nhrs, a0.raw(), &ld, a1.raw(), &ldb
                            , a2.raw(), &rcond, &rank, a3.main()
                            , &wn, &that
                            );

        return that;
     }
  };

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lsy_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((expr_ < table_< single_<A0>, S0 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< single_<A1>, S1 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< integer_<A2>, S2 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        result_type that;
        nt2_la_int rank;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  nhrs = nt2::width(a1);
        nt2_la_int  ldb = a1.leading_size();
        typedef float T ;
        T rcond = Sqrteps<T>() - (Sqrteps<T>() - Eps<T>())/2;

        NT2_F77NAME(sgelsy) (&m, &n, &nhrs, 0, &ld, 0, &ldb, 0, &rcond, &rank
                            , w.main(), details::query(), &that
                            );

          a2 = nt2::zeros<nt2_la_int>(n,1);
          w.prepare_main();
          nt2::lsy(a0,a1,a2,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Compute with rank as output
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lsy_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((expr_ < table_< single_<A0>, S0 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< single_<A1>, S1 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< integer_<A2>, S2 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              (scalar_< integer_<A3> > )   //rank
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  nhrs = nt2::width(a1);
        nt2_la_int  ldb = a1.leading_size();
        typedef  float T ;
        T rcond =  Sqrteps<T>() - (Sqrteps<T>() - Eps<T>())/2;

        NT2_F77NAME(sgelsy) (&m, &n, &nhrs, 0, &ld, 0, &ldb, 0, &rcond, &a3
                            , w.main(), details::query(), &that
                            );

        a2 = nt2::zeros<nt2_la_int>(n,1);
        w.prepare_main();
        nt2_la_int  wn = w.main_size();

        NT2_F77NAME(sgelsy) (&m, &n, &nhrs, a0.raw(), &ld, a1.raw(), &ldb
                            , a2.raw(), &rcond, &a3, w.main()
                            , &wn, &that
                            );

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lsy_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((expr_ < table_< single_<A0>, S0 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< single_<A1>, S1 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< integer_<A2>, S2 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                             (unspecified_<A3>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2, A3& a3) const
     {
        result_type that;
        nt2_la_int rank;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  wn = a3.main_size();
        nt2_la_int  nhrs = nt2::width(a1);
        nt2_la_int  ldb = a1.leading_size();
        typedef float T ;
        T rcond = Sqrteps<T>() - (Sqrteps<T>() - Eps<T>())/2;

        a2 = nt2::zeros<nt2_la_int>(n,1);

        NT2_F77NAME(sgelsy) (&m, &n, &nhrs, a0.raw(), &ld, a1.raw(), &ldb
                            , a2.raw(), &rcond, &rank, a3.main()
                            , &wn, &that
                            );

        return that;
     }
  };


} }

#endif
