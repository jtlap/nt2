/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_CONTAINER_DETAILS_BLOCK_BASE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DETAILS_BLOCK_BASE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Hoisted class for base index related block member functions
////////////////////////////////////////////////////////////////////////////////
#include <cstddef>
#include <boost/mpl/size.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/fusion/include/at.hpp>

namespace nt2 { namespace details
{
  template<class Bases> struct block_base
  {
    block_base(Bases const& bs) : mBase(bs) {}

    ////////////////////////////////////////////////////////////////////////////
    // Return the starting index on the Nth dimension
    ////////////////////////////////////////////////////////////////////////////
    template<std::size_t N>
    typename boost::enable_if_c < (N<=boost::mpl::size<Bases>::value)
                                , typename boost::fusion::result_of
                                                ::at_c<Bases const,N-1>::type
                                >::type
    lower() const
    {
      return boost::fusion::at_c<N-1>(mBase);
    }

    template<std::size_t N>
    typename boost::disable_if_c< (N<=boost::mpl::size<Bases>::value)
                                , int
                                >::type
    lower() const
    {
      return 1;
    }

    Bases mBase;
  };
} }

#endif
