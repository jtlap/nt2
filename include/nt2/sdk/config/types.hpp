/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONFIG_TYPES_HPP_INCLUDED
#define NT2_SDK_CONFIG_TYPES_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Types injection into nt2
// Injects or define some absic types in NT2 namespace for consistency sake.
//* TODO : Documentation: http://nt2.lri.fr/doc/build/html/sdk/config/types.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/config.hpp>
#include <boost/cstdint.hpp>

namespace nt2
{
  using ::boost::uint8_t;
  using ::boost::uint16_t;
  using ::boost::uint32_t;
  using ::boost::uint64_t;
  using ::boost::int8_t;
  using ::boost::int16_t;
  using ::boost::int32_t;
  using ::boost::int64_t;
}

#endif
