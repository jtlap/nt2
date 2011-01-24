//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_SUCCESSOR_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_SUCCESSOR_HPP_INCLUDED
#include <nt2/sdk/constant/infinites.hpp>

#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/bitinteger.hpp>
#include <nt2/include/functions/bitfloating.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/sdk/constant/real.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::successor_, tag::cpu_,
                           (A0),
                           (arithmetic_<A0>)
                          )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::successor_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
<<<<<<< HEAD
    struct result<This(A0)> : boost::mpl::true_ {};

    template<class This,class A0,class A1>
    struct  result<This(A0,A1)>
          : boost::is_integral<typename nt2::meta::strip<A1>::type > {};
=======
      struct result<This(A0)> : meta::strip<A0> {};
    NT2_FUNCTOR_CALL(1){ return oneplus(a0); }
>>>>>>> functor2
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::successor_, tag::cpu_,
                           (A0),
                           (real_<A0>)
                          )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::successor_(tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> : meta::strip<A0> {};
    NT2_FUNCTOR_CALL(1)
    {
      return is_inf(a0) || is_nan(a0) ? Nan<A0>()  : bitfloating(oneplus(bitinteger(a0)));
    }
<<<<<<< HEAD
    NT2_FUNCTOR_CALL(2)
    {
       return is_inf(a0) || is_nan(a0) ? Nan<A0>()  : bitfloating(bitinteger(a0)+a1);
    }

=======
>>>>>>> functor2
  };
} }

NT2_REGISTER_DISPATCH(tag::successor_, tag::cpu_,
                           (A0)(A1),
                           (arithmetic_<A0>)(integer_<A1>)
                          )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::successor_(tag::arithmetic_, tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
      struct result<This(A0, A1)> : meta::strip<A0> {};
    NT2_FUNCTOR_CALL(2){ return a0+a1;       }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::successor_, tag::cpu_,
		      (A0)(A1),
		      (real_<A0>)(integer_<A1>)
                          )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::successor_(tag::real_, tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
      struct result<This(A0, A1)> : meta::strip<A0> {};
    NT2_FUNCTOR_CALL(2)
    {
       return a0==Inf<A0>() ? a0 : bitfloating(bitinteger(a0)+a1);
    }

  };
} }

#endif
// modified by jt the 26/12/2010
// modified manually by jt the 02/01/2011 
