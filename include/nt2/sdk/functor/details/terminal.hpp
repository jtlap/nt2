/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_DETAILS_TERMINAL_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_DETAILS_TERMINAL_HPP_INCLUDED

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // Special functor for handling terminal in expression AST evaluation
  //////////////////////////////////////////////////////////////////////////////
  template<class Info> struct functor<terminal_,Info>
  {
    struct validate { typedef boost::mpl::true_ result_type; };

    template<class Sig> struct result;
    template<class This,class V,class S,class D>
    struct result<This(V,S,D)>
    {
      typedef typename meta::category_of<V>::type::tag          dom;
      typedef functors::call<terminal_,dom,Info>                callee;
      typedef typename std::tr1::result_of<callee(V,S,D)>::type type;
    };

    template<class V,class S,class D> inline
    typename result<functor(V,S,D)>::type
    operator()(V& v, S s, D& d) const
    {
      typedef typename meta::category_of<V>::type::tag  dom;
      call<terminal_,dom,Info>                              callee;
      return callee(v,s,d);
    }
  };
} }

#endif
