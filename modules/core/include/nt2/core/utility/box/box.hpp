//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_BOX_BOX_HPP_INCLUDED
#define NT2_CORE_UTILITY_BOX_BOX_HPP_INCLUDED

#include <boost/proto/traits.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/expression.hpp>

namespace nt2
{
  namespace tag { struct box_ {}; }

  //============================================================================
  // box is a terminal taking care of wrapping a box into something usable by a
  // nt2 AST.
  //============================================================================
  template<class T>
  struct box  :
            nt2::container::
            expression< typename boost::proto::nullary_expr<tag::box_,T>::type
                      , T
                      >
  {
    typedef T value_type;

    box() {}
    box( box const& b)  { boost::proto::value(*this) = boost::proto::value(b); }
    box( T const& b)    { boost::proto::value(*this) = b; }

    box& operator=( box const& b)
    {
      boost::proto::value(*this) = boost::proto::value(b);
      return *this;
    }

    box& operator=( T const& b)
    {
      boost::proto::value(*this) = b;
      return *this;
    }

    T const& value() const { return boost::proto::value(*this); }
  };
}

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // table use container<tag::table_> to do its biddings
  //============================================================================
  template<class T> struct semantic_of< nt2::box<T> > { typedef T type; };
} } }

#endif
