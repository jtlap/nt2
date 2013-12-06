//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_QP3_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_QP3_HPP_INCLUDED

#include <nt2/linalg/functions/qp3.hpp>
#include <nt2/include/functions/xerbla.hpp>
#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/core/container/table/kind.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/options.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
#include <nt2/linalg/details/utility/exception.hpp>

#include <nt2/table.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/zeros.hpp>

extern "C"
{
  void NT2_F77NAME(dgeqp3)( const nt2_la_int* m  , const nt2_la_int* n
                          , double* a            , const nt2_la_int* lda
                          , nt2_la_int* jpvt     , double* tau
                          , double* work         , const nt2_la_int* lwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(sgeqp3)( const nt2_la_int* m  , const nt2_la_int* n
                          , float* a             , const nt2_la_int* lda
                          , nt2_la_int* jpvt     , float* tau
                          , float* work          , const nt2_la_int* lwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(cgeqp3)( const nt2_la_int* m  , const nt2_la_int* n
                          , nt2_la_complex* a    , const nt2_la_int* lda
                          , nt2_la_int* jpvt     , nt2_la_complex* tau
                          , nt2_la_complex* work , const nt2_la_int* lwork
                          , float* rwork         , nt2_la_int* info
                          );

  void NT2_F77NAME(zgeqp3)( const nt2_la_int* m  , const nt2_la_int* n
                          , nt2_la_complex* a    , const nt2_la_int* lda
                          , nt2_la_int* jpvt     , nt2_la_complex* tau
                          , nt2_la_complex* work , const nt2_la_int* lwork
                          , double* rwork        , nt2_la_int* info
                          );
}




namespace nt2 { namespace ext
{
  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::qp3_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              ((container_< nt2::tag::table_, double_<A2>, S2 >))
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();

        NT2_F77NAME(dgeqp3) (&m, &n, 0, &ld, 0, 0, w.main()
                            , details::query(), &that
                            );

          w.prepare_main();
          nt2::qp3(a0,a1,a2,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::qp3_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              ((container_< nt2::tag::table_, double_<A2>, S2 >))
                             (unspecified_<A3>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2, A3& a3) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  wn = a3.main_size();

        a2.resize( nt2::of_size(std::min(n, m), 1) );

        NT2_F77NAME(dgeqp3) (&m, &n, a0.raw(), &ld, a1.raw(), a2.raw(), a3.main()
                            , &wn, &that
                            );
        return that;
     }
  };

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::qp3_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              ((container_< nt2::tag::table_, single_<A2>, S2 >))
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();

        NT2_F77NAME(sgeqp3) (&m, &n, 0, &ld, 0, 0, w.main()
                            , details::query(), &that
                            );

          w.prepare_main();
          nt2::qp3(a0,a1,a2,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::qp3_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              ((container_< nt2::tag::table_, single_<A2>, S2 >))
                             (unspecified_<A3>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2, A3& a3) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  wn = a3.main_size();

        a2.resize( nt2::of_size(std::min(n, m), 1) );

        NT2_F77NAME(sgeqp3) (&m, &n, a0.raw(), &ld, a1.raw(), a2.raw(), a3.main()
                            , &wn, &that
                            );
        return that;
     }
  };

//------------------------------------------Complex----------------------------------------//

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::qp3_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              ((container_< nt2::tag::table_, complex_<double_<A2> >, S2 >))
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();

        NT2_F77NAME(zgeqp3) (&m, &n, 0, &ld, 0, 0, w.main()
                            , details::query(), 0, &that
                            );

          w.prepare_main();
          nt2::qp3(a0,a1,a2,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::qp3_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              ((container_< nt2::tag::table_, complex_<double_<A2> >, S2 >))
                             (unspecified_<A3>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2, A3& a3) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  wn = a3.main_size();

        nt2::container::table<double> rwork(nt2::of_size(2*n,1));
        a2.resize( nt2::of_size(std::min(n, m), 1) );

        NT2_F77NAME(zgeqp3) (&m, &n, a0.raw(), &ld, a1.raw(), a2.raw(), a3.main()
                            , &wn, rwork.raw(), &that
                            );
        return that;
     }
  };

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::qp3_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              ((container_< nt2::tag::table_, complex_<single_<A2> >, S2 >))
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();

        NT2_F77NAME(cgeqp3) (&m, &n, 0, &ld, 0, 0, w.main()
                            , details::query(), 0, &that
                            );

          w.prepare_main();
          nt2::qp3(a0,a1,a2,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::qp3_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              ((container_< nt2::tag::table_, complex_<single_<A2> >, S2 >))
                             (unspecified_<A3>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2, A3& a3) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  wn = a3.main_size();

        nt2::container::table<float> rwork(nt2::of_size(2*n,1));
        a2.resize( nt2::of_size(std::min(n, m), 1) );

        NT2_F77NAME(cgeqp3) (&m, &n, a0.raw(), &ld, a1.raw(), a2.raw(), a3.main()
                            , &wn, rwork.raw(), &that
                            );
        return that;
     }
  };
} }

#endif
