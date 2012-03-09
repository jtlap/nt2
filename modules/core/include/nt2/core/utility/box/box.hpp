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
  //============================================================================
  // box_ is an elementwise operation
  //============================================================================
  namespace tag
  {
    struct box_ : ext::elementwise_<box_>
    {
      typedef ext::elementwise_<box_> parent;
    };
  }

  //============================================================================
  // box is a nullary expression taking care of wrapping helper types into a
  // node assimilable by nt2 ASTs.
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

  template<class T> BOOST_FORCEINLINE box<T> boxify(T const& v)
  {
    box<T> that(v);
    return that;
  }
}

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // Semantic of box<T> is T
  //============================================================================
  template<class T> struct semantic_of< nt2::box<T> > { typedef T type; };
} } }

#endif
