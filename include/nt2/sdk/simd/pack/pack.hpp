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

/*
    //////////////////////////////////////////////////////////////////////////
    // vec<T,C> can be splatted using a single scalar
    //////////////////////////////////////////////////////////////////////////
    template<class A0>
    vec( A0 const& a0
       , typename boost::enable_if<boost::is_arithmetic<A0> >::type* x = 0
       )
    {
      ignore_unused_param(x);
      bp::value(*this).fill(a0);
    }

    //////////////////////////////////////////////////////////////////////////
    // vec<T,C> behaves like its underlying type
    //////////////////////////////////////////////////////////////////////////
    vec(inner_type v) { bp::value(*this).reset(v); }

          operator  inner_type()  const { return vec::value(); }

    vec&  operator=(inner_type v)
    {
      bp::value(*this).reset(v);
      return *this;
    }

    //////////////////////////////////////////////////////////////////////////
    // SIMD expression evaluates as vec<T,C>
    //////////////////////////////////////////////////////////////////////////
    template<class X>
    vec(expr<X,info_type> const& v ) { bp::value(*this).eval(v); }

    template<class X,class I> vec& operator=(expr<X,I> const& v )
    {
      bp::value(*this).eval(v);
      return *this;
    }
*/
    //////////////////////////////////////////////////////////////////////////
    // access to the scalar components of the vector type
    //////////////////////////////////////////////////////////////////////////
    const_reference  operator[](int i) const
    {
      return boost::proto::value(*this)[i];
    }
  };
} }

#endif
