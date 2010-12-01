/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_META_HIERARCHY_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_META_HIERARCHY_HPP_INCLUDED

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <nt2/sdk/details/preprocessor.hpp>
#include <nt2/sdk/functor/details/hierarchy.hpp>

////////////////////////////////////////////////////////////////////////////////
// Local macros handling boilerplate code for regular and template hierarchies
////////////////////////////////////////////////////////////////////////////////
#define NT2_HIERARCHY_CLASS(Name, Parent) \
template<class T> struct Name : Parent    \
{                                         \
  typedef Parent    parent;               \
  typedef tag::Name type;                 \
}                                         \
/**/

#define NT2_HIERARCHY_CLASS_TPL(Name, Parent)               \
template<class T> struct Name : NT2_PP_STRIP(Parent)::type  \
{                                                           \
  typedef typename NT2_PP_STRIP(Parent)::type    parent;    \
  typedef tag::Name type;                                   \
}                                                           \
/**/

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Types hierarchy defines a partially order lattice of type familly
  // which helps categorizing a given type into all its potential enclosing type
  // sets. Hierarchies are template so they can use their root type to
  // selct at each lattice node which ancestor to use.
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // The unknown_ hierarchy is the upper bound in our hierarchy lattice.
  // When a dispatch resovles on unknown_, it means so suitqble overload have
  // been found.
  //////////////////////////////////////////////////////////////////////////////
  template<class T> struct unknown_ { typedef tag::unknown_ type; };

  //////////////////////////////////////////////////////////////////////////////
  // Upper level hierarchies:
  // fundamental_ gathers all native types
  // arithmetic_ gathers all native type except bool
  // integer_ gathers all native integer types
  //////////////////////////////////////////////////////////////////////////////
  NT2_HIERARCHY_CLASS(fundamental_, unknown_<T>     );
  NT2_HIERARCHY_CLASS(arithmetic_ , fundamental_<T> );
  NT2_HIERARCHY_CLASS(integer_    , arithmetic_<T>  );


  NT2_HIERARCHY_CLASS_TPL (signed_, (boost::mpl::if_< boost::is_integral<T>
                                                    , integer_<T>
                                                    , arithmetic_<T>
                                                    >
                                    )
                          );

  NT2_HIERARCHY_CLASS(unsigned_   , integer_<T>   );

  //////////////////////////////////////////////////////////////////////////////
  // Floating point types hierarchy
  //////////////////////////////////////////////////////////////////////////////
  NT2_HIERARCHY_CLASS(real_       , signed_<T>    );

  //////////////////////////////////////////////////////////////////////////////
  // Sign based hierarchy - gather integral types of a given signedness
  //////////////////////////////////////////////////////////////////////////////
  NT2_HIERARCHY_CLASS(int_        , signed_<T>    );
  NT2_HIERARCHY_CLASS(uint_       , unsigned_<T>  );

  //////////////////////////////////////////////////////////////////////////////
  // Sizeof based hierarchy - gather type which sizeof is equal to a given value
  //////////////////////////////////////////////////////////////////////////////
  NT2_HIERARCHY_CLASS_TPL (type8_, (boost::mpl::if_< boost::is_signed<T>
                                                    , int_<T>
                                                    , uint_<T>
                                                    >
                                    )
                          );

  NT2_HIERARCHY_CLASS_TPL (type16_, (boost::mpl::if_< boost::is_signed<T>
                                                    , int_<T>
                                                    , uint_<T>
                                                    >
                                    )
                          );

  NT2_HIERARCHY_CLASS_TPL (type32_
                          , (boost::mpl::if_<boost::is_floating_point<T>
                                            , real_<T>
                                            , typename
                                              boost::mpl::if_ < boost::is_signed<T>
                                                              , int_<T>
                                                              , uint_<T>
                                                              >::type
                                            >
                                    )
                          );

  NT2_HIERARCHY_CLASS_TPL (type64_
                          , (boost::mpl::if_<boost::is_floating_point<T>
                                            , real_<T>
                                            , typename
                                              boost::mpl::if_ < boost::is_signed<T>
                                                              , int_<T>
                                                              , uint_<T>
                                                              >::type
                                            >
                                    )
                          );

  //////////////////////////////////////////////////////////////////////////////
  // Sizeof based hierarchy of integers
  //////////////////////////////////////////////////////////////////////////////
  NT2_HIERARCHY_CLASS(ints8_        , type8_<T>       );
  NT2_HIERARCHY_CLASS(ints16_       , type16_<T>      );
  NT2_HIERARCHY_CLASS(ints32_       , type32_<T>      );
  NT2_HIERARCHY_CLASS(ints64_       , type64_<T>      );

  //////////////////////////////////////////////////////////////////////////////
  // Sizeof based hierarchy of signed integers
  //////////////////////////////////////////////////////////////////////////////
  NT2_HIERARCHY_CLASS(int8_         , ints8_<T>       );
  NT2_HIERARCHY_CLASS(int16_        , ints16_<T>      );
  NT2_HIERARCHY_CLASS(int32_        , ints32_<T>      );
  NT2_HIERARCHY_CLASS(int64_        , ints64_<T>      );

  //////////////////////////////////////////////////////////////////////////////
  // Sizeof based hierarchy of unsigned integers
  //////////////////////////////////////////////////////////////////////////////
  NT2_HIERARCHY_CLASS(uint8_        , ints8_<T>       );
  NT2_HIERARCHY_CLASS(uint16_       , ints16_<T>      );
  NT2_HIERARCHY_CLASS(uint32_       , ints32_<T>      );
  NT2_HIERARCHY_CLASS(uint64_       , ints64_<T>      );

  //////////////////////////////////////////////////////////////////////////////
  // Native real types hierarchy
  //////////////////////////////////////////////////////////////////////////////
  NT2_HIERARCHY_CLASS(double_       , type64_<T>      );
  NT2_HIERARCHY_CLASS(float_        , type32_<T>      );

  //////////////////////////////////////////////////////////////////////////////
  // Boolean type hierarchy
  //////////////////////////////////////////////////////////////////////////////
  NT2_HIERARCHY_CLASS(bool_         , fundamental_<T> );
} }

#undef NT2_HIERARCHY_CLASS
#undef NT2_HIERARCHY_CLASS_TPL

#endif
