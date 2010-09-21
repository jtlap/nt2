//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_AT_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_AT_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/toolbox/reduction/include.hpp>

// namespace nt2 { namespace functors
//   {	       
//     template<std::size_t Idx> struct at_ {};
//   }
  
//   template<std::size_t Idx, class A0>
//   inline NT2_FUNCTION_RETURN_TYPE(functors::at_<Idx>,1)
//   at(A0 const& a0)
//   {
//     NT2_FUNCTION_BODY(functors::at_<Idx>,1)
//   }

//   template<std::size_t Idx, class A0>
//   inline NT2_FUNCTION_RETURN_TYPE(functors::at_<Idx>,1)
//   extract(A0 const& a0)
//   {
//     NT2_FUNCTION_BODY(functors::at_<Idx>,1)
//   }

//   NT2_FUNCTION_IMPLEMENTATION( functors::at_<0>, at     , 2)
//   NT2_FUNCTION_IMPLEMENTATION( functors::at_<0>, extract, 2)
// }

 
#include <nt2/toolbox/reduction/function/scalar/at.hpp>
#include NT2_REDUCTION_INCLUDE(at.hpp) 

 
#endif
