//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_MOLER_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_MOLER_HPP_INCLUDED
#include <nt2/toolbox/linalg/functions/moler.hpp>
#include <nt2/include/functions/triw.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/constants/mone.hpp>

namespace nt2
{
  namespace ext
  {

    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::moler_, tag::cpu_,
                                (A0)(T),
                                (scalar_<integer_<A0> >)
                                (target_<scalar_<floating_<T> > > )
                              )
    {
      typedef typename T::type t_t;
      BOOST_DISPATCH_RETURNS(2, (A0 const& n, T const& t),
                             (nt2::moler(n, nt2::Mone<t_t>()))
                            )
        };

    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::moler_, tag::cpu_,
                                (A0)(A1),
                                (scalar_<integer_<A0> >)
                                (scalar_<floating_<A1> >)

                              )
    {
      BOOST_DISPATCH_RETURNS(2, (A0 const& n, A1 const& a1),
                             (nt2::mtimes(ctranspose(nt2::triw(n, n, a1)),nt2::triw(n, n, a1)))
                            )
        };

  }


  meta::call<tag::moler_(const ptrdiff_t &, meta::as_<double> const &)>::type
  moler(ptrdiff_t n)
  {
    return nt2::moler(n,  meta::as_<double>());
  }
  template<class T>
  typename meta::call<tag::moler_(const ptrdiff_t &, typename meta::as_<T> const &)>::type
  moler(ptrdiff_t n)
  {
    return nt2::moler(n,  meta::as_<T>());
  }

}


#endif
