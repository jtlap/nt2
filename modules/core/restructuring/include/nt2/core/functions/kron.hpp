//==============================================================================
//         Copyright 2015  J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_KRON_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_KRON_HPP_INCLUDED

// Copyright (c) 2009, Bruno Luong
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:

//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in
//       the documentation and/or other materials provided with the distribution

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/include/functions/ismatrix.hpp>
#include <boost/assert.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief kron generic tag

     Represents the kron function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct  kron_ : ext::unspecified_<kron_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<kron_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_kron_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }

  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::kron_, Site> dispatching_kron_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::kron_, Site>();
   }
   template<class... Args>
   struct impl_kron_;
  }
  /*!
    krnecker tensor product

    @par Semantic:


    @code
    auto r = kron(a0,a1);
    @endcode

    The result is a large matrix formed by taking all possible
    products between the elements of X and those of Y.


    @param a0

    @param a1

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::kron_, kron, 2)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::kron_,Domain,N,Expr>
  {
    typedef _2D result_type;

    BOOST_FORCEINLINE result_type operator ()(Expr& e) const
    {
      BOOST_ASSERT_MSG(ismatrix(boost::proto::child_c<0>(e))
                          , "kron first input is not matricial");
      BOOST_ASSERT_MSG(ismatrix(boost::proto::child_c<1>(e))
                          , "kron second input is not matricial");
      result_type sizee(boost::proto::child_c<0>(e).extent());
      sizee[0] *= boost::fusion::at_c<0>(boost::proto::child_c<1>(e).extent());
      sizee[1] *= boost::fusion::at_c<1>(boost::proto::child_c<1>(e).extent());

      return sizee;
    }
  };

  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::kron_,Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of
    ::child_c<Expr&,0>::value_type::value_type  type;
    typedef typename  boost::proto::result_of
    ::child_c<Expr&,1>::value_type::value_type  other_type;

    BOOST_MPL_ASSERT_MSG
    ( (boost::is_same<type,other_type>::value)
    , NT2_INCOMPATIBLE_TYPE_IN_KRON_EXPRESSION
    , (type,other_type)
    );
  };
} }

#endif
