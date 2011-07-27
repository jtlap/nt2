/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_PACK_DATA_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_DATA_HPP_INCLUDED

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/meta/fusion.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <boost/simd/sdk/simd/meta/is_native.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/sdk/simd/pack/evaluation.hpp>

namespace boost { namespace simd
{
  ////////////////////////////////////////////////////////////////////////////
  // data is a tag-dispatched SIMD entity that selects between a native
  // or emulated implementation depending on Type and Cardinal
  ////////////////////////////////////////////////////////////////////////////
  template<class Type,class Cardinal>
  struct  data
  {
    typedef typename meta::vector_of<Type,Cardinal::value>::type  parent;

    ////////////////////////////////////////////////////////////////////////////
    // Hierarchizable interface
    ////////////////////////////////////////////////////////////////////////////
    typedef typename dispatch::meta::hierarchy_of<parent,data>::type nt2_hierarchy_tag;

    ////////////////////////////////////////////////////////////////////////////
    // Range interface
    ////////////////////////////////////////////////////////////////////////////
    typedef typename parent::value_type               value_type;
    typedef typename parent::reference                reference;
    typedef typename parent::const_reference          const_reference;
    typedef typename parent::size_type                size_type;
    typedef typename parent::iterator                 iterator;
    typedef typename parent::const_iterator           const_iterator;

    ////////////////////////////////////////////////////////////////////////////
    // Constructors from various sources
    ////////////////////////////////////////////////////////////////////////////
    data()                  : mData()   {}
    data(parent const& a0)  : mData(a0) {}

    data& operator=(data const& a0)
    {
      mData = a0.mData;
      return *this;
    }

    data& operator=(parent const& a0)
    {
      mData = a0;
      return *this;
    }

    void fill(Type const& a0)
    {
      fill(a0,typename meta::is_native<parent>::type());
    }

    ////////////////////////////////////////////////////////////////////////////
    // Array interface
    ////////////////////////////////////////////////////////////////////////////
    reference       operator[](int i)       { return mData[i]; }
    const_reference operator[](int i) const { return mData[i]; }

    ////////////////////////////////////////////////////////////////////////////
    // Range interface
    ////////////////////////////////////////////////////////////////////////////
    const_iterator  begin()  const  { return mData.begin(); }
    const_iterator  end()    const  { return mData.end();   }
    iterator        begin()         { return mData.begin(); }
    iterator        end()           { return mData.end();   }

    ////////////////////////////////////////////////////////////////////////////
    // Fill current data by evaluating some expression
    ////////////////////////////////////////////////////////////////////////////
    template<class X> void evaluate(X const& xpr )
    {
      boost::simd::evaluate(mData,xpr);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Return internal value
    ////////////////////////////////////////////////////////////////////////////
    parent const& value() const
    {
      return mData;
    }

    private:
    parent mData;

    private:
    ////////////////////////////////////////////////////////////////////////////
    // Inner evaluation dispatched on native category
    // true_  => native
    ////////////////////////////////////////////////////////////////////////////
    void fill(Type const& a0, boost::mpl::true_ const&)
    {
      mData = splat<parent>(a0);
    }

    ////////////////////////////////////////////////////////////////////////////
    // false_ => array
    ////////////////////////////////////////////////////////////////////////////
    void fill(Type const& a0, boost::mpl::false_ const&)
    {
      mData.fill(a0);
    }
  };
} }

namespace boost { namespace dispatch { namespace meta
{
  template<class Type,class Cardinal, class Origin>
  struct  property_of< boost::simd::data<Type,Cardinal>, Origin >
        : property_of< Type, boost::simd::data<Type,Cardinal> > {};
} } }
#endif
