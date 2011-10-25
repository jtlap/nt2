//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BOOLEAN_LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BOOLEAN_LOGICAL_HPP_INCLUDED

#include <climits>
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
    // mask is a bits pattern that allow direct use of value bits as a bool
    // Special care is taken for floating points value as -0 is false and not
    // true as its bits want us to think.
    //==========================================================================    
    BOOST_STATIC_CONSTANT ( bits
                          , mask  = is_floating_point<T>::value
                                  ? bits(~(bits(1) << (sizeof(T)*CHAR_BIT-1)))
                                  : ~bits(0)
                          );

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
    BOOST_DISPATCH_FORCE_INLINE logical(bool const v) : value_(v)  {}
    
    //==========================================================================    
    /*!
     * Constructs a logical from a value of type \c T
     *
     * \param v Value to turn into a logical value
     **/
    //==========================================================================    
    BOOST_DISPATCH_FORCE_INLINE logical(T const v) 
                              : value_( (bitwise_cast<bits>(v) & mask) != 0) 
    {}

    BOOST_DISPATCH_FORCE_INLINE bool operator ==(logical<T> const a) const { return  value_ == a.value_; }
    BOOST_DISPATCH_FORCE_INLINE bool operator !=(logical<T> const a) const { return  value_ != a.value_; }
    //==========================================================================    
    /*!
     * Convert a logical value to a real boolean
     *
     * \return Value of type \c bool containing the state of the logical 
     **/
    //==========================================================================    
    BOOST_DISPATCH_FORCE_INLINE operator bool() const { return value_; }
    
    //==========================================================================    
    /*!
     * Convert a logical value to its underlying type.
     *
     * \return Value of type \c T containing the state of the logical 
     **/
    //==========================================================================    
    BOOST_DISPATCH_FORCE_INLINE operator T() const 
    { 
      return static_cast<T>(value_); 
    }

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
    return os << bool(v);
  }

} }

namespace boost { namespace simd { namespace ext
{
  //============================================================================
  // logical_ is the hierarchy of logical<T> and goes straight to fundamental
  //============================================================================
  template<class T> struct logical_ : fundamental_<T>
  {
    typedef fundamental_<T> parent;
  };
} } }

namespace boost { namespace dispatch { namespace meta
{
  using boost::simd::ext::logical_;
    
  //============================================================================
  // value_of< logical<T> > is value_of<T>
  //============================================================================
  template<class T> struct value_of< simd::logical<T> > : value_of<T> {};

  //============================================================================
  // model_of< logical<T> > is logical< model_of<T> >
  //============================================================================
  template<class T> struct model_of< simd::logical<T> >
  {
    struct type
    {
      template<class X> struct apply
      {
        typedef typename mpl::apply<typename model_of<T>::type,X>::type base;
        typedef simd::logical<base>                                     type;
      };
    };
  };

  template<class T, class Origin> 
  struct property_of< simd::logical<T>, Origin >
  {
    typedef simd::ext::logical_<Origin> type;
  };

  template<class T, class Origin>
  struct  hierarchy_of< simd::logical<T>, Origin>
  {
    typedef meta::scalar_< simd::ext::logical_<Origin> >  type;
  };
} } }

#include <boost/simd/toolbox/boolean/details/logical_simd.hpp>
#include <boost/simd/toolbox/boolean/as_logical.hpp>

#endif
