//==============================================================================
//          Copyright 2015 - Jean-Thierry Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_FACTORIZATIONS_HESS_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_FACTORIZATIONS_HESS_HPP_INCLUDED

#include <nt2/linalg/functions/hess.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/gghrd.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/istriu.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/include/functions/qr.hpp>
#include <nt2/include/functions/resize.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/core/utility/assign_swap.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  //hess Scalar
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( hess_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return a0;
    }
  };

  //============================================================================
  //hess Scalar
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( hess_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              (scalar_<unspecified_<A1> >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1&) const
    {
      return a0;
    }
  };

  //============================================================================
  //hess
  //============================================================================
  /// INTERNAL ONLY
  BOOST_DISPATCH_IMPLEMENT  ( hess_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_ < A0, nt2::tag::hess_
                                      , N0, nt2::container::domain
                                      >
                              ))
                              ((node_ < A1, nt2::tag::tie_
                                      , N1, nt2::container::domain
                                      >
                              ))
                            )
  {
    typedef void                                                        result_type;
    typedef typename boost::proto::result_of::child_c<A0&,0>::value_type     child0;
    typedef typename child0::value_type                                      type_t;
    typedef nt2::memory::container<tag::table_, type_t, nt2::_2D>        o_semantic;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      BOOST_ASSERT_MSG(issquare(boost::proto::child_c<0>(a0))
                      , "input matrices must be square");
      eval(a0, a1, N0(), N1());
    }
  private:
    /// INTERNAL ONLY - h =  hess(a)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<1> const& // # inputs
              , boost::mpl::long_<1> const& // # outputs
              ) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic
                           , hess, boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<0>(a1));
      nt2_la_int n = height(hess);
      nt2::container::table<type_t> b = eye(n, meta::as_<type_t>());
      nt2::gghrd( 'N', 'N', 1, n
                , boost::proto::value(hess), boost::proto::value(b)
                , boost::proto::value(b),    boost::proto::value(b));
      assign_swap(boost::proto::child_c<0>(a1), hess);
    }

    /// INTERNAL ONLY - tie(h, p) =  hess(a)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<1> const& // # inputs
              , boost::mpl::long_<2> const& // # outputs
              ) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic
                           , hess, boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_OUT(o_semantic
                           , p
                           , boost::proto::child_c<1>(a1));
      nt2_la_int n = height(hess);
      nt2::container::table<type_t> b = eye(n, meta::as_<type_t>());
      p.resize(hess.extent());
      nt2::gghrd( 'I', 'N', 1, n
                , boost::proto::value(hess), boost::proto::value(b)
                , boost::proto::value(p),    boost::proto::value(b));
      assign_swap(boost::proto::child_c<0>(a1), hess);
      assign_swap(boost::proto::child_c<1>(a1), p);
    }

    /// INTERNAL ONLY - tie(aa, bb, q, z) =  hess(a)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const& // # inputs
              , boost::mpl::long_<4> const& // # outputs
              ) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic
                           , aa, boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_INOUT(o_semantic
                           , bb, boost::proto::child_c<1>(a0)
                           , boost::proto::child_c<1>(a1));
      BOOST_ASSERT_MSG(issquare(bb), "input matrices must be square");
      nt2_la_int n = height(aa);
      nt2::container::table<type_t> q;
      nt2::container::table<type_t> z;
      if(!istriu(bb))
      {
        tie(q, bb) = qr(bb);
        aa = mtimes(ctrans(q), aa);
      }
      nt2::gghrd( 'V', 'I', 1, n
                , boost::proto::value(aa), boost::proto::value(bb)
                , boost::proto::value(q) , boost::proto::value(z));
      assign_swap(boost::proto::child_c<0>(a1), aa);
      assign_swap(boost::proto::child_c<1>(a1), bb);
      assign_swap(boost::proto::child_c<2>(a1), q);
      assign_swap(boost::proto::child_c<3>(a1), z);
    }

    /// INTERNAL ONLY - tie(aa, bb, q, z) =  hess(a)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const& // # inputs
              , boost::mpl::long_<3> const& // # outputs
              ) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic
                           , aa, boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_INOUT(o_semantic
                           , bb, boost::proto::child_c<1>(a0)
                           , boost::proto::child_c<1>(a1));
      BOOST_ASSERT_MSG(issquare(bb), "input matrices must be square");
      nt2_la_int n = height(aa);
      nt2::container::table<type_t> q;
      if(!istriu(bb))
      {
        tie(q, bb) = qr(bb);
        aa = mtimes(trans(q), aa);
      }
      nt2::gghrd( 'V', 'N', 1, n
                , boost::proto::value(aa), boost::proto::value(bb)
                , boost::proto::value(q) , boost::proto::value(q));
      assign_swap(boost::proto::child_c<0>(a1), aa);
      assign_swap(boost::proto::child_c<1>(a1), bb);
      assign_swap(boost::proto::child_c<2>(a1), q);
    }

    /// INTERNAL ONLY - tie(aa, bb, q, z) =  hess(a)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const& // # inputs
              , boost::mpl::long_<2> const& // # outputs
              ) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic
                           , aa, boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_INOUT(o_semantic
                           , bb, boost::proto::child_c<1>(a0)
                           , boost::proto::child_c<1>(a1));
      BOOST_ASSERT_MSG(issquare(bb), "input matrices must be square");
      nt2_la_int n = height(aa);
      if(!istriu(bb))
      {
        nt2::container::table<type_t> q;
        tie(q, bb) = qr(bb);
        aa = mtimes(trans(q), aa);
      }
      nt2::gghrd( 'N', 'N', 1, n
                , boost::proto::value(aa), boost::proto::value(bb)
                , boost::proto::value(bb), boost::proto::value(bb));
      assign_swap(boost::proto::child_c<0>(a1), aa);
      assign_swap(boost::proto::child_c<1>(a1), bb);
    }
  };
} }

#endif
