//==============================================================================
//         Copyright 2015          J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_OPTIONS_HPP_INCLUDED
#define NT2_LINALG_OPTIONS_HPP_INCLUDED

#include <nt2/core/options.hpp>
#include <nt2/sdk/meta/policy.hpp>

namespace nt2
{
  namespace ext
  {
    struct forward_    : boost::mpl::true_  {}; //used in deriv, jac
    struct backward_   : boost::mpl::true_  {}; //used in deriv, jac
    struct centered_   : boost::mpl::true_  {}; //used in deriv, jac
    struct pow2den_    : boost::mpl::true_  {}; //used in forward,  bacward, centered, deriv, jac
  }

  nt2::policy<ext::forward_>      const forward_;
  nt2::policy<ext::backward_>     const backward_;
  nt2::policy<ext::centered_>     const centered_;
  nt2::policy<ext::pow2den_>       const pow2den_;
 }

#endif
