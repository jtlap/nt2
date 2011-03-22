//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SCALAR_COMPARATOR_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SCALAR_COMPARATOR_HPP_INCLUDED
#include <boost/fusion/tuple.hpp>

#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/any.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::comparator_, tag::cpu_,
                            (A0)(A1)(A2),
                            (arithmetic_<A0>)(arithmetic_<A1>)(arithmetic_<A2>)
                           )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::comparator_(tag::arithmetic_,tag::arithmetic_,tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A2>
    struct result<This(A0, A0, A2)>
    {
      typedef typename meta::strip<A0>::type           stA0;
      typedef boost::fusion::tuple<stA0,stA0,bool>     type;
    };

    NT2_FUNCTOR_CALL(3)
    {
      typename NT2_RETURN_TYPE(3)::type res;
      eval( a0, a1, a2
           , boost::fusion::at_c<0>(res)
           , boost::fusion::at_c<1>(res)
           , boost::fusion::at_c<2>(res)
           );
      return res;
    }
  private:
    template<class A0,class A2,class R0,class R1> inline void
    eval(A0 const& a0, A0 const& a1, A2 const& a2, R0& r0, R1& r1, bool& modified)const
    {
      r0 = a0;
      r1 = a1;
      if (a2)
      {
        if ( (modified = (a0 > a1)) ) std::swap(r0, r1);
      }
      else
      {
        if ( (modified = (a1 > a0)) ) std::swap(r0, r1);
      }
//       r0 =  nt2::min(a0, a1);
//       r1 =  nt2::max(a0, a1);
//       if (a2) {
//    A0 t =  r1;
//    r1 = r0;
//    r0 = t;
//       }
//       modified = any(a0-r0);
    }

  };
} }

#endif
// modified by jt the 26/12/2010
