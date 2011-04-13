/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_META_HIERARCHY_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_META_HIERARCHY_HPP_INCLUDED

#include <nt2/sdk/meta/hierarchy.hpp>

namespace nt2 { namespace tag
{
  NT2_HIERARCHY_CLASS(formal_, meta::unspecified_<formal_>);
  NT2_HIERARCHY_CLASS(cpu_, formal_);
}
}

#endif
