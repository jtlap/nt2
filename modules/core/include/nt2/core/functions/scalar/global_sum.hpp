//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_CORE_FUNCTIONS_SCALAR_GLOBAL_SUM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_GLOBAL_SUM_HPP_INCLUDED

#include <nt2/core/functions/global_sum.hpp>


namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::global_sum_, tag::cpu_
                            , (A0), (scalar_< unspecified_<A0> >)
                            )
  {
    typedef A0 result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0& a0) const { return a0; }
  };

} }

#endif
