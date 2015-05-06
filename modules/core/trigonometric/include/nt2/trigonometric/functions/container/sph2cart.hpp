//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_CONTAINER_SPH2CART_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_CONTAINER_SPH2CART_HPP_INCLUDED
#include <nt2/trigonometric/functions/sph2cart.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/core/container/dsl.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>
#include <boost/fusion/tuple.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( sph2cart_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)(A5)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              ((ast_<A2, nt2::container::domain>))
                              (unspecified_<A3>)
                              (unspecified_<A4>)
                              (unspecified_<A5>)
                            )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1
                                            , A2 const& a2
                                            ,A3 & r0, A4& r1, A5& r2) const
    {
      nt2::tie(r0,r1,r2) = nt2::sph2cart(a0, a1, a2);
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( sph2cart_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              ((ast_<A2, nt2::container::domain>))
                              (unspecified_<A3>)
                              (unspecified_<A4>)
                            )
  {
    typedef typename boost::dispatch::meta::terminal_of<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1
                                            , A2 const& a2
                                            ,A3 & r1, A4& r2) const
    {
      result_type r0;
      nt2::tie(r0,r1,r2) = nt2::sph2cart(a0, a1, a2);
      return r0;
    }
  };

    BOOST_DISPATCH_IMPLEMENT  ( sph2cart_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              ((ast_<A2, nt2::container::domain>))
                              (unspecified_<A3>)
                            )
  {
    typedef typename boost::dispatch::meta::terminal_of<A0>::type type1;
    typedef boost::fusion::tuple<type1, type1>              result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1
                                            , A2 const& a2
                                            ,A3& r2) const
    {
      type1 r0, r1;
      nt2::tie(r0, r1, r2) = nt2::sph2cart(a0, a1, a2);
      return result_type(r0, r1);
    }
  };
} }

#endif
