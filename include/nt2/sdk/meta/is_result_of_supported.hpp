/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_IS_RESULT_OF_SUPPORTED_HPP_INCLUDED
#define NT2_SDK_META_IS_RESULT_OF_SUPPORTED_HPP_INCLUDED

#include <boost/mpl/or.hpp>
#include <boost/utility/enable_if.hpp>
#include <nt2/sdk/meta/enable_if_type.hpp>
#include <boost/function_types/result_type.hpp>

namespace nt2
{
  namespace details
  {
    //////////////////////////////////////////////////////////////////////////
    // Is result_type defined in a given type ?
    //////////////////////////////////////////////////////////////////////////
    BOOST_MPL_HAS_XXX_TRAIT_DEF(result_type)

    //////////////////////////////////////////////////////////////////////////
    // Is a inner result struct defined in a given type ?
    //////////////////////////////////////////////////////////////////////////
    template<class F, class FArgs, class Enable=void>
    struct result_defined
         : boost::mpl::false_ {};

    template<class F, class Args>
    struct result_defined< F
                         , Args
                         , typename meta::enable_if_type<
                                    typename F::template result<Args>::type
                                                        >::type
                         >
         : boost::mpl::true_ {};
  }

  namespace meta
  {
    template<class T, class Enable=void>
    struct is_result_of_supported : public boost::mpl::false_ {};

    template<class T>
    struct is_result_of_supported<T, typename boost::enable_if_c<
          boost::mpl::or_< details::has_result_type<
                          typename boost::function_types::result_type<T>::type
                                                   >
                         , details::result_defined<
                          typename boost::function_types::result_type<T>::type,T
                                                  >
                         >::value
            >::type
        > : boost::mpl::true_ {};
  }
}
#endif
