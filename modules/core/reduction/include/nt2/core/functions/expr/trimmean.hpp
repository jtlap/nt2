//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_TRIMMEAN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_TRIMMEAN_HPP_INCLUDED

#include <nt2/core/functions/trimmean.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/along.hpp>
#include <nt2/include/functions/ifloor.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/mean.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/sort.hpp>
#include <nt2/include/functions/swap.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/core/container/colon/colon.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( trimmean_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>)) )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 a0)
                          , nt2::trimmean(a0,0.50,nt2::policy<ext::both_>(), firstnonsingleton(a0))
                          );
  };

  BOOST_DISPATCH_IMPLEMENT  ( trimmean_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> > )
                              )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 a0, A1 a1)
                          , nt2::trimmean(a0,0.50,nt2::policy<ext::both_>(), a1)
                          );
  };

  BOOST_DISPATCH_IMPLEMENT  ( trimmean_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<floating_<A1> > )
                              )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 a0, A1 a1)
                          , nt2::trimmean(a0,a1,nt2::policy<ext::both_>(), firstnonsingleton(a0) )
                          );
  };

  BOOST_DISPATCH_IMPLEMENT  ( trimmean_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (unspecified_<A1>)
                              )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 a0, A1 a1)
                          , nt2::trimmean(a0,0.5, a1, firstnonsingleton(a0) )
                          );
  };
  BOOST_DISPATCH_IMPLEMENT  ( trimmean_, tag::cpu_,
                               (A0)(A1)(A2),
                              ((ast_<A0, nt2::container::domain>))
                               (scalar_<floating_<A1> >)
                               (unspecified_<A2>)
                              )
  {
    BOOST_DISPATCH_RETURNS(3, (A0 a0, A1 a1, A2 a2)
                          , nt2::trimmean(a0,a1,a2, firstnonsingleton(a0))
                          )
  };

  BOOST_DISPATCH_IMPLEMENT  ( trimmean_, tag::cpu_,
                               (A0)(A1)(A2),
                              ((ast_<A0, nt2::container::domain>))
                               (scalar_<floating_<A1>>)
                               (scalar_<integer_<A2>>)
                              )
  {
    BOOST_DISPATCH_RETURNS(3, (A0 a0, A1 a1, A2 a2)
                          , nt2::trimmean(a0,a1,nt2::policy<ext::both_>(),a2)
                          )
  };

  BOOST_DISPATCH_IMPLEMENT  ( trimmean_, tag::cpu_,
                               (A0)(A1)(A2),
                              ((ast_<A0, nt2::container::domain>))
                               (unspecified_<A1>)
                               (scalar_<integer_<A2>>)
                              )
  {
    BOOST_DISPATCH_RETURNS(3, (A0 a0, A1 a1, A2 a2)
                          , nt2::trimmean(a0,0.5,a1,a2)
                          )
  };

  BOOST_DISPATCH_IMPLEMENT  ( trimmean_, tag::cpu_,
                               (A0)(A1)(A2)(A3),
                               ((ast_<A0, nt2::container::domain>))
                               (scalar_<floating_<A1> >)
                               (unspecified_<A2>)
                               (scalar_<integer_<A3> >)
                              )
  {
    typedef typename A0::value_type type_t;
    typedef container::table<type_t> result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& percent
                                            , const A2&, const A3& n) const
    {
      BOOST_ASSERT_MSG(percent >= Zero<A1>() && percent <=  One<A1>()
                      , "percent must be between 0 and 1");
      std::size_t d, f;
      bounds(size(a0, n), d, f, percent, A2());
      container::table<type_t> sa =  sort(a0, n);
      return mean(along(sa, _(d, f), n), n);
    }
  private :
    BOOST_FORCEINLINE static void bounds(const std::size_t & l
                                        , std::size_t &d, std::size_t & f
                                        , A1 percent
                                        , nt2::policy<ext::both_> const & )
    {
      percent *= Half<A1>();
      std::size_t w = ifloor(l*percent);
      d = oneplus(w);
      f = l - w;
      if (f < d) nt2::swap(d, f);
    }
    BOOST_FORCEINLINE static void bounds(const std::size_t & l
                                        , std::size_t &d, std::size_t & f
                                        , A1 percent
                                        , nt2::policy<ext::lower_> const & )
    {
      std::size_t w = ifloor(l*percent);
      d = 1;
      f = l-w;
    }
    BOOST_FORCEINLINE static void bounds(const std::size_t & l
                                        , std::size_t &d, std::size_t & f
                                        , A1 percent
                                        , nt2::policy<ext::upper_> const & )
    {
      std::size_t w = ifloor(l*percent);
      d =  oneplus(w);
      f = l;
    }

  };

} }

#endif
