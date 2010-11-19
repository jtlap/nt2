//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BOOST_MATH_FUNCTION_SCALAR_ELLINT_RJ_HPP_INCLUDED
#define NT2_TOOLBOX_BOOST_MATH_FUNCTION_SCALAR_ELLINT_RJ_HPP_INCLUDED

namespace nt2 { namespace functors
{
  template<class Info>
  struct validate<boost_math::ellint_rj_,tag::scalar_(tag::arithmetic_),Info>
    {
      template<class Sig> struct result;
      template<class This,class A0, class A1, class A2, class A3>
      struct result<This(A0, A1, A2, A3)> :
        boost::mpl::and_<
           meta::has_smaller_size<A0,long double>,
           meta::has_smaller_size<A1,long double>,
           meta::has_smaller_size<A2,long double>,
           meta::has_smaller_size<A3,long double>
        >{};
    };
  /////////////////////////////////////////////////////////////////////////////
  // Compute ellint_rj(const A0& a0, const A1& a1, const A2& a2, const A3& a3)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<boost_math::ellint_rj_,tag::scalar_(tag::arithmetic_),real_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1, class A2, class A3>
    struct result<This(A0, A1, A2, A3)> : 
      boost::result_of<meta::floating(A0, A1, A2, A3)>{};

    NT2_FUNCTOR_CALL(4){ return boost::math::ellint_rj(a0, a1, a2, a3); }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<boost_math::ellint_rj_,tag::scalar_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1, class A2, class A3>
    struct result<This(A0, A1, A2, A3)> : 
      boost::result_of<meta::floating(A0, A1, A2, A3)>{};

    NT2_FUNCTOR_CALL(4)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type;
      return nt2::boost_math::ellint_rj(type(a0), type(a1), type(a2), type(a3));
    }
  };

} }

#endif
/// Revised by jt the 16/11/2010
