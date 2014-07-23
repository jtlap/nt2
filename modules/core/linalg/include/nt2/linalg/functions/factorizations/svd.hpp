//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_FACTORIZATIONS_SVD_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_FACTORIZATIONS_SVD_HPP_INCLUDED

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/include/functions/resize.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/gesvd.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/linalg/details/utility/lapack_assert.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/sdk/meta/concrete.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/include/functions/abs.hpp>

#include <nt2/core/container/table/table.hpp>

#include <boost/dispatch/meta/ignore_unused.hpp>
#include <nt2/table.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::svd_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> >)
                            )
  {
    typedef  typename nt2::meta::as_real<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return nt2::abs(a0);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::svd_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              (unspecified_<A1>)
                            )
  {
    typedef  typename nt2::meta::as_real<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1&) const
    {
      return nt2::abs(a0);
    }
  };


  //============================================================================
  //SVD
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::svd_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::svd_
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
    typedef typename boost::proto::result_of::child_c<A0&,0>::value_type     child0;
    typedef typename child0::value_type                                      type_t;
    typedef typename meta::as_real<type_t>::type                            rtype_t;
    typedef typename meta::as_integer<rtype_t>::type                        itype_t;
    typedef nt2::memory::container<tag::table_, type_t, nt2::_2D>        o_semantic;
    typedef nt2::memory::container<tag::table_, rtype_t, nt2::_2D>       r_semantic;
    typedef nt2::memory::container<tag::table_, nt2_la_int, nt2::_2D>    i_semantic;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      eval(a0, a1, N0(), N1());
    }

    //==========================================================================
    /// INTERNAL ONLY - S = SVD(A)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<1> const&
              , boost::mpl::long_<1> const&
              ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(o_semantic, a, boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (r_semantic, s, boost::proto::child_c<0>(a1));

      nt2_la_int  m  = nt2::height(a);
      nt2_la_int  n  = nt2::width(a);

      s.resize(nt2::of_size(std::min(m,n),1));

      lapack_assert(nt2::gesvd( boost::proto::value(a)
                              , boost::proto::value(s)
                              , boost::proto::value(a) //unused
                              , boost::proto::value(a) //unused
                              , 'N', 'N'));
      boost::proto::child_c<0>(a1) = s;
    }

    //==========================================================================
    /// INTERNAL ONLY - [U,S,V] = SVD(X)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<1> const&
              , boost::mpl::long_<3> const&
              ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(o_semantic, a, boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (o_semantic, u, boost::proto::child_c<0>(a1));
      nt2_la_int  m  = nt2::height(a);
      nt2_la_int  n  = nt2::width(a);

      u.resize(nt2::of_size(m,m));
      nt2::container::table<type_t> vt(of_size(n, n));
      nt2::container::table<rtype_t>  s(of_size(min(n, m), 1));

      lapack_assert(nt2::gesvd( boost::proto::value(a)
                              , boost::proto::value(s)
                              , boost::proto::value(u)
                              , boost::proto::value(vt)
                              , 'A', 'A'));
      NT2_DISPLAY(s);
      boost::proto::child_c<0>(a1) = u;
      boost::proto::child_c<2>(a1) = nt2::trans(vt);
      boost::proto::child_c<1>(a1) = nt2::expand(nt2::from_diag(s),height(a0),width(a0));
    }

    //==========================================================================
    /// INTERNAL ONLY - [U,S,V] = SVD(X,0/econ_/lapack_)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const&
              , boost::mpl::long_<3> const&
              ) const
    {
      eval2_3(a0,a1,
              boost::proto::value(boost::proto::child_c<1>(a0)));
    }


    //==========================================================================
    // bunch of evali_j
    //==========================================================================
    /// INTERNAL ONLY - [U,S,V] = SVD(X,0)
    BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
              , int const&
              ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(o_semantic, a, boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (o_semantic, u, boost::proto::child_c<0>(a1));

      nt2_la_int  m  = nt2::height(a);
      nt2_la_int  n  = nt2::width(a);
      nt2_la_int  d  = std::min(n, m);
      nt2::container::table<type_t> vt(of_size(n, n));
      nt2::container::table<rtype_t>  s(of_size(d, 1));
      char jobu = (m>n) ? 'S' :'A';
      u.resize(nt2::of_size(m,d));

      lapack_assert(nt2::gesvd( boost::proto::value(work)
                              , boost::proto::value(s)
                              , boost::proto::value(u)
                              , boost::proto::value(vt)
                              , jobu, 'A'));

      boost::proto::child_c<2>(a1) = nt2::trans(vt);
      boost::proto::child_c<1>(a1) = nt2::from_diag(s);
      boost::proto::child_c<0>(a1) = u;
    }


    /// INTERNAL ONLY - [U,S,V] = SVD(X,econ_)
    BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
                 , const nt2::policy<ext::econ_>&
                 ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(o_semantic, a, boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (o_semantic, u, boost::proto::child_c<0>(a1));

      nt2_la_int  m  = nt2::height(a);
      nt2_la_int  n  = nt2::width(a);

      nt2::container::table<rtype_t>  s(of_size(std::min(m,n), 1));
      nt2::container::table<type_t> vt;

      char jobu = 'A';
      char jobvt= 'A';
      if(m>=n)
      {
        jobu = 'S';
        u.resize(nt2::of_size(m,n));
        vt.resize(nt2::of_size(n,n));
      }
      else if (m<n)
      {
        jobvt = 'S';
        u.resize(nt2::of_size(m,m));
        vt.resize(nt2::of_size(m,n));
      }

      lapack_assert(nt2::gesvd( boost::proto::value(a)
                              , boost::proto::value(s)
                              , boost::proto::value(u)
                              , boost::proto::value(vt)
                              , jobu, jobvt ));

      boost::proto::child_c<1>(a1) = nt2::from_diag(s);
      boost::proto::child_c<2>(a1) = nt2::trans(vt);
      boost::proto::child_c<0>(a1) = u;

    }

    /// INTERNAL ONLY - [U,S,VT] = SVD(X,lapack_)
    BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
                 , const nt2::policy<ext::lapack_>&
                 ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(o_semantic, a, boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (o_semantic, u, boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_OUT  (o_semantic, vt, boost::proto::child_c<2>(a1));
      NT2_AS_TERMINAL_OUT  (r_semantic, s, boost::proto::child_c<1>(a1));

      nt2_la_int  m  = nt2::height(a);
      nt2_la_int  n  = nt2::width(a);

      u.resize(nt2::of_size(m,m));
      vt.resize(of_size(n, n));
      s.resize(of_size(min(n, m), 1));

      lapack_assert(nt2::gesvd( boost::proto::value(a)
                              , boost::proto::value(s)
                              , boost::proto::value(u)
                              , boost::proto::value(vt)
                              , 'A', 'A'));

      boost::proto::child_c<1>(a1) = s;
      boost::proto::child_c<2>(a1) = vt;
      boost::proto::child_c<0>(a1) = u;

    }

  };
} }

#endif


