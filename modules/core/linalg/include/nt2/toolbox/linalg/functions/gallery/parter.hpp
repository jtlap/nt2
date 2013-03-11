/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_PARTER_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_PARTER_HPP_INCLUDED
#include <nt2/toolbox/linalg/functions/parter.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/cauchy.hpp>

namespace nt2
{
  namespace ext
  {

    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::parter_, tag::cpu_,
                                (A0)(T),
                                (scalar_<integer_<A0> >)
                                (target_<scalar_<floating_<T> > > )
                              )
    {
      typedef typename T::type t_t;
      BOOST_DISPATCH_RETURNS(2, (A0 const& n, T const& t),
                             (nt2::cauchy(nt2::_(t_t(1.5), t_t(n+0.5)), -nt2::_(t_t(1), t_t(n))))
                            )
        };
  }


  meta::call<tag::parter_(const ptrdiff_t &, meta::as_<double> const &)>::type
  parter(ptrdiff_t n)
  {
    return nt2::parter(n,  meta::as_<double>());
  }
  template<class T>
  typename meta::call<tag::parter_(const ptrdiff_t &, typename meta::as_<T> const &)>::type
  parter(ptrdiff_t n)
  {
    return nt2::parter(n,  meta::as_<T>());
  }

}


#endif
