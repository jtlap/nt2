//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_FAST_FREXP_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_FAST_FREXP_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/shri.hpp>
#include <nt2/include/functions/bitwise_andnot.hpp>
#include <boost/fusion/include/vector.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::fast_frexp_, tag::cpu_,
                             (A0)(X),
                             ((simd_<arithmetic_<A0>,X>))
                            );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::fast_frexp_(tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
     {
       typedef typename meta::strip<A0>::type                     A00;
       typedef typename meta::as_integer<A00, signed>::type  exponent;
       typedef boost::fusion::vector<A00,exponent>                type;
     };

    NT2_FUNCTOR_CALL(1)
    {
      typename NT2_RETURN_TYPE(1)::type res;
      eval( a0
          , boost::fusion::at_c<0>(res)
          , boost::fusion::at_c<1>(res)
          );
      return res;
    }
  private:
    template<class A0,class R0,class R1> inline void
    eval(A0 const& a0,R0& r0, R1& r1)const
    {
      typedef typename meta::as_integer<A0, signed>::type      int_type;
      typedef typename meta::scalar_of<int_type>::type        sint_type;
      typedef typename meta::scalar_of<A0>::type                 s_type;
      static const sint_type me = Maxexponent<s_type>()-1;
      static const sint_type nmb= Nbmantissabits<s_type>();
      static const int_type vn1 = nt2::splat<int_type>((2*me+3)<<nmb);
      static const sint_type n2 = me<<nmb;
      r1 = b_and(vn1, a0);                                 //extract exponent
      A0 x = b_andnot(a0, vn1);                            //clear exponent in a0
      r1 = shri(r1,nmb) - splat<int_type>(me);             //compute exponent
      r0 = b_or(x,splat<int_type>(n2));                    //insert expon+1 in x
    }
  };
} }

#endif
// modified by jt the 04/01/2011