//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_MQR_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_MQR_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/mqr.hpp>
#include <nt2/include/functions/xerbla.hpp>

#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/core/container/table/category.hpp>
#include <nt2/core/utility/numeric_class.hpp>
#include <nt2/toolbox/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/toolbox/linalg/details/utility/options.hpp>
#include <nt2/toolbox/linalg/details/utility/workspace.hpp>
#include <nt2/toolbox/linalg/details/utility/exception.hpp>

#include <nt2/table.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/eye.hpp>

extern "C"
{
  void NT2_F77NAME(dormqr)( const char* side        , const char* trans
                          , const nt2_la_int* m     , const nt2_la_int* n
                          , const nt2_la_int* k     , const double* a
                          , const nt2_la_int* lda   , const double* tau
                          , double* c               , const nt2_la_int* ldc
                          , double* work            , const nt2_la_int* lwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(sormqr)( const char* side        , const char* trans
                          , const nt2_la_int* m     , const nt2_la_int* n
                          , const nt2_la_int* k     , const float* a
                          , const nt2_la_int* lda   , const float* tau
                          , float* c                , const nt2_la_int* ldc
                          , float* work             , const nt2_la_int* lwork
                          , nt2_la_int* info
                          );
}


namespace nt2 { namespace ext
{
  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mqr_, tag::cpu_
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
                              ((expr_ < table_< double_<A2>, S2 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2) const
     {
        result_type that;
        details::workspace<typename A2::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  k  = a1.leading_size();
        char side  = 'L';
        char trans = 'N';

        a2= eye(m,m);

        NT2_F77NAME(dormqr) (&side,&trans,&m, &m, &k, 0, &ld, 0, 0, &m, w.main()
                            , details::query(), &that
                            );
        w.prepare_main();
        nt2::mqr(a0,a1,a2,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mqr_, tag::cpu_
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
                              ((expr_ < table_< double_<A2>, S2 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                             (unspecified_<A3>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2,A3& a3) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  wn = a3.main_size();
        nt2_la_int  k  = a1.leading_size();
        char side  = 'L';
        char trans = 'N';

        a2 = eye(m,m);

        NT2_F77NAME(dormqr) ( &side, &trans, &m, &m, &k, a0.raw(), &ld, a1.raw()
                            , a2.raw(), &m, a3.main(), &wn, &that
                            );
        return that;
     }
  };

   /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mqr_, tag::cpu_
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
                              ((expr_ < table_< single_<A2>, S2 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2) const
     {
        result_type that;
        details::workspace<typename A2::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  k  = a1.leading_size();
        char side  = 'L';
        char trans = 'N';

        a2 = eye(m,m,nt2::single_);

        NT2_F77NAME(sormqr) (&side,&trans,&m, &m, &k, 0, &ld, 0, 0, &m, w.main()
                            , details::query(), &that
                            );
        w.prepare_main();

        nt2::mqr(a0,a1,a2,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mqr_, tag::cpu_
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
                              ((expr_ < table_< single_<A2>, S2 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                             (unspecified_<A3>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2,A3& a3) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  wn = a3.main_size();
        nt2_la_int  k  = a1.leading_size();
        char side  = 'L';
        char trans = 'N';

        a2 = eye(m,m, nt2::single_);

        NT2_F77NAME(sormqr) ( &side, &trans, &m, &m, &k, a0.raw(), &m, a1.raw()
                            , a2.raw(), &m, a3.main(), &wn, &that
                            );
        return that;
     }
  };

} }

#endif
