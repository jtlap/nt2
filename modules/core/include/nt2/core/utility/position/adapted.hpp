//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_POSITION_ADAPTED_HPP_INCLUDED
#define NT2_CORE_UTILITY_POSITION_ADAPTED_HPP_INCLUDED

#include <nt2/sdk/meta/is_container.hpp>
#include <nt2/sdk/meta/container_of.hpp>
#include <nt2/sdk/meta/dimensions_of.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>

#include <nt2/core/utility/position/category.hpp>

//==============================================================================
// Forward declaration
//==============================================================================
namespace nt2 {
  template<typename Seq, typename S, typename B, typename SO, typename A> struct position;
}

namespace nt2 { namespace meta
{
  //============================================================================
  // Register container as a proper container
  //============================================================================
  template<typename Seq, typename S, typename B, typename SO, typename A>
  struct is_container< nt2::position<Seq,S,B,SO,A> > : boost::mpl::true_ {};
} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // hierarchy_of specialization
  //============================================================================
  template<typename Seq, typename S, typename B, typename SO, typename A, typename Origin>
  struct hierarchy_of< nt2::position<Seq,S,B,SO,A>, Origin >
  {
    typedef position_< Seq, A, Origin > type;
  };

  //============================================================================
  // value_of specialization
  //============================================================================
  template<typename Seq, typename S, typename B, typename SO, typename A>
  struct value_of< nt2::position<Seq,S,B,SO,A> >
  {
    typedef std::ptrdiff_t type;
  };

  //============================================================================
  // model_of specialization
  //============================================================================
  template<typename Seq, typename S, typename B, typename SO, typename A>
  struct model_of< nt2::position<Seq,S,B,SO,A> >
  {
    struct type
    {
      struct apply { typedef nt2::position<Seq,S,B,SO,A> type; };
    };
  };
} } }

#endif
