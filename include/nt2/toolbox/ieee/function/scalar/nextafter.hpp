//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_NEXTAFTER_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_NEXTAFTER_HPP_INCLUDED

#include <nt2/include/functions/sign.hpp>
#include <nt2/sdk/constant/digits.hpp>

#include <nt2/toolbox/ieee/details/math.hpp>
#include <boost/math/special_functions/next.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::nextafter_, tag::cpu_,
                           (A0)(A1),
                           (arithmetic_<A0>)(arithmetic_<A1>)
                          )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::nextafter_(tag::arithmetic_,tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      return a0+sign(a1-a0);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::nextafter_, tag::cpu_,
                           (A0)(A1),
                           (double_<A0>)(double_<A1>)
                          )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::nextafter_(tag::double_,tag::double_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
    #ifdef NT2_TOOLBOX_IEEE_HAS_NEXTAFTER
      return ::nextafter(a0, a1);
    #elif defined(NT2_TOOLBOX_IEEE_HAS__NEXTAFTER)
      return ::_nextafter(a0, a1);
    #else
      return boost::math::nextafter(a0, a1);
    #endif
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::nextafter_, tag::cpu_,
                           (A0)(A1),
                           (float_<A0>)(float_<A1>)
                          )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::nextafter_(tag::float_,tag::float_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
    #ifdef NT2_TOOLBOX_IEEE_HAS_NEXTAFTERF
      return ::nextafterf(a0, a1);
    #elif defined(NT2_TOOLBOX_IEEE_HAS__NEXTAFTERF)
      return ::_nextafterf(a0, a1);
    #else
      return boost::math::nextafter(a0, a1);
    #endif
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::nextafter_, tag::cpu_,
                           (A0)(A1),
                           (unsigned_<A0>)(unsigned_<A1>)
                          )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::nextafter_(tag::unsigned_,tag::unsigned_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      return (a1 == a0) ? a0 : (a1 > a0) ? a0+One<A0>() : a0-One<A0>();
    }
  };
} }

#endif
// modified by jt the 26/12/2010
