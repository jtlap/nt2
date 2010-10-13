/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PACK_PACK_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_PACK_HPP_INCLUDED

namespace nt2 { namespace simd
{
  ////////////////////////////////////////////////////////////////////////////
  // pack, implemented in terms of simd::expr
  ////////////////////////////////////////////////////////////////////////////
  template<class Type,std::size_t Cardinal,class BP>
  struct  pack
        : expression_facade<Type,boost::mpl::size_t<Cardinal> >::type
  {
    typedef typename
    expression_facade<Type,boost::mpl::size_t<Cardinal> >::type parent;
    typedef Type                                                scalar_type;
    typedef Type&                                               reference;
    typedef Type                                                const_reference;

    //////////////////////////////////////////////////////////////////////////
    // Constructors
    //////////////////////////////////////////////////////////////////////////
    pack() : parent() {}
    explicit pack(Type const& a0)
    {
      boost::proto::value(*this).fill(a0);
    }

    ////////////////////////////////////////////////////////////////////////////
    // SIMD expression evaluates as pack
    ////////////////////////////////////////////////////////////////////////////
    template<class X>
    pack(expression<X,Type,boost::mpl::size_t<Cardinal> > const& xpr )
    {
      boost::proto::value(*this).evaluate(xpr);
    }

    template<class X> pack&
    operator=(expression<X,Type,boost::mpl::size_t<Cardinal> > const& xpr )
    {
      boost::proto::value(*this).evaluate(xpr);
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // access to the scalar components of the vector type
    ////////////////////////////////////////////////////////////////////////////
    const_reference  operator[](int i) const
    {
      return boost::proto::value(*this)[i];
    }
  };
} }

#endif
