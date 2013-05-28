//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_GQR_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_GQR_HPP_INCLUDED

#include <nt2/linalg/functions/gqr.hpp>
#include <nt2/include/functions/xerbla.hpp>
#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/core/container/table/category.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/options.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>


#include <nt2/table.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>

extern "C"
{
  void NT2_F77NAME(dorgqr)( const nt2_la_int* m     , const nt2_la_int* n
                          , const nt2_la_int* k     , double* a
                          , const nt2_la_int* lda   , const double* tau
                          , double* work            , const nt2_la_int* lwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(sorgqr)( const nt2_la_int* m     , const nt2_la_int* n
                          , const nt2_la_int* k     , float* a
                          , const nt2_la_int* lda   , const float* tau
                          , float* work             , const nt2_la_int* lwork
                          , nt2_la_int* info
                          );

}


namespace nt2 { namespace ext
{
  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gqr_, tag::cpu_
                            , (A0)(S0)(A1)(S1)
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
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  k  = a1.leading_size();

        NT2_F77NAME(dorgqr) (&m, &n, &k, 0, &ld, 0, w.main()
                            , details::query(), &that
                            );

          w.prepare_main();
          nt2::gqr(a0,a1,w);


        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gqr_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)
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
                             (unspecified_<A2>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  wn = a2.main_size();
        nt2_la_int  k  = a1.leading_size();

        NT2_F77NAME(dorgqr) (&m, &n, &k, a0.raw(), &ld, a1.raw(), a2.main()
                            , &wn, &that
                            );
        return that;
     }
  };

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gqr_, tag::cpu_
                            , (A0)(S0)(A1)(S1)
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
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  k  = a1.leading_size();

        details::workspace<typename A0::value_type> w;

        NT2_F77NAME(sorgqr)(&m, &n, &k,  0, &ld, 0, w.main()
                          , details::query(), &that
                           );

        w.prepare_main();
        nt2::gqr(a0,a1,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gqr_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)
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
                             (unspecified_<A2>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  wn = a2.main_size();
        nt2_la_int  k  = a1.leading_size();


        NT2_F77NAME(sorgqr) (&m, &n, &k, a0.raw(), &ld, a1.raw(), a2.main()
                            , &wn, &that
                            );
        return that;
     }
  };
} }

#endif
