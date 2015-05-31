//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_FUNCTIONS_GENERIC_COS_HPP_INCLUDED
#define NT2_AD_FUNCTIONS_GENERIC_COS_HPP_INCLUDED

#include <nt2/include/functions/cos.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2 { namespace ad
{
  template < class T>
  valder<T> cos(const valder<T>&u)
  {
    return valder<T>(cos(u.val()), -sin(u.val())*u.der());
  };

} }

#endif
