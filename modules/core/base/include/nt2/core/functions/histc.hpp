//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_HISTC_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_HISTC_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the histc functor
    **/
    struct histc_ : ext::tieable_<histc_>
    {
      typedef ext::tieable_<histc_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_histc_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::histc_, Site> dispatching_histc_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::histc_, Site>();
    }
    template<class... Args>
    struct impl_histc_;
  }


  /*!
    @brief  histogram bin counts


    @code
    T0 r = histc(x, bins);
    @endcode

    bins is the vector of bin edges (if bins is not a vector, the column vector bins(_) is used)
    Counted in r(i) are those in [bins(i), bins(i+1)[, except for the last bin
    which only counts elements equal to bins(end_).
    Values outside of [bins(1), bins(end_)] are not counted. Use appropriate infs to catch all (but nans).

    if x is multidimensionnal the histograms are done along the first not singleton dimension.

    @param  x values to be counted
    @param  bins vector of edges (if bins is not a vector bins(_) is used)


  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::histc_, histc, 2)

  /*!
    @brief historam bin counts

    @code
    T0 r = histc(x, bins, dim);
    @endcode

    bins is the vector of bin edges (if bins is not a vector, the column vector bins(_) is used)
    Counted in r(i) are those in [bins(i), bins(i+1)[, except for the last bin
    which only counts elements equal to bins(end_).
    Values outside of [bins(1), bins(end_)] are not counted. Use appropriate infs to catch all (but nans).

    the histograms are done along the dimension dim.

    @param  x values to be counted
    @param  integer value or bins edges
    @param  dimension along which to perform the counts
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::histc_, histc, 3)
}
namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::histc_,Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of
                    ::child_c<Expr&,0>::value_type::extent_type result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee = boost::proto::child_c<0>(e).extent();
      sizee[firstnonsingleton(boost::proto::child_c<0>(e))-1] = numel(boost::proto::child_c<1>(e));
      return sizee;
    }
  };
} }

#endif
