//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_CORE_FUNCTIONS_EXTENT_SIZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXTENT_SIZE_HPP_INCLUDED

#include <nt2/core/settings/size.hpp>
#include <nt2/core/functions/size.hpp>
#include <nt2/core/container/extent/extent.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::size_, tag::cpu_
                            , (A0)(S0)
                            , ((expr_ < boost::dispatch::meta::extent_<A0,S0> 
                                      , nt2::container::domain
                                      , boost::proto::tag::terminal
                                      >
                              ))
                            )
  {
    typedef container::
            extent< of_size_< 1
                            , A0::static_dimensions ? A0::static_dimensions : 1
                            > 
                  > result_type;

    BOOST_DISPATCH_FORCE_INLINE 
    result_type operator()(A0 const&) const
    {
      result_type that;
      return that;
    }
  };
} }

#endif
