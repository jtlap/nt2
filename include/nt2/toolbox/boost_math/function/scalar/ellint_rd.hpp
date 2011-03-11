//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BOOST_MATH_FUNCTION_SCALAR_ELLINT_RD_HPP_INCLUDED
#define NT2_TOOLBOX_BOOST_MATH_FUNCTION_SCALAR_ELLINT_RD_HPP_INCLUDED


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(boost_math::tag::ellint_rd_, tag::cpu_,
                           (A0)(A1)(A2),
                           (arithmetic_<A0>)(arithmetic_<A1>)(arithmetic_<A2>)
                          )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<boost_math::tag::ellint_rd_(tag::arithmetic_,tag::arithmetic_,tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1, class A2>
    struct result<This(A0, A1, A2)> :
      std::tr1::result_of<meta::floating(A0, A1, A2)>{};

    NT2_FUNCTOR_CALL(3)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      return nt2::boost_math::ellint_rd(type(a0), type(a1), type(a2));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(boost_math::tag::ellint_rd_, tag::cpu_,
                           (A0)(A1)(A2),
                           (real_<A0>)(real_<A1>)(real_<A2>)
                          )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<boost_math::tag::ellint_rd_(tag::real_,tag::real_,tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1, class A2>
    struct result<This(A0, A1, A2)> :
      std::tr1::result_of<meta::floating(A0, A1, A2)>{};

    NT2_FUNCTOR_CALL(3){ return boost::math::ellint_rd(a0, a1, a2); }
  };
} }

#endif
// modified by jt the 26/12/2010
