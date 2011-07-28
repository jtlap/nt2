//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_COMMON_PLUS_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_COMMON_PLUS_HPP_INCLUDED

//////////////////////////////////////////////////////////////////////////////
/// mixed scalar/simd plus
//////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::plus_, tag::cpu_, 
			      (A0)(A1)(X), 
			      ((simd_<arithmetic_ <A0>,X>))((scalar_<arithmetic_<A1> >))
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return nt2::plus(a0, nt2::splat<A0>(a1)); 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( tag::plus_, tag::cpu_, 
			      (A0)(A1)(X), 
			      ((scalar_<arithmetic_<A0> >))((simd_<arithmetic_<A1>,X>))
                            )
  {
    typedef A1 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return nt2::plus(a1, nt2::splat<A0>(a0)); 
    }
  };

} }


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of plus.hpp
// /////////////////////////////////////////////////////////////////////////////
