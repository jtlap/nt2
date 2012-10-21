//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FIND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FIND_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the find function
**/

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/nbtrue.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/sdk/memory/container_shared_ref.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <ostream>
#include <nt2/sdk/meta/type_id.hpp>
#include <nt2/table.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the find functor
    **/
    struct find_ : ext::tieable_<find_>
    {
      typedef ext::tieable_<find_> parent;
    };
  }

  /*!
    @brief

    @param
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::find_, find, 1)

  /*!
    @brief

    @param
    @param
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::find_, find, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::find_, find, 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::find_, find, 4)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::find_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {
    typedef nt2::_1D result_type;
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type c0_t;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      c0_t a0 = boost::proto::child_c<0>(e);
      ptrdiff_t k = boost::proto::value(boost::proto::child_c<1>(e));
      BOOST_ASSERT_MSG(k > 0, "Error using find: second argument must be a positive scalar integer."); 
      ptrdiff_t n =ptrdiff_t(nt2::nbtrue(nt2::colvect(a0))(1));
      return (k > 0)? nt2::min(k, n) : 0; 
    }

  };

  template<class Domain, class Expr>
  struct  size_of<tag::find_,Domain,1,Expr>
        : meta::size_as<Expr,0>
  {
    typedef nt2::_1D result_type;
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type c0_t;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      c0_t a0 = boost::proto::child_c<0>(e);
      return result_type(ptrdiff_t(nt2::nbtrue(nt2::colvect(a0))(1)));
    }

  };

  template<class Domain, int N, class Expr>
  struct  value_type<tag::find_,Domain,N,Expr>
  {
    typedef std::ptrdiff_t      type;

  };


  
} }
    


#endif

