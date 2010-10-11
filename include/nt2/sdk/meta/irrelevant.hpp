/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_IRRELEVANT_HPP_INCLUDED
#define NT2_SDK_META_IRRELEVANT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Category tag for types not handled by nt2 by design
// Documentation: http://nt2.lri.fr/sdk/meta/tag/unknown.html
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/config/types.hpp>

namespace nt2 { namespace tag
{
  struct irrelevant
  {
    typedef irrelevant tag;
    BOOST_STATIC_CONSTANT(boost::uint32_t rank, = 1);
  };
} }

#endif
