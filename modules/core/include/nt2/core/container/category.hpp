//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_CATEGORY_HPP_INCLUDED
#define NT2_CORE_CONTAINER_CATEGORY_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <boost/dispatch/meta/property_of.hpp>

namespace boost { namespace dispatch { namespace meta
{
  // TODO: Move to table/ later
  template<class T, class Size>
  struct table_ : table_< typename T::parent, Size >
  {
    typedef table_<typename T::parent, Size> parent;
  };
  
  template<class T, class Size>
  struct  table_< unspecified_<T>, Size > 
        : generic_< typename property_of<T>::type >
  {
    typedef generic_< typename property_of<T>::type > parent;
  };    
} } }

namespace nt2 { namespace ext
{
  using boost::dispatch::meta::table_;
} }

//==============================================================================
// Proto Work around - Prevent operator()() to whine eagerly
//==============================================================================
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( boost::proto::tag::function, tag::cpu_
                            , (A0)(S0)
                            , ((table_< unspecified_<A0>, S0 >))
                            )
  {
    typedef A0& result_type;
    result_type operator()(A0& a0) const { return a0; }
  };
} }

#endif
