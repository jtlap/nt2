//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_YSVX_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_YSVX_HPP_INCLUDED

#include <nt2/linalg/functions/ysvx.hpp>
#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/core/container/table/category.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>

#include <nt2/table.hpp>

extern "C"
{
  void NT2_F77NAME(dsysvx)( const char* fact       , const char* uplo
                          , const nt2_la_int* n    , const nt2_la_int* nrhs
                          , const double* a        , const nt2_la_int* lda
                          , double* af             , const nt2_la_int* ldaf
                          , nt2_la_int* ipiv       , const double* b
                          , const nt2_la_int* ldb  , double* x
                          , const nt2_la_int* ldx  , double* rcond
                          , double* ferr           , double* berr
                          , double* work           , const nt2_la_int* lwork
                          , nt2_la_int* iwork      , nt2_la_int* info
                          );

  void NT2_F77NAME(ssysvx)( const char* fact       , const char* uplo
                          , const nt2_la_int* n    , const nt2_la_int* nrhs
                          , const float* a         , const nt2_la_int* lda
                          , float* af              , const nt2_la_int* ldaf
                          , nt2_la_int* ipiv       , const float* b
                          , const nt2_la_int* ldb  , float* x
                          , const nt2_la_int* ldx  , float* rcond
                          , float* ferr            , float* berr
                          , float* work            , const nt2_la_int* lwork
                          , nt2_la_int* iwork      , nt2_la_int* info
                          );
}

namespace nt2 { namespace ext
{
  /// Computes the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ysvx_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)
                            , ((expr_ < table_< double_<A0>, S0 >   // A
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< integer_<A1>, S1 > // piv
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< double_<A2>, S2 >  // B
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< double_<A3>, S3 >  // X
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              (scalar_< floating_<A4> >)           //rcond
                            )
  {
     typedef nt2_la_int result_type;
     typedef double T;

     BOOST_FORCEINLINE result_type operator()( A0 const& a0, A1& a1, A2& a2
                                             , A3& a3, A4& a4) const
     {
        result_type that;
        nt2_la_int  n  = nt2::height(a0);
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = n;
        char fact = 'N';
        char uplo = 'L';

        details::workspace<typename A2::value_type> work;

        NT2_F77NAME(dsysvx)( &fact       , &uplo
                           , &n          , &nhrs
                           , 0           , &n
                           , 0           , &n
                           , 0           ,0
                           , &ldb        , 0
                           , &ldb        , &a4
                           , 0           , 0
                           , work.main() , details::query()
                           , 0           , &that
                           );

        work.prepare_main();
        nt2::ysvx(a0,a1,a2,a3,a4,work);

        return that;
     }
  };
  /// Workspace is ready -
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ysvx_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)(A5)
                            , ((expr_ < table_< double_<A0>, S0 >   // A
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< integer_<A1>, S1 > // piv
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< double_<A2>, S2 >  // B
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< double_<A3>, S3 >  // X
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              (scalar_< floating_<A4> >)   // rcond
                              (unspecified_<A5>)           // Workspace
                            )
  {
     typedef nt2_la_int result_type;
     typedef double T;

     BOOST_FORCEINLINE result_type operator() (A0 const& a0, A1& a1, A2& a2
                                            , A3& a3, A4& a4, A5& a5) const
     {
        result_type that;
        nt2_la_int  n  = nt2::height(a0);
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = n;
        nt2_la_int  wn  = a5.main_size();
        char fact = 'N';
        char uplo = 'L';

        nt2::table<T> af(nt2::of_size(n,n));
        nt2::table<T> ferr(nt2::of_size(nhrs,1));
        nt2::table<T> berr(nt2::of_size(nhrs,1));


        nt2::table<nt2_la_int> iwork(nt2::of_size(n,1));

        NT2_F77NAME(dsysvx)( &fact       , &uplo
                           , &n          , &nhrs
                           , a0.raw()    , &n
                           , af.raw()    , &n
                           , a1.raw()    , a2.raw()
                           , &ldb        , a3.raw()
                           , &ldb        , &a4
                           , ferr.raw()  , berr.raw()
                           , a5.main()   , &wn
                           , iwork.raw() , &that
                           );

        return that;
     }
  };
  /// Computes the workspace -
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ysvx_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)
                            , ((expr_ < table_< single_<A0>, S0 >   // A
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< integer_<A1>, S1 > // piv
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< single_<A2>, S2 >  // B
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< single_<A3>, S3 >  // X
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              (scalar_< floating_<A4> >)           //rcond
                            )
  {
     typedef nt2_la_int result_type;
     typedef float T;

     BOOST_FORCEINLINE result_type operator()( A0 const& a0, A1& a1, A2& a2
                                             , A3& a3, A4& a4) const
     {
        result_type that;
        nt2_la_int  n  = nt2::height(a0);
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = n;
        char fact = 'N';
        char uplo = 'L';

        details::workspace<typename A2::value_type> work;

        NT2_F77NAME(ssysvx)( &fact       , &uplo
                           , &n          , &nhrs
                           , 0           , &n
                           , 0           , &n
                           , 0           , 0
                           , &ldb        , 0
                           , &ldb        , &a4
                           , 0           , 0
                           , work.main() , details::query()
                           , 0           , &that
                           );

        work.prepare_main();
        nt2::ysvx(a0,a1,a2,a3,a4,work);

        return that;
     }
  };

  /// Workspace is ready -
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ysvx_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)(A5)
                            , ((expr_ < table_< single_<A0>, S0 >   // A
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< integer_<A1>, S1 > // piv
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< single_<A2>, S2 >  // B
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< single_<A3>, S3 >  // X
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              (scalar_< floating_<A4> >)   // rcond
                              (unspecified_<A5>)           // Workspace
                            )
  {
     typedef nt2_la_int result_type;
     typedef float T;

     BOOST_FORCEINLINE result_type operator() (A0 const& a0, A1& a1, A2& a2
                                            , A3& a3, A4& a4, A5& a5) const
     {
        result_type that;
        nt2_la_int  n  = nt2::height(a0);
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = n;
        nt2_la_int  wn  = a5.main_size();
        char fact = 'N';
        char uplo = 'L';

        nt2::table<T> af(nt2::of_size(n,n));
        nt2::table<T> ferr(nt2::of_size(nhrs,1));
        nt2::table<T> berr(nt2::of_size(nhrs,1));


        nt2::table<nt2_la_int> iwork(nt2::of_size(n,1));

        NT2_F77NAME(ssysvx)( &fact       , &uplo
                           , &n          , &nhrs
                           , a0.raw()    , &n
                           , af.raw()    , &n
                           , a1.raw()    , a2.raw()
                           , &ldb        , a3.raw()
                           , &ldb        , &a4
                           , ferr.raw()  , berr.raw()
                           , a5.main()   , &wn
                           , iwork.raw() , &that
                           );

        return that;
     }
  };

} }

#endif
