//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SCALAR_ALL_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SCALAR_ALL_HPP_INCLUDED

#include <nt2/include/functions/is_nez.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for all

  /////////////////////////////////////////////////////////////////////////////
  // Compute all(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<all_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;

    // see documentation http://nt2.lri.fr/extension/custom_function.html
    // for writing the functor implementation code 
    // with or without type dispatching

  };
} }


      
#endif
