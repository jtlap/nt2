//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_HSTRF_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_HSTRF_HPP_INCLUDED

#include <nt2/linalg/functions/hstrf.hpp>
#include <nt2/linalg/details/lapack/declare/hstrf.hpp>

#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/options.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hstrf_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(C0)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))   //a
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))  //ipiv
                              (scalar_<ints8_<C0> >)                                //uplo
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a, A1& ipiv, C0 uplo) const
     {
       result_type info;
       details::workspace<typename A0::value_type> w;
       nt2_la_int  n  = nt2::width(a);
       nt2_la_int  lda = a.leading_size();

       NT2_F77NAME(dsytrf)(&uplo,&n,0,&lda,0,w.main(),details::query(),&info);

       w.prepare_main();
       return nt2::hstrf(a,ipiv,uplo,w);
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hstrf_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(C0)(WK)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))   //a
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))  //ipiv
                              (scalar_<ints8_<C0> >)                                //uplo
                              (unspecified_<WK>)                                    //workspace
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a, A1& ipiv, C0 uplo, WK& wk) const
    {
      result_type info;
      nt2_la_int  n  = nt2::width(a);
      nt2_la_int  lda = a.leading_size();
      nt2_la_int  wn = wk.main_size();

      ipiv.resize( nt2::of_size(n, 1) );

      NT2_F77NAME(dsytrf)(&uplo,&n,a.raw(),&lda,ipiv.raw(),wk.main(),&wn,&info);
      return info;
    }
  };

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hstrf_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(C0)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))     //a
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))    //ipiv
                              (scalar_<ints8_<C0> >)                                  //uplo

                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a, A1& ipiv, C0 uplo) const
    {
      result_type info;
      nt2_la_int  n  = nt2::width(a);
      nt2_la_int  lda = a.leading_size();

      details::workspace<typename A0::value_type> w;
      ipiv.resize( nt2::of_size(n, 1) );

      NT2_F77NAME(ssytrf)(&uplo,&n,0,&lda,0,w.main(),details::query(),&info);

      w.prepare_main();
      return nt2::hstrf(a,ipiv,uplo,w);
    }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hstrf_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(C0)(WK)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))    //a
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))  //ipiv
                              (scalar_<ints8_<C0> >)                                //uplo
                              (unspecified_<WK>)                                    //workspace
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a, A1& ipiv,C0 uplo,WK& wk) const
    {
      result_type info;
      nt2_la_int  n  = nt2::width(a);
      nt2_la_int  lda = a.leading_size();
      nt2_la_int  wn = wk.main_size();

      ipiv.resize( nt2::of_size(n, 1) );

      NT2_F77NAME(ssytrf)(&uplo,&n, a.raw(),&lda,ipiv.raw(),wk.main(),&wn,&info );
      return info;
    }
  };

//---------------------------------------Complex-----------------------------------------//

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hstrf_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(C0)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))   //a
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))             //ipiv
                              (scalar_<ints8_<C0> >)                                           //uplo
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a, A1& ipiv, C0 uplo) const
    {
      result_type info;
      nt2_la_int  n  = nt2::width(a);
      nt2_la_int  lda = a.leading_size();

      details::workspace<typename A0::value_type> w;
      ipiv.resize( nt2::of_size(n, 1) );

      NT2_F77NAME(chetrf)(&uplo,&n,0,&lda,0,w.main(),details::query(),&info);

      w.prepare_main();
      return nt2::hstrf(a,ipiv,uplo, w);
    }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hstrf_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(C0)(WK)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))   //a
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))             //ipiv
                              (scalar_<ints8_<C0> >)                                           //uplo
                              (unspecified_<WK>)                                               //workspace
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a, A1& ipiv,C0 uplo,WK& wk) const
    {
      result_type info;
      nt2_la_int  n  = nt2::width(a);
      nt2_la_int  lda = a.leading_size();
      nt2_la_int  wn = wk.main_size();

      ipiv.resize( nt2::of_size(n, 1) );

      NT2_F77NAME(chetrf)(&uplo,&n,a.raw(),&lda,ipiv.raw(),wk.main(),&wn,&info);
      return info;
    }
  };

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hstrf_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(C0)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))   //a
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))           //ipiv
                              (scalar_<ints8_<C0> >)                                           //uplo
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a, A1& ipiv,C0 uplo) const
    {
      result_type info;
      nt2_la_int  m  = nt2::height(a);
      nt2_la_int  n  = nt2::width(a);
      nt2_la_int  lda = a.leading_size();

      details::workspace<typename A0::value_type> w;
      ipiv.resize( nt2::of_size(n, 1) );

      NT2_F77NAME(zhetrf)(&uplo,&n,0,&lda,0,w.main(),details::query(),&info);

      w.prepare_main();
      return nt2::hstrf(a,ipiv,uplo,w);
    }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hstrf_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(C0)(WK)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))   //a
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))             //ipiv
                              (scalar_<ints8_<C0> >)                                           //uplo
                              (unspecified_<WK>)                                               //workspace
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a, A1& ipiv,C0 uplo,WK& wk) const
    {
      result_type info;
      nt2_la_int  m  = nt2::height(a);
      nt2_la_int  n  = nt2::width(a);
      nt2_la_int  lda = a.leading_size();
      nt2_la_int  wn = wk.main_size();

      ipiv.resize( nt2::of_size(n, 1) );

      NT2_F77NAME(zhetrf)(&uplo,&n,a.raw(),&lda,ipiv.raw(),wk.main(),&wn,&info);
      return info;
    }
  };
} }

#endif
