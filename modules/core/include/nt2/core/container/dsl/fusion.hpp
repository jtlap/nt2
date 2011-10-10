//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_FUSION_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_FUSION_HPP_INCLUDED

#include <nt2/core/functions/size.hpp>
#include <nt2/core/container/dsl/forward.hpp>

namespace nt2 { namespace tag
{
  //============================================================================
  /*! Identify expression as valid fusion sequence                            */
  //============================================================================
  struct container_ {};
} }

//==============================================================================
//Implement shared generic Fusion sequence conformance for container expression
//==============================================================================
namespace boost { namespace fusion { namespace extension
{
  //============================================================================
  // Register container expression as fusion random access sequence
  //============================================================================
  template<> struct is_sequence_impl<nt2::tag::container_>
  {
    template<typename T> struct apply : mpl::true_ {};
  };

  template<> struct is_view_impl<nt2::tag::container_>
  {
    template<typename Seq> struct apply : mpl::false_ {};
  };

  template<> struct category_of_impl<nt2::tag::container_>
  {
    typedef random_access_traversal_tag type;
  };

  //============================================================================
  // Size of extent_ expression is given by its Dimensions
  //============================================================================
  template<> struct size_impl<nt2::tag::container_>
  {
    /*
    template<typename Sequence>
    struct apply : mpl::int_<Sequence::static_dimensions> 
    {};
    */
  };
} } }

#endif
