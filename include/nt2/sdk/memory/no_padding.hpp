/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_NO_PADDING_HPP_INCLUDED
#define NT2_SDK_MEMORY_NO_PADDING_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Padding strategies for memory allocation
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/pair.hpp>
#include <nt2/sdk/memory/padding.hpp>

////////////////////////////////////////////////////////////////////////////////
// Various pre-made padding strategies
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace memory
{
  //////////////////////////////////////////////////////////////////////////////
  // No padding: all data are allocated as specified
  //////////////////////////////////////////////////////////////////////////////
  struct no_padding
  {
    typedef meta::padding_<no_padding>                  nt2_hierarchy_tag;
    //typedef boost::mpl::pair<tag::padding_,no_padding>  nt2_settings_type;
  };
} }

#include <nt2/sdk/memory/details/no_padding.hpp>

#endif
