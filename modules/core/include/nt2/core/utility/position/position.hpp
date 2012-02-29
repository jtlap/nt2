//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_POSITION_POSITION_HPP_INCLUDED
#define NT2_CORE_UTILITY_POSITION_POSITION_HPP_INCLUDED

#include <nt2/sdk/meta/hierarchy_of.hpp>

/**
 * \file
 * \brief Define nt2::position
**/

namespace nt2
{
  namespace tag { struct position_ {}; }
  
  template<typename Seq, typename B, typename SO, typename A>
  struct position
  {
    typedef tag::position_ fusion_tag;
    typedef typename boost::mpl::if_<boost::fusion::traits::is_view<Seq>, Seq const, Seq const&>::type sequence_type;
    
    position (Seq const& seq) : seq_(seq) {}
    
    sequence_type seq_;
  };
}

#include <nt2/core/utility/position/fusion.hpp>

#endif
