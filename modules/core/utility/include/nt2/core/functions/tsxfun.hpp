//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TSXFUN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TSXFUN_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

/*!
 * \ingroup core
 * \defgroup core tsxfun
 *
 * \par Description
 * Returns the tsxfun of functor of 3 variables applied to
 * the three other parameters with singleton expansion
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/tsxfun.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0, class A1, class A2, class A3>
 *     meta::call<tag::tsxfun_(A0, A1, A2, A3)>::type
 *     tsxfun(const A0 & a0, const A1 & a1, const A2 & a2, const A3 & a3);
 * }
 * \endcode
 *
 * \param a0 a three parameters elementwise func...something
 * \param a1 a2 a3 the two parameters on which func will be applied
 *        elementwise with singleton expansion
 *
 *
 * \par
 *
**/


namespace nt2
{
  namespace tag
  {
    struct tsxfun_ : ext::elementwise_<tsxfun_>
    {
      typedef ext::elementwise_<tsxfun_> parent;
    };
  }

  //============================================================================
  /*!
   * tsxfun
   *
   * \param xpr  table
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::tsxfun_, tsxfun, 4)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::tsxfun_,Domain,N,Expr>
  {
    // TODO dual static of_size case to handle
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type  c0_t;
    typedef typename boost::proto::result_of::child_c<Expr&,1>::value_type  c1_t;
    typedef typename boost::proto::result_of::child_c<Expr&,2>::value_type  c2_t;
    typedef typename c0_t::extent_type                                      e0_t;
    typedef typename c1_t::extent_type                                      e1_t;
    typedef typename c2_t::extent_type                                      e2_t;

    typedef typename  make_size < (e0_t::static_size > e1_t::static_size)
                                ? e0_t::static_size
                                : e1_t::static_size
                                >::type                     et_t;
    typedef typename  make_size < (et_t::static_size > e2_t::static_size)
                                ? et_t::static_size
                                : e2_t::static_size
                                >::type                     result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type s1 = boost::proto::child_c<0>(e).extent();
      result_type s2 = boost::proto::child_c<1>(e).extent();
      result_type s3 = boost::proto::child_c<2>(e).extent();
      result_type sizee ;

      for(size_t i = 0; i < sizee.size(); ++i)
      {
        sizee[i] = std::max(std::max(s1[i], s2[i]), s3[i]);
        BOOST_ASSERT_MSG
        ( ((s1[i] == sizee[i])||(s1[i] == 1))  &&
          ((s2[i] == sizee[i])||(s2[i] == 1)) &&
          ((s3[i] == sizee[i])||(s3[i] == 1))
        , "??? Operands dimensions are not compatible in tsxfun:\n"
          "where dimensions differ the set of values must be of"
          "cardinal 2 and one of the values must be 1"
        );
      }

      return sizee;
    }
  };

  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::tsxfun_,Domain,N,Expr>
  {
    typedef typename meta::
            call< nt2::tag::tsxfun_
                ( typename  boost::proto::result_of
                            ::child_c<Expr&,3>::value_type::value_type
                , typename  boost::proto::result_of
                            ::child_c<Expr&,0>::value_type::value_type
                , typename  boost::proto::result_of
                            ::child_c<Expr&,1>::value_type::value_type
                , typename  boost::proto::result_of
                            ::child_c<Expr&,2>::value_type::value_type
                )
                >::type                            type;

  };
} }

#endif
