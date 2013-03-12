//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
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


namespace nt2{ namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::null_, tag::cpu_,
                                       (A0)(A1),
                                       ((ast_<A0, nt2::container::domain>))
                                       (scalar_<floating_<A1> > )
                                       )
  {
    BOOST_DISPATCH_RETURNS(2, (const A0& a0, const A1 epsi),
                           (nt2::factorization::svd<A0>(a0, 'N', 'O').null(epsi))
                           )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::null_, tag::cpu_,
                                     (A0),
                                     ((ast_<A0, nt2::container::domain>))
                                     )
  {
    typedef typename A0::value_type               value_type;
    BOOST_DISPATCH_RETURNS(1, (const A0& a0),
                           (nt2::factorization::svd<A0>(a0, 'N', 'O').null(Mone<value_type>()))
                           )
  };

} }


#endif

