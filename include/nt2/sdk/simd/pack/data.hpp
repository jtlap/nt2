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
#include <nt2/sdk/dsl/proto/visitor.hpp>
#include <nt2/sdk/simd/meta/vector_of.hpp>

namespace nt2 { namespace simd
{
  ////////////////////////////////////////////////////////////////////////////
  // data is a tag-dispatched SIMD entity that selects between a native
  // or emulated implementation depedning on Type and Cardinal
  ////////////////////////////////////////////////////////////////////////////
  template<class Type,class Cardinal>
  struct  data
        : meta::vector_of<Type,Cardinal::value>::type
  {
    typedef typename meta::vector_of<Type,Cardinal::value>::type  parent;

    ////////////////////////////////////////////////////////////////////////////
    // Constructors from various sources
    ////////////////////////////////////////////////////////////////////////////
    data() : parent() {}

    ////////////////////////////////////////////////////////////////////////////
    // Fill current data by evaluating soem expression
    ////////////////////////////////////////////////////////////////////////////
    template<class X> void evaluate(expression<X,Type,Cardinal> const& xpr )
    {
      evaluate(xpr,typename meta::is_native<parent>::type());
    }

    ////////////////////////////////////////////////////////////////////////////
    // Return internal value
    ////////////////////////////////////////////////////////////////////////////
    parent const& value() const
    {
      return static_cast<parent const&>(*this);
    }

    private:
    ////////////////////////////////////////////////////////////////////////////
    // Inner evalaution dispatched on native category
    // true_  => native
    // false_ => array
    ////////////////////////////////////////////////////////////////////////////
    template<class X>
    void evaluate ( expression<X,Type,Cardinal> const& xpr
                  , boost::mpl::true_ const&
                  )
    {
      // On simd native, use the native evaluator transform
        static_cast<parent&>(*this) = Four<parent>();
    }

    template<class X>
    void evaluate ( expression<X,Type,Cardinal> const& xpr
                  , boost::mpl::false_ const&
                  )
    {
      boost::proto::visitor < dsl::compute_transform
                            , dsl::grammar
                            >
      evaluator;

      // On array, iterate over values and evaluates the expressions
      // for every index of the array
      for(std::size_t i=0;i<Cardinal::value;++i)
        (*this)[i] = evaluator(xpr,i,i);
    }
  };
} }

#endif
