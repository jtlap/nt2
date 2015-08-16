///==============================================================================
///         Copyright 2015 J.T. Lapreste
///
///          Distributed under the Boost Software License, Version 1.0.
///                 See accompanying file LICENSE.txt or copy at
///                     http:///www.boost.org/LICENSE_1_0.txt
///==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TABLE_MK_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TABLE_MK_HPP_INCLUDED

#include <nt2/core/functions/mk.hpp>


namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( mk_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<integer_<A0>>)
                              (unspecified_<A1>)
                            )
  {
    typedef void                        result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0&, A1) const
    { }
  };
} }

#endif
