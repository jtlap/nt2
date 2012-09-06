/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_NULL_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_NULL_HPP_INCLUDED
#include <nt2/include/functions/null.hpp>
#include <nt2/include/functions/svd.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/asin.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/orth.hpp>
#include <nt2/include/functions/norm.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/table.hpp>

namespace nt2{ namespace ext
{
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::null_, tag::cpu_,
                                (A0)(A1), 
                                ((ast_<A0>))
                                (scalar_<floating_<A1> > )
                                )
  {
    typedef typename A0::value_type value_type; 
    typedef nt2::table<value_type> result_type; 
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(const A0& a0, const A1 & a1) const
    {
      return nt2::factorization::svd<A0>(a0, 'N', 'O').null(a1); 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::null_, tag::cpu_,
                              (A0),
                              ((ast_<A0>))
                              )
  {
    typedef typename A0::value_type value_type;
    typedef nt2::table<value_type> result_type; 
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(const A0& a0) const
    {
      return nt2::factorization::svd<A0>(a0, 'N', 'O').null(Mone<value_type>()); 
    }
  };

} }


#endif

