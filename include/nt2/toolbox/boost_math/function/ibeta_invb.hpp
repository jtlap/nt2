//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BOOST_MATH_FUNCTION_IBETA_INVB_HPP_INCLUDED
#define NT2_TOOLBOX_BOOST_MATH_FUNCTION_IBETA_INVB_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>
#include <boost/math/special_functions/beta.hpp>

namespace nt2 { namespace boost_math
  {	       
    struct ibeta_invb_ {};
    NT2_FUNCTION_IMPLEMENTATION(boost_math::ibeta_invb_, ibeta_invb, 3)
  }
}
 
#include <nt2/toolbox/boost_math/function/scalar/ibeta_invb.hpp>
// #include NT2_BOOST_MATH_INCLUDE(ibeta_invb.hpp) 

 
#endif
