//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DIFF_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DIFF_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the diff function
**/

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief tag for diff functor
    **/
    struct diff_ : ext::elementwise_<diff_>
    {
      typedef  ext::elementwise_<diff_> parent;
    };
  }

  /*!
    @brief


    @param
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::diff_       , diff, 1)


  /*!
    @brief

    @param
    @param
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::diff_       , diff, 2)


  /*!
    @brief

    @param
    @param
    @param
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::diff_       , diff, 3)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct size_of<nt2::tag::diff_,Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of
                    ::child_c<Expr&,0>::value_type::extent_type result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee = boost::proto::child_c<0>(e).extent();
      std::size_t along = boost::proto::value(boost::proto::child_c<1>(e));
      if(sizee[along]) sizee[along]--;

      return sizee;
    }
  };

  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::diff_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
