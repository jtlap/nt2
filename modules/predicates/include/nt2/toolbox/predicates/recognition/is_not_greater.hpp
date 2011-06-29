/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_PREDICATES_RECOGNITION_IS_NOT_GREATER_HPP_INCLUDED
#define NT2_TOOLBOX_PREDICATES_RECOGNITION_IS_NOT_GREATER_HPP_INCLUDED

#include <nt2/sdk/dsl/category.hpp>
#include <nt2/sdk/dsl/recognition.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/toolbox/predicates/function/is_not_greater.hpp>

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::logical_not_ , tag::recognition_, (A0)(Dom)(Sema)
			      , ((expr_<A0,Dom,tag::is_greater_,Sema>))
			      )
  {

      typedef typename  meta::call< tag::is_not_greater_(
          typename boost::proto::result_of::child_c<A0, 0>::type
        ) >::type result_type; 

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return is_not_greater(boost::proto::child_c<0>(a0));
    }
  };
} }

#endif
