/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_FORSYTHE_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_FORSYTHE_HPP_INCLUDED
#include <nt2/toolbox/linalg/functions/forsythe.hpp>
#include <nt2/include/functions/jordbloc.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/ones.hpp>

namespace nt2 {namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::forsythe_, tag::cpu_,
                              (A0)(A1)(A2),
                              (scalar_<integer_<A0> >)
                              (scalar_<floating_<A1> >)
                              (scalar_<floating_<A2> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(3, (A0 const& n, A1 const& alpha, A2 const& l),
                           (nt2::jordbloc(n, l)+alpha*nt2::from_diag(nt2::ones(1, 1, meta::as_<A1>()),-ptrdiff_t(n-1)))
                          )
  };

} }

#endif
