/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_SETTINGS_ID_HPP_INCLUDED
#define NT2_CORE_SETTINGS_ID_HPP_INCLUDED

#include <boost/mpl/string.hpp>
#include <nt2/core/settings/meta/option.hpp>

////////////////////////////////////////////////////////////////////////////////
// Defines ID options
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace options
{
  struct id_ { typedef void nt2_is_option_type; };
} }

////////////////////////////////////////////////////////////////////////////////
// id_<'foo'> tags containers with a 32bits ID, either numerical or by using
// the multichar string extension.
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { template<int ID> struct id_ {}; }

////////////////////////////////////////////////////////////////////////////////
// Register id_ has a valid options::id_ type
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  template<int ID, class Default>
  struct option<id_<ID>, options::id_, Default, void>
  {
    typedef boost::mpl::string<ID> type;
  };
} }

#endif
