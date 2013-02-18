/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_FRANK_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_FRANK_HPP_INCLUDED
#include <nt2/toolbox/linalg/functions/frank.hpp>
#include <nt2/include/functions/minij.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/fliplr.hpp>
#include <nt2/include/functions/flipud.hpp>
#include <nt2/include/functions/trans.hpp>

namespace nt2 {namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::frank1_, tag::cpu_,
                              (A0)(T),
                              (scalar_<integer_<A0> >)
                              (target_<scalar_<unspecified_<T> > >)
                             )
  {
    typedef typename meta::call<tag::minij_(A0 const&, T)>::type            T1;
    typedef typename meta::call<tag::offset_triu_(T1, ptrdiff_t)>::type   result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& n,T const &)
    {
      return triu(minij(n,T()), ptrdiff_t(-1));
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::frank0_, tag::cpu_,
                              (A0)(T),
                              (scalar_<integer_<A0> >)
                              (target_<scalar_<unspecified_<T> > >)
                             )
  {
    typedef typename meta::call<tag::frank1_(A0 const&,T)>::type  T1;
    typedef typename meta::call<tag::fliplr_(T1)>::type           T2;
    typedef typename meta::call<tag::flipud_(T2)>::type           T3;
    typedef typename meta::call<tag::trans_(T3)>::type   result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& n, T const &)
    {
      return nt2::trans(nt2::flipud(nt2::fliplr(nt2::frank1(n, T()))));
    }
  };

} }

#endif
