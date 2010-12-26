//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_REMQUO_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_REMQUO_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/mpl/vector.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::remquo_, tag::cpu_,
                        (A0)(A1),
                        (fundamental_<A0>)(fundamental_<A1>)
                       )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::remquo_(tag::fundamental_,tag::fundamental_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)>
    {
      typedef typename boost::result_of<meta::floating(A0,A1)>::type rem;
      typedef typename meta::as_integer<A0,signed>::type             quo;
      typedef boost::fusion::tuple<rem,quo>                         type;
    };

    NT2_FUNCTOR_CALL(2)
    {
      typename NT2_RETURN_TYPE(2)::type res;
      typedef meta::find_type<A0,float,double,empty_> set_t;
      eval( a0, a1
          , boost::fusion::at_c<0>(res),  boost::fusion::at_c<1>(res)
          , typename set_t::type()
          );
      return res;
    }
  private :
    template<class A0,class A1,class R0,class R1> inline void
    eval(A0 const& a0,A1 const& a1,R0& r0, R1& r1, double const &)const
    {
       int rt;
       r0 = ::remquo(a0, a1, &rt);
       r1 = rt;
    }

    template<class A0,class A1,class R0,class R1> inline void
    eval(A0 const& a0,A1 const& a1,R0& r0, R1& r1, float const &)const
    {
       r0 = ::remquof(a0, a1, &r1);
    }
  };
} }

#endif
// modified by jt the 26/12/2010