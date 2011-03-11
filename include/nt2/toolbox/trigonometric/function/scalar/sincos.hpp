//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_SINCOS_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_SINCOS_HPP_INCLUDED
#include <boost/fusion/tuple.hpp>
#include <nt2/toolbox/trigonometric/function/scalar/impl/trigo.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::sincos_, tag::cpu_,
                        (A0),
                        (arithmetic_<A0>)
                       )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::sincos_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename std::tr1::result_of<meta::floating(A0)>::type etype;
      typedef boost::fusion::tuple<etype, etype>                   type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename std::tr1::result_of<meta::floating(A0)>::type type;
      return sincos(type(a0));
    }

  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::sincos_, tag::cpu_,
                        (A0),
                        (real_<A0>)
                       )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::sincos_(tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename meta::strip<A0>::type          etype;
      typedef boost::fusion::tuple<etype, etype>       type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      typename NT2_RETURN_TYPE(1)::type res;
      impl::trig_base < A0,radian_tag
                      , trig_tag, tag::not_simd_type
                      >::sincosa( a0
                                , boost::fusion::at_c<0>(res)
                                , boost::fusion::at_c<1>(res)
                                );
      return res;
    }

  };
} }

#endif
// modified by jt the 22/01/2011

