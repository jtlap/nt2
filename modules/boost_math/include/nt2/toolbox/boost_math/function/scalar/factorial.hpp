//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BOOST_MATH_FUNCTION_SCALAR_FACTORIAL_HPP_INCLUDED
#define NT2_TOOLBOX_BOOST_MATH_FUNCTION_SCALAR_FACTORIAL_HPP_INCLUDED
#include <nt2/toolbox/boost_math/specific/interface.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is integer_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(boost_math::tag::factorial_<T>, tag::cpu_,
		      (A0)(T),
		      (integer_<A0>)
		      )

namespace nt2 { namespace ext
{
  template<class T, class Dummy>
  struct call<boost_math::tag::factorial_<T>(tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    typedef T result_type; 

    NT2_FUNCTOR_CALL(1)
    {
      return boost::math::factorial<T>(a0, nt2_policy());
    }
  };
} }

#endif
// modified by jt the 29/12/2010
