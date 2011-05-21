//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SCALAR_COMPARE_GREATER_EQUAL_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SCALAR_COMPARE_GREATER_EQUAL_HPP_INCLUDED

NT2_REGISTER_DISPATCH( tag::compare_greater_equal_, tag::cpu_
                     , (A0)(A1)
                     , (fundamental_<A0>)(fundamental_<A1>)
                     );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call<tag::compare_greater_equal_(tag::fundamental_,tag::fundamental_), tag::cpu_, Dummy>
        : callable
  {
    typedef bool result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return a0 >= a1;
    }
  };
} } 

#endif
