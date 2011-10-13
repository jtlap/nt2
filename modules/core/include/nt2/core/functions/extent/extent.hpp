//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_CORE_FUNCTIONS_EXTENT_EXTENT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXTENT_EXTENT_HPP_INCLUDED

#include <nt2/core/settings/size.hpp>
#include <nt2/core/functions/extent.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::extent_, tag::cpu_
                            , (A0)(S0)
                            , ((boost::dispatch::meta::extent_<A0, S0>))
                            )
  {
    typedef S0 const& result_type;
    static S0 const sz;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0& a0) const { return sz; }
  };
} }

#endif
