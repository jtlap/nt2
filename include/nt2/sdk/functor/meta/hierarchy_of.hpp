/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_META_HIERARCHY_OF_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_META_HIERARCHY_OF_HPP_INCLUDED

#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <nt2/sdk/functor/meta/hierarchy.hpp>

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // implementation details for hierarchy_of
  //////////////////////////////////////////////////////////////////////////////
  template<class T,std::size_t Size, bool Signed> struct hierarchy_of;
} }

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // hierarchy_of computes the entry point of a given type inside the type
  // hierarchy lattice.
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct  hierarchy_of
        : boost::mpl::eval_if < boost::is_integral<T>
                              , details::hierarchy_of < T
                                                      , sizeof(T)*CHAR_BIT
                                                      , boost::is_signed<T>::value
                                                      >
                              , details::hierarchy_of<T,0,false>
                              >
  {};

  //////////////////////////////////////////////////////////////////////////////
  // Overload for non integral native types
  //////////////////////////////////////////////////////////////////////////////
  template<> struct hierarchy_of<bool>    { typedef bool_<bool>     type; };
  template<> struct hierarchy_of<float>   { typedef float_<float>   type; };
  template<> struct hierarchy_of<double>  { typedef double_<double> type; };
} }


namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // implementation details for hierarchy_of - overload for integral sized type
  //////////////////////////////////////////////////////////////////////////////
  template<class T,std::size_t Size, bool Signed>
  struct hierarchy_of
  {
    typedef meta::unknown_<T> type;
  };

  template<class T> struct hierarchy_of<T,8,true>   { typedef meta::int8_<T>    type; };
  template<class T> struct hierarchy_of<T,8,false>  { typedef meta::uint8_<T>   type; };
  template<class T> struct hierarchy_of<T,16,true>  { typedef meta::int16_<T>   type; };
  template<class T> struct hierarchy_of<T,16,false> { typedef meta::uint16_<T>  type; };
  template<class T> struct hierarchy_of<T,32,true>  { typedef meta::int32_<T>   type; };
  template<class T> struct hierarchy_of<T,32,false> { typedef meta::uint32_<T>  type; };
  template<class T> struct hierarchy_of<T,64,true>  { typedef meta::int64_<T>   type; };
  template<class T> struct hierarchy_of<T,64,false> { typedef meta::uint64_<T>  type; };
} }

////////////////////////////////////////////////////////////////////////////////
// User level macro to define a new hierarchy element taking advantage of the
// type hierarchy lattice system.
////////////////////////////////////////////////////////////////////////////////
#define NT2_REGISTER_HIERARCHY(Name)                                \
namespace nt2                                                       \
{                                                                   \
  namespace tag { struct Name {}; }                                 \
  namespace meta                                                    \
  {                                                                 \
    template<class T> struct Name : Name< typename T::parent >      \
    {                                                               \
      typedef Name< typename T::parent > parent;                    \
      typedef tag::Name type(typename T::type);                     \
    };                                                              \
                                                                    \
    template<class T> struct Name< unknown_<T> > : unknown_<T> {};  \
  }                                                                 \
}                                                                   \
/**/

#endif
