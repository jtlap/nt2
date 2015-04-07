//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_CONTFRAC_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_CONTFRAC_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2 {
  namespace tag
  {
   /*!
     @brief contfrac generic tag

     Represents the contfrac function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct contfrac_ : ext::unspecified_<contfrac_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<contfrac_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY(
        dispatching_contfrac_( ext::adl_helper(), static_cast<Args&&>(args)... )
      )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::contfrac_, Site>
   dispatching_contfrac_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::contfrac_, Site>();
   }
   template<class... Args>
   struct impl_contfrac_;
  }
  /*!
    Computes the  evaluation of continuous fraction given by two tables of
    coefficient

    @par Semantic:

    For every tables a and b

    @code
    auto r = contfrac(a, b, {x});
    @endcode

    computes a1/(b1+x+a2/(b2+x+a3/(...an/(bn+x))))


    @code
    auto r = contfrac(a, b, x, lower_/upper_/both_);
    @endcode

    computes respectively

    a1/(b1+x+a2/(b2+x+a3/(...an/(bn+x))))

    (x+a1)/(b1+(x+a2)/(b2+(x+a3)/(...(x+an)/bn)))

    (a1+x)/(b1+x+(a2+x)/(b2+x+(a3+x)/(...(an+x)/(bn+x))))

    @param a numerators of the cf
    @param b denominators of the cf

    @return a value of the same type as the parameters elements
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::contfrac_, contfrac, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::contfrac_, contfrac, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::contfrac_, contfrac, 4)

}

namespace nt2
 {
   namespace ext
   {
     template<class Domain, int N, class Expr>
     struct  size_of<tag::contfrac_,Domain,N,Expr>
     {
       typedef typename  boost::proto::result_of::child_c<Expr&,0>::value_type::extent_type result_type;

       BOOST_FORCEINLINE result_type operator()(Expr& e) const
       {
         result_type sizee = boost::proto::child_c<0>(e).extent();
         return sizee;
       }
     };

     template<class Domain, int N, class Expr>
     struct  value_type<tag::contfrac_,Domain,N,Expr>
     {
       typedef typename  boost::proto::result_of
       ::child_c<Expr&,0>::value_type::value_type  intype;
       typedef intype type;
     };
   }
}
#endif
