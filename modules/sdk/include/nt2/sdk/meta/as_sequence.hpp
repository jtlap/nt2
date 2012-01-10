//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_AS_SEQUENCE_HPP_INCLUDED 
#define NT2_SDK_META_AS_SEQUENCE_HPP_INCLUDED 

//==============================================================================
/**!
 * @file
 * Defines the nt2::as_sequence function
 **/
//==============================================================================
#include <boost/utility/enable_if.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/fusion/include/single_view.hpp>
#include <boost/fusion/include/is_sequence.hpp>

namespace nt2 { namespace details
{
  template< class Type
          , bool isSequence = boost::fusion::traits::is_sequence<Type>::value
          >
  struct as_sequence
  {
    typedef Type const& type;
    static BOOST_FORCEINLINE type call(Type const& s) { return s; }
  };

  template< class Type>
  struct as_sequence<Type,false>
  {
    typedef boost::fusion::single_view<Type> type;
    static BOOST_FORCEINLINE type call(Type const& s) { return type(s); }
  };    
} }

namespace nt2 { namespace meta
{
  template<class Type>
  BOOST_FORCEINLINE typename details::as_sequence<Type>::type
  as_sequence( Type const& s )
  {
    return details::as_sequence<Type>::call(s);
  }
} } 

#endif
