//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_MODELS_FUNCTION_MODEL_FOUR_BRANCHES_HPP_INCLUDED
#define NT2_TOOLBOX_MODELS_FUNCTION_MODEL_FOUR_BRANCHES_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/toolbox/models/include.hpp>

namespace nt2 { namespace functors
  {	       
    struct model_four_branches_ {};
  }
  NT2_FUNCTION_IMPLEMENTATION(functors::model_four_branches_, model_four_branches, 1)
}
 
#include <nt2/toolbox/models/function/scalar/model_four_branches.hpp>
#include NT2_MODELS_INCLUDE(model_four_branches.hpp) 

 
#endif
