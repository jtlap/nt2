//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_BOX_HPP_INCLUDED
#define NT2_CORE_UTILITY_BOX_HPP_INCLUDED

/*!
  @file
  @brief Definition of the box nullary expression
**/

#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/expression.hpp>
#include <nt2/dsl/functions/terminal.hpp>
#include <boost/proto/traits.hpp>

namespace nt2
{
  /*!
    @brief Custom boxed value nullary expression

    box is a nullary expression taking care of wrapping helper types or values
    into a node compatible with nt2::expression.

    @tparam T Type of the value to store which models DefaultConstructible and
    Assignable.

    @par Rationale
    Why use this kitchen sink instead of adding the proper terminal cases to the
    NT2 grammar ? Well, in some case of expression building, one may want to
    store various values that are not easily computable from the Abstract Syntax
    Tree alone. In many case, these values may have a type which is complex to
    assess within a proto grammar rule (Callable Objects for example) or may
    conflict with the general semantic of the expression. Another issue is the
    lifetime of said values that are usually created in the expression building
    function as temporaries, making taking reference to them dangerous.

    box solves these problem by being the only one to be registered in the NT2
    proto grammar. box take a copy of the value, making it safe to store in the
    Abstract Syntax Tree and provide a simple interface to grab the value or the
    type of value back.

    @par When to use @c box ?
    box should be used for passing informations that can not be infered from the
    Abstract Syntax Tree alone or without requiring costly recomputation but are
    required for expression evaluation. This include any Callable Object that may
    parametrize the expression, any value that should be precomputed to speed
    expression evaluation. Unless if it fit into the former cases, one should not
    use box to store expression size as this is the job of ext::size_of.
  **/
  template<class T, class Dummy>
  struct box  :
            nt2::container::
            expression< typename boost::proto::nullary_expr<tag::box_,T>::type
                      , T
                      >
  {
    /// Type of the value stored in current box
    typedef T value_type;

    /*!
      @brief Default constructor for box
    */
    box() {}

    /*!
      @brief Value constructor for box

      Construct a box from a value of type @c T
    */
    box(T const& b) { boost::proto::value(*this) = b; }

    /*!
      @brief Value assignment operator for box

      Assign a value of type @c T to a box

      @param b Value to store in the current box
      @return The modified box
    */
    box& operator=(T const& b)
    {
      boost::proto::value(*this) = b;
      return *this;
    }

    /*!
      @brief Value accessor

      Provide an immutable access to the stored value inside current box.

      @return a reference to the constant value stored in current box.
    */
    T const& value() const { return boost::proto::value(*this); }
  };

  /*!
    @brief Build a box out of a value

    Turn any value @c v of type @c T into a @c box<T> containing a copy of @c v

    @param v Value to put in a box

    @return a @c box<T> instance containing a copy of @c v
   **/
  template<class T> BOOST_FORCEINLINE box<T> boxify(T const& v)
  {
    box<T> that(v);
    return that;
  }
}

namespace boost { namespace dispatch { namespace meta
{
  /// INTERNAL ONLY
  /// Semantic of box<T> is T
  template<class T> struct semantic_of< nt2::box<T> > { typedef T type; };
} } }

#endif
