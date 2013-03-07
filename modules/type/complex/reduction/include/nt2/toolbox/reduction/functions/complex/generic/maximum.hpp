//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTIONS_COMPLEX_GENERIC_MAXIMUM_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTIONS_COMPLEX_GENERIC_MAXIMUM_HPP_INCLUDED

#include <nt2/toolbox/reduction/functions/maximum.hpp>
#include <nt2/include/functions/posmax.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <nt2/include/constants/maxinit.hpp> // This include is sort of weird
// as the file do not uses maxinit
// but it is necessary to include this somewhere for changing the to the  complex
// ordering used in max complex determination.

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::maximum_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef typename boost::dispatch::meta::scalar_of<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return a0[posmax(a0)];
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::maximum_, tag::cpu_, (A0)
                            , (generic_< imaginary_< arithmetic_<A0> > >)
                            )
  {
    typedef typename boost::dispatch::meta::scalar_of<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return result_type(nt2::maximum(nt2::imag(a0)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::maximum_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef typename boost::dispatch::meta::scalar_of<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return result_type(nt2::maximum(nt2::real(a0)));
    }
  };
} }

#endif
