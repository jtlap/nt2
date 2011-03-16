//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BOOST_MATH_FUNCTION_SCALAR_LEGENDRE_NEXT_HPP_INCLUDED
#define NT2_TOOLBOX_BOOST_MATH_FUNCTION_SCALAR_LEGENDRE_NEXT_HPP_INCLUDED


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A2 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(boost_math::tag::legendre_next_, tag::cpu_,
                               (A0)(A1)(A2)(A3)(A4),
                               (integer_<A0>)(integer_<A1>)(arithmetic_<A2>)(arithmetic_<A3>)(arithmetic_<A4>)
                              )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<boost_math::tag::legendre_next_(tag::integer_,tag::integer_,tag::arithmetic_,tag::arithmetic_,tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1, class A2, class A3, class A4>
    struct result<This(A0, A1, A2, A3, A4)> :
      std::tr1::result_of<meta::floating(A2, A3, A4)>{};

    NT2_FUNCTOR_CALL(5)
    {
      typedef typename NT2_RETURN_TYPE(5)::type type;
      return legendre_next(a0, a1, type(a2), type(a3), type(a4));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(boost_math::tag::legendre_next_, tag::cpu_,
                               (A0)(A1)(A2)(A3)(A4),
                               (integer_<A0>)(integer_<A1>)(real_<A2>)(real_<A3>)(real_<A4>)
                              )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<boost_math::tag::legendre_next_(tag::integer_,tag::integer_,tag::real_,tag::real_,tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1, class A2, class A3, class A4>
    struct result<This(A0, A1, A2, A3, A4)> :
      std::tr1::result_of<meta::floating(A2, A3, A4)>{};

    NT2_FUNCTOR_CALL(5){ return boost::math::legendre_next(a0, a1, a2, a3, a4); }
  };
} }

#endif
// modified by jt the 29/12/2010
