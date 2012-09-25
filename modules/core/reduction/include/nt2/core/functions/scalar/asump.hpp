//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_ASUMP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_ASUMP_HPP_INCLUDED

#include <nt2/core/functions/asump.hpp>
#include <nt2/include/functions/scalar/pow_abs.hpp>

/// TODO include complex cases
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asump_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< floating_<A0> >)
                              (scalar_< arithmetic_<A1> > )
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a, A1 const& p) const
    {
      return nt2::pow_abs(a, p);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asump_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< floating_<A0> >)
                              (scalar_< arithmetic_<A1> > )
                              (scalar_< integer_<A2> > )
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a, A1 const& p, A2 const&) const
    {
      return nt2::pow_abs(a, p);
    }
  };
} }

#endif
