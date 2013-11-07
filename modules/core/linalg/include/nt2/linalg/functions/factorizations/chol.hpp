//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_FACTORIZATIONS_CHOL_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_FACTORIZATIONS_CHOL_HPP_INCLUDED

#include <nt2/include/functions/potrf.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/tril.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/sdk/meta/concrete.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

#include <nt2/table.hpp>

#include <iostream>

namespace nt2 { namespace ext
{
  //============================================================================
  //Cholesky factorization
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chol_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::chol_
                                    , N0, nt2::container::domain
                                      >
                              ))
                              ((node_<A1, nt2::tag::tie_
                                    , N1, nt2::container::domain
                                     >
                              ))
                            )
  {
    typedef void  result_type;
    typedef typename boost::proto::result_of::child_c<A0&,0>::value_type child0;
    typedef typename child0::value_type type_t;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      eval(a0, a1, N0(), N1());
    }

    //==========================================================================
    /// INTERNAL ONLY - R = chol(A)
    BOOST_FORCEINLINE
    void eval ( A0& a0 ,  A1& a1
              , boost::mpl::long_<1> const& , boost::mpl::long_<1> const&
              ) const
    {
      nt2::table<type_t> work = boost::proto::child_c<0>(a0);


      nt2_la_int info = nt2::potrf( work,'U');

      boost::proto::child_c<0>(a1) = nt2::triu(work);
    }

    //==========================================================================
    /// INTERNAL ONLY - L = chol(A,Lower/Upper)
    BOOST_FORCEINLINE
    void eval ( A0& a0 , A1& a1
              , boost::mpl::long_<2> const& , boost::mpl::long_<1> const&
              ) const
    {
      eval( a0, a1, N0(), N1()
                , boost::proto::value(boost::proto::child_c<1>(a0))
                );
    }

    //==========================================================================
    /// INTERNAL ONLY - L = chol(A,Lower)
    BOOST_FORCEINLINE
    void eval( A0& a0 , A1& a1
              , boost::mpl::long_<2> const& , boost::mpl::long_<1> const&
              , nt2::policy<ext::lower_> const&
              ) const
    {
      nt2::table<type_t> work = boost::proto::child_c<0>(a0);

      nt2_la_int info = nt2::potrf( work,'L');

      boost::proto::child_c<0>(a1) = nt2::tril(work);
    }


    //==========================================================================
    /// INTERNAL ONLY - R = chol(A,Upper)
    BOOST_FORCEINLINE
    void eval ( A0& a0 , A1& a1
              , boost::mpl::long_<2> const& , boost::mpl::long_<1> const&
              , nt2::policy<ext::upper_> const&
              ) const
    {
      eval(a0,a1,N1(),N1());
    }


    //==========================================================================
    /// INTERNAL ONLY - R,P = chol(A)
    BOOST_FORCEINLINE
    void eval ( A0& a0 , A1& a1
              , boost::mpl::long_<1> const& , boost::mpl::long_<2> const&
              ) const
    {
      nt2::table<type_t> work = boost::proto::child_c<0>(a0);

      nt2_la_int info = nt2::potrf( work,'U');

      boost::proto::child_c<0>(a1) = nt2::triu(work);
      boost::proto::child_c<1>(a1) = info;
    }

    //==========================================================================
    /// INTERNAL ONLY - R,P = chol(A,Lower/Upper)
    BOOST_FORCEINLINE
    void eval ( A0& a0 , A1& a1
              , boost::mpl::long_<2> const& , boost::mpl::long_<2> const&
              ) const
    {
      eval( a0, a1, N0(), N1()
                , boost::proto::value(boost::proto::child_c<1>(a0))
                );
    }

    //==========================================================================
    /// INTERNAL ONLY - L,P = chol(A,Lower)
    BOOST_FORCEINLINE
    void eval ( A0& a0 , A1& a1
              , boost::mpl::long_<2> const& , boost::mpl::long_<2> const&
              , nt2::policy<ext::lower_> const&
              ) const
    {
      nt2::table<type_t> work = boost::proto::child_c<0>(a0);

      nt2_la_int info = nt2::potrf( work,'L');

      boost::proto::child_c<0>(a1) = nt2::tril(work);
      boost::proto::child_c<1>(a1) = info;
    }

    //==========================================================================
    /// INTERNAL ONLY - R,P = chol(A,Upper)
    BOOST_FORCEINLINE
    void eval ( A0& a0 , A1& a1
              , boost::mpl::long_<2> const& , boost::mpl::long_<2> const&
              , nt2::policy<ext::upper_> const&
              ) const
    {
      eval(a0,a1,boost::mpl::long_<1>(),N0());
    }
  };
} }

#endif


