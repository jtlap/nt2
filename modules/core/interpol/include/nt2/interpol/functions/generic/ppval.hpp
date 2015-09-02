//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTERPOL_FUNCTIONS_GENERIC_PPVAL_HPP_INCLUDED
#define NT2_INTERPOL_FUNCTIONS_GENERIC_PPVAL_HPP_INCLUDED

#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/depth.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/interpol/functions/details/bsearch.hpp>
#include <boost/type_traits/is_integral.hpp>

namespace nt2 { namespace ext
{

  template < class T, class V = T> class ppval{
  public:
    typedef T                                                             x_type;
    typedef V                                                         value_type;
    typedef typename meta::as_integer<x_type>::type                   index_type;
    typedef table<x_type>                                                 xtab_t;
    typedef table<value_type>                                             vtab_t;
    typedef table<index_type>                                             itab_t;

    template < class XPR1,  class XPR2 >
    ppval(const XPR1 & breaks_, const XPR2 &coefs_):
      form("pp"){
      size_t dlk = numel(coefs_);
      size_t l   = minusone(numel(breaks_));
      size_t k  = dlk/l;
      BOOST_ASSERT_MSG((k > 0)&&(l*k == dlk), "breaks and coefs do not fit in size");
      breaks = reshape(breaks_,1,l+1);
      coefs = reshape(coefs,l,k);
      pieces = l;
      order = k;
      dim = 1;
    }

    template < class XPR1,  class XPR2,  class DIM>
    ppval(const XPR1 & breaks_, const XPR2 &coefs_,  const DIM & d):
      form("pp"){
      using is_int = typename boost::is_integral<DIM>::type;
      size_t dlk = numel(coefs_);
      size_t l   = minusone(numel(breaks_));
      size_t dl =  num(d, is_int())*l;
      size_t k  = dlk/dl;
      BOOST_ASSERT_MSG((k > 0)&&(dl*k == dlk), "breaks and coefs do not fit in size");
      breaks = reshape(breaks_,1,l+1);
      coefs = reshape(coefs_,dl,k);
      pieces = l;
      order = k;
      dim = d;
    }

    const table<value_type>& getbreaks()  const{return breaks; }
    const table<value_type>& getcoefs ()  const{return coefs;  }
    size_t                   getorder()   const{return order;  }
    size_t                   getpieces()  const{return pieces; }
    const std::string &      getform()    const{return form;   }
    template < class A>
    void                     setdim(const A & dim_) { dim = dim_; }

    template < class D > BOOST_FORCEINLINE
    static size_t num(const D& d, const boost::mpl::true_ &)
    {
      return d;
    }
    template < class D >BOOST_FORCEINLINE
    static size_t num(const D& d, const boost::mpl::false_ &)
    {
      return numel(d);
    }

    template <class XPR> vtab_t eval(const XPR & xxi) const
    {
      xtab_t xii =  xxi;
      table<int> index;
      details::bsearch (index, breaks, xii);
      size_t lx =  numel(xii);
      size_t d = numel(dim);
      xtab_t xi;
      xii -= breaks(index);
      if(d > 1)
      {
        // ... replicate xs and index in case PP is vector-valued ...
        xi = reshape(expand_to(xii, of_size(d, lx)),1,d*lx);
        index *= int(d);
        table<int> temp = colvect(_(-int(d), -1));
        table<int> tmp1 = oneplus(index(ones(d,1, meta::as_<int>()),_));
        index = reshape( tmp1+temp(_,ones(1,lx, meta::as_<int>())), d*lx, 1);
      }
      else
        xi =  xii;


      vtab_t val   = coefs(index, 1);
      for(size_t i=2; i <= order; ++i){
        val = fma(xi(_), val, coefs(index,i));
      }
//       auto sizee = of_size(height(xxi), width(xxi), depth(coefs)); // this is incorrect if xi0 is properly _3D
//       val = nt2::reshape(val, sizee);
      return val;
    }

//     template <class XPR> vtab_t eval(const XPR & xxi)
//     {
//       xtab_t xi =  xxi;
//       itab_t index;
//       details::bsearch (index, breaks, xi);
//       xi -= breaks(index);
//       vtab_t val   = coefs(index, 1);
//       for(size_t i=2; i <= order; ++i){
//         val = fma(xi(_), val, coefs(index,i));
//       }
// //       auto sizee = of_size(height(xxi), width(xxi), depth(coefs)); // this is incorrect if xi0 is properly _3D
// //       val = nt2::reshape(val, sizee);
//       return val;
//     }

  private :
    std::string form;
    nt2::table<value_type> breaks;
    nt2::table<value_type> coefs;
    size_t order;
    size_t pieces;
    nt2::of_size_<-1l, -1l, -1l, -1l> dim;
  };


} }


#endif
