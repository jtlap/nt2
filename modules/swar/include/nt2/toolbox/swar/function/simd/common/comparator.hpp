//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_COMMON_COMPARATOR_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_COMMON_COMPARATOR_HPP_INCLUDED
#include <boost/mpl/vector.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/any.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::comparator_, tag::cpu_,
                             (A0)(A2)(X),
                             ((simd_<arithmetic_<A0>,X>))
                             ((simd_<arithmetic_<A0>,X>))
                             ((integer_<A2>))
                            );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::comparator_(tag::simd_<tag::arithmetic_, X> ,
                               tag::simd_<tag::arithmetic_, X> ,
                               tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A2>
    struct result<This(A0,A0,A2)>
    {
      typedef typename meta::strip<A0>::type                       nA0;
      typedef boost::fusion::vector<nA0,nA0,int>                   type;
    };

    NT2_FUNCTOR_CALL(3)
    {
      typedef typename NT2_RETURN_TYPE(3)::type r_t;
      r_t res;
      if (a2)
	{
	  boost::fusion::at_c<1>(res) =  nt2::min(a0, a1);
	  boost::fusion::at_c<0>(res) =  nt2::max(a0, a1);
	}
      else
	{
	  boost::fusion::at_c<0>(res) =  nt2::min(a0, a1);
	  boost::fusion::at_c<1>(res) =  nt2::max(a0, a1);
	}
      boost::fusion::at_c<2>(res) = nt2::any(a0-boost::fusion::at_c<0>(res)); 
      return res; 
    }

  };
} }

#endif
// modified by jt the 05/01/2011
