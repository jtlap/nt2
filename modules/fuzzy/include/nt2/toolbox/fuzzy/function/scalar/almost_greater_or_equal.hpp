//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_FUZZY_FUNCTION_SCALAR_ALMOST_GREATER_OR_EQUAL_HPP_INCLUDED
#define NT2_TOOLBOX_FUZZY_FUNCTION_SCALAR_ALMOST_GREATER_OR_EQUAL_HPP_INCLUDED
#include <nt2/include/functions/predecessor.hpp>
#include <nt2/include/functions/is_inf.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::almost_greater_or_equal_, tag::cpu_,
                                         (A0)(A1)(A2),
                                         (arithmetic_<A0>)(arithmetic_<A1>)(integer_<A2>)
                                        )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::almost_greater_or_equal_(tag::arithmetic_,tag::arithmetic_,tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    typedef bool result_type; 
    
    NT2_FUNCTOR_CALL(3)
    {
      return a0 >= a1-a2;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::almost_greater_or_equal_, tag::cpu_,
                                         (A0)(A1)(A2),
                                         (real_<A0>)(real_<A1>)(integer_<A2>)
                                        )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::almost_greater_or_equal_(tag::real_,tag::real_,tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    typedef bool result_type; 

    NT2_FUNCTOR_CALL(3)
    {
      if (a0 == a1) return true;
      if (is_inf(a0) || is_inf(a1)) return (a0 == a1);
      if (is_nan(a0) || is_nan(a1)) return false;
      // see http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
      // by Bruce Dawson
      // Do not choose a2 negative or too large
      // assert(aa2 > 0 && aa2 < bitinteger(Nan<select_type>()) );
      return  a0 >= predecessor(a1, a2); 
    }
  };
} }

#endif
// modified by jt the 26/12/2010
