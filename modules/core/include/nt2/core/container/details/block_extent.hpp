/***********************
 * ********************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_CONTAINER_DETAILS_BLOCK_NRC_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DETAILS_BLOCK_NRC_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Hoisted class for base index related block member functions
////////////////////////////////////////////////////////////////////////////////
#include <boost/typeof/typeof.hpp>
#include <nt2/core/container/details/block_size.hpp>
#include <nt2/core/container/details/block_base.hpp>

namespace nt2 { namespace details
{
  template<class Bases,class Sizes>
  struct block_extent : block_base<Bases>, block_size<Sizes>
  {
    ////////////////////////////////////////////////////////////////////////////
    // Check that Bases adn Sizes have correct size
    ////////////////////////////////////////////////////////////////////////////
    struct type_
    {
      typename boost::fusion::result_of::value_at_c<Bases const,0>::type& base_;
      typename boost::fusion::result_of::value_at_c<Sizes const,0>::type& size_;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL( nested, base_ + size_ -1 )
  
      typedef typename nested::type type;
    };
    
    typedef typename type_::type difference_type;
    
   ////////////////////////////////////////////////////////////////////////////
   // Check that Bases adn Sizes have correct size
   ////////////////////////////////////////////////////////////////////////////

   block_extent ( Bases const& b, Sizes const& s)
                : block_size<Sizes>(s)
                , block_base<Bases>(b)
    {}

    ////////////////////////////////////////////////////////////////////////////
    // Return the ending index on the Nth dimension
    ////////////////////////////////////////////////////////////////////////////
    template<std::size_t N>
    typename boost::enable_if_c < (N<=boost::mpl::size<Sizes>::value)
                                , difference_type
                                >::type
    upper() const
    {
      return    block_size<Sizes>::template  size<N>()
              + block_base<Bases>::template lower<N>() - 1;
    }

    template<std::size_t N>
    typename boost::disable_if_c< (N<=boost::mpl::size<Sizes>::value)
                                , difference_type
                                >::type
    upper() const
    {
      return 1;
    }
  };
} }

#endif
