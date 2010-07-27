/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DSL_RECURSIVE_PROCESS_HPP_INCLUDED
#define NT2_SDK_DSL_RECURSIVE_PROCESS_HPP_INCLUDED

#include <boost/mpl/apply.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/make_expr.hpp>
#include <nt2/sdk/dsl/push_front.hpp>

namespace nt2 { namespace dsl
{
  template<class Visitor> struct compile;
} }

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Base of a Proto primitive transform that handle node evaluation by calling
  // proto::_default after building some function expression.
  //////////////////////////////////////////////////////////////////////////////
  template< class Visitor, class Tag> struct recursive_process
  {
    typedef typename boost::mpl::apply<Visitor,Tag>::type               visit;
    typedef typename boost::proto::terminal<visit>::type                term;
    typedef boost::proto::functional::unpack_expr<functors::function_>  upck;
    typedef boost::proto::_default< dsl::compile<Visitor> >            descent;

    template<class X> struct unpacker
    {
      typedef typename boost::result_of<meta::push_front(X,term)>::type xpr;
      typedef typename boost::result_of<upck(xpr)>::type                type;
    };

    template<class Sig> struct result;
    template<class This,class X,class S,class D>
    struct  result<This(X,S,D)>
          : boost::result_of<descent(typename unpacker<X>::type,S,D)>
    {};

    template<class X,class S,class D>
    inline typename result<recursive_process(X,S,D)>::type
    operator()( X& x, S& s, D& d ) const
    {
      return descent()(upck()(meta::push_front()(x,term())),s,d);
    }
  };
} }

#endif
