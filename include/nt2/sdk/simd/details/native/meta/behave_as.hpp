/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_NATIVE_META_BEHAVE_AS_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_NATIVE_META_BEHAVE_AS_HPP_INCLUDED

#include <boost/mpl/apply.hpp>
#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/meta/behave_as.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2
{
  namespace details
  {
    ////////////////////////////////////////////////////////////////////////////
    // Overload for SIMD types
    ////////////////////////////////////////////////////////////////////////////
    template<class Lambda,class T, class C,class X>
    struct behave_as_impl<Lambda,T,tag::simd_(C,X) >
         : boost::mpl::apply1<Lambda,typename meta::scalar_of<T>::type>::type {};
  }
}

#endif
