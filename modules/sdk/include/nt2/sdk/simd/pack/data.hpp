/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PACK_DATA_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_DATA_HPP_INCLUDED

#include <nt2/sdk/simd/native.hpp>
#include <nt2/sdk/dsl/compute.hpp>
#include <nt2/sdk/meta/fusion.hpp>
#include <nt2/sdk/simd/meta/vector_of.hpp>

namespace nt2 { namespace simd
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
    typedef typename meta::hierarchy_of<parent>::type nt2_hierarchy_tag;

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
      evaluate(xpr,typename meta::is_native<parent>::type());
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

    template<class X>
    void evaluate ( X const& xpr, boost::mpl::true_ const& )
    {
      meta::as_<parent> target;
      mData = meta::compile < meta::compute<boost::mpl::_1,boost::mpl::_2>
                            , tag::cpu_
                            >()(xpr,target);
    }

    ////////////////////////////////////////////////////////////////////////////
    // false_ => array
    ////////////////////////////////////////////////////////////////////////////
    void fill(Type const& a0, boost::mpl::false_ const&)
    {
      mData.fill(a0);
    }

    template<class X>
    void evaluate ( X const& xpr, boost::mpl::false_ const& )
    {
      meta::as_<parent> target;
      for(std::size_t i=0;i<Cardinal::value;++i)
        mData[i] = meta::compile< meta::compute<boost::mpl::_1,boost::mpl::_2>
                                , tag::cpu_
                                >()(xpr,target,i);
    }
  };
} }

#endif
