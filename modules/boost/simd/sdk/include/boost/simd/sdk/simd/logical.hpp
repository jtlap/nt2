//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_LOGICAL_HPP_INCLUDED

#include <climits>
#include <boost/assert.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/simd/sdk/details/bitwise_cast.hpp>
 
namespace boost { namespace simd
{
  //============================================================================
  /*!
   * logical<T> is a thin wrapper used to optimize bool-to-type conversion and
   * provide a scalar equivalent of typed boolean SIMD types. logical<T> is also
   * set up to work as a vectorizable type, beign mapped to proper register type
   * for any given extension
   */
  //============================================================================
  template<typename T> struct logical
  {
    typedef typename dispatch::meta::as_integer<T>::type bits;

    //==========================================================================    
    /*!
     * Default logical constructor
     **/
    //==========================================================================        
    BOOST_DISPATCH_FORCE_INLINE logical() {}
    
    //==========================================================================    
    /*!
     * Constructs a logical from a boolean value
     *
     * \param v Boolean value to convert to logical
     **/
    //==========================================================================    
    BOOST_DISPATCH_FORCE_INLINE 
    logical(bool const v) : value_(v)  {}
    
    //==========================================================================    
    /*!
     * Constructs a logical from a value of type \c T
     *
     * \param v Value to turn into a logical value. \c v must be 0 or 1 or
     * the constructor will fail. 
     **/
    //==========================================================================    
    BOOST_DISPATCH_FORCE_INLINE     
    explicit logical( T const& v) : value_(v) 
    {
      BOOST_ASSERT_MSG(((v==0) || (v==1)), "Invalid boolean value");
    }

    BOOST_DISPATCH_FORCE_INLINE 
    bool operator ==(logical<T> const a) const { return  value_ == a.value_; }
    
    BOOST_DISPATCH_FORCE_INLINE 
    bool operator !=(logical<T> const a) const { return  value_ != a.value_; }
    
    BOOST_DISPATCH_FORCE_INLINE bool operator ~() const { return ~value_; }
    BOOST_DISPATCH_FORCE_INLINE bool operator !() const { return ~value_; }

    //==========================================================================    
    /*!
     * Convert a logical value to a real boolean
     *
     * \return Value of type \c bool containing the state of the logical 
     **/
    //==========================================================================    
    BOOST_DISPATCH_FORCE_INLINE operator bool() const { return value_; }

    private:
    bool  value_;
  };

  ////////////////////////////////////////////////////////////////////////////
  // Stream insertion for logical<T>
  ////////////////////////////////////////////////////////////////////////////
  template<class T>
  BOOST_DISPATCH_FORCE_INLINE
  std::ostream& operator<<(std::ostream& os, logical<T> const& v )
  {
    return os << std::boolalpha << bool(v) << std::noboolalpha;
  }
} }

namespace boost { namespace simd { namespace ext
{
  //============================================================================
  // logical_ is the hierarchy of logical<T> and goes straight to fundamental
  //============================================================================
  template<class T> struct logical_ : dispatch::meta::fundamental_<T>
  {
    typedef dispatch::meta::fundamental_<T> parent;
  };
} } }

//==============================================================================
  // Rgister logical<T> to variosu dispatch system
//============================================================================== 
namespace boost { namespace dispatch { namespace meta
{
  using boost::simd::ext::logical_;

  template<class T, class Origin>
  struct  hierarchy_of< simd::logical<T>, Origin>
  {
    typedef meta::scalar_< simd::ext::logical_<Origin> >  type;
  };
 
  template<class T, class Origin>
  struct property_of< simd::logical<T>, Origin>
  {
    typedef simd::ext::logical_<Origin> type;
  };
} } }

#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/simd/sdk/simd/details/logical.hpp>

#endif
