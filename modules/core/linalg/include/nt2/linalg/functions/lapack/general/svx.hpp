//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_SVX_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_LAPACK_SVX_HPP_INCLUDED

#include <nt2/linalg/functions/svx.hpp>
#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/core/container/table/category.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>

#include <nt2/table.hpp>

extern "C"
{
  void NT2_F77NAME(dgesvx)( const char* fact    , const char* trans
                          , const nt2_la_int* n , const nt2_la_int* nrhs
                          , const double* a     , const nt2_la_int* lda
                          , double* af          , const nt2_la_int* ldaf
                          , nt2_la_int* ipiv    , const char* equed
                          , double* r           , double* c
                          , const double* b     , const nt2_la_int* ldb
                          , double* x           , const nt2_la_int* ldx
                          , double* rcond       , double* ferr
                          , double* berr        , double* work
                          , nt2_la_int* iwork   , nt2_la_int* info
                          );

  void NT2_F77NAME(sgesvx)( const char* fact    , const char* trans
                          , const nt2_la_int* n , const nt2_la_int* nrhs
                          , const float* a      , const nt2_la_int* lda
                          , float* af           , const nt2_la_int* ldaf
                          , nt2_la_int* ipiv    , const char* equed
                          , float* r            , float* c
                          , const float* b      , const nt2_la_int* ldb
                          , float* x            , const nt2_la_int* ldx
                          , float* rcond        , float* ferr
                          , float* berr         , float* work
                          , nt2_la_int* iwork   , nt2_la_int* info
                          );
}

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::svx_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((expr_ < table_< double_<A0>, S0 >  // A
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< double_<A1>, S1 >  // B
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< double_<A2>, S2 >  // X
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              (scalar_< floating_<A3> >)          //rcond
                            )
  {
     typedef nt2_la_int result_type;
     typedef double T;

     BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2& a2, A3& a3) const
     {
        result_type that;
        nt2_la_int  n  = nt2::height(a0);
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = n;
        char fact  = 'N';
        char trans = 'N';
        char equed = 'N';

        nt2::table<T> af(nt2::of_size(n,n));

        nt2::table<T> r(nt2::of_size(n,1));
        nt2::table<T> c(nt2::of_size(n,1));
        nt2::table<T> ferr(nt2::of_size(nhrs,1));
        nt2::table<T> berr(nt2::of_size(nhrs,1));
        details::workspace<typename A2::value_type> work;
        work.resize_main(4*n);

        nt2::table<nt2_la_int> ipiv(nt2::of_size(n,1));
        nt2::table<nt2_la_int> iwork(nt2::of_size(n,1));

        NT2_F77NAME(dgesvx)( &fact       , &trans
                           , &n          , &nhrs
                           , a0.raw()    , &n
                           , af.raw()    , &n
                           , ipiv.raw()  , &equed
                           , r.raw()     , c.raw()
                           , a1.raw()    , &ldb
                           , a2.raw()    , &ldb
                           , &a3         , ferr.raw()
                           , berr.raw()  , work.main()
                           , iwork.raw() , &that
                           );

        return that;
     }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::svx_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((expr_ < table_< single_<A0>, S0 >  // A
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< single_<A1>, S1 >  // B
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < table_< single_<A2>, S2 >  // X
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              (scalar_< floating_<A3> >)           //rcond
                            )
  {
     typedef nt2_la_int result_type;
     typedef float T;

     BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2& a2, A3& a3) const
     {
        result_type that;
        nt2_la_int  n  = nt2::height(a0);
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = n;
        char fact  = 'N';
        char trans = 'N';
        char equed = 'N';

        nt2::table<T> af(nt2::of_size(n,n));

        nt2::table<T> r(nt2::of_size(n,1));
        nt2::table<T> c(nt2::of_size(n,1));
        nt2::table<T> ferr(nt2::of_size(nhrs,1));
        nt2::table<T> berr(nt2::of_size(nhrs,1));
        details::workspace<typename A2::value_type> work;
        work.resize_main(4*n);

        nt2::table<nt2_la_int> ipiv(nt2::of_size(n,1));
        nt2::table<nt2_la_int> iwork(nt2::of_size(n,1));

        NT2_F77NAME(sgesvx)( &fact       , &trans
                           , &n          , &nhrs
                           , a0.raw()    , &n
                           , af.raw()    , &n
                           , ipiv.raw()  , &equed
                           , r.raw()     , c.raw()
                           , a1.raw()    , &ldb
                           , a2.raw()    , &ldb
                           , &a3         , ferr.raw()
                           , berr.raw()  , work.main()
                           , iwork.raw() , &that
                           );

        return that;
     }
  };

} }

#endif
