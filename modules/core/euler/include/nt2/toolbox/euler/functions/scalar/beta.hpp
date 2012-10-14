//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_SCALAR_BETA_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_SCALAR_BETA_HPP_INCLUDED
#include <nt2/toolbox/euler/functions/beta.hpp>
#include <boost/math/special_functions.hpp>
#include <nt2/sdk/error/policies.hpp>

/**
 * \ingroup euler_beta
 * \defgroup euler_beta_scalar Notes on the scalar implementation
 * 
 * \par Specificities
 *
 *  Some info on \c beta in scalar mode  
 **/

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::beta_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)(scalar_< arithmetic_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return boost::math::beta(result_type(a0), result_type(a1), nt2_policy());
    }
  };
} }


#endif
