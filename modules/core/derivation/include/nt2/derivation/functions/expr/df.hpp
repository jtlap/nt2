//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DERIVATION_FUNCTIONS_EXPR_DF_HPP_INCLUDED
#define NT2_DERIVATION_FUNCTIONS_EXPR_DF_HPP_INCLUDED

#include <nt2/derivation/functions/df.hpp>
#include <nt2/include/functions/backward.hpp>
#include <nt2/include/functions/centered.hpp>
#include <nt2/include/functions/forward.hpp>
#include <nt2/include/functions/vand.hpp>
#include <nt2/derivation/options.hpp>
#include <nt2/table.hpp>

namespace nt2 { namespace ext
{
 BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_ < A1, nt2::tag::df_, N
                                      , nt2::container::domain
                                      >
                              ))
                            )
  {
    typedef A0&                                   result_type;
    typedef typename A0::value_type                    type_t;
    typedef typename meta::as_real<type_t>::type      rtype_t;
    typedef typename boost::proto::result_of::child_c<A1&, 2>::value_type tag_t;
    typedef typename tag_t::value_type::option_type  method_t;

    result_type operator()(A0& out, const A1& in ) const
    {
      auto x0 = boost::proto::child_c<1>(in);
      auto f =  boost::proto::value(boost::proto::child_c<0>(in));
      compute(out, f, x0, N());
      return out;
    }
  private :
    template < class A, class F, class X>
    static void compute(A& out, const F & f,  const X& x, const boost::mpl::long_<3> &)
    {
      out = functor<method_t>()(f, x);
    }
    template <class A, class F, class X>
    static void compute(A& out, const F & f,  const  X& x, const boost::mpl::long_<4> &)
    {
      typedef typename boost::proto::result_of::child_c<A1&, 3>::value_type opt_t;
      out = functor<method_t>()(f, x, opt_t());
    }
  };


} }

#endif
