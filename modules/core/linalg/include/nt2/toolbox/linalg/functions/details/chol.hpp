//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_CHOL_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_CHOL_HPP_INCLUDED

#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/tril.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/toolbox/linalg/details/lapack/potrf.hpp>
#include <nt2/toolbox/linalg/details/lapack/potrs.hpp>
#include <nt2/toolbox/linalg/details/lapack/pocon.hpp>
#include <nt2/toolbox/linalg/details/lapack/lange.hpp>

namespace nt2 { namespace details
{
  template<class T> struct cholesky_result
  {
    typedef typename meta::strip<T>::type                   source_t;
    typedef typename source_t::value_type                   type_t;
    typedef typename source_t::index_type                   index_t;
    typedef typename meta::as_real<type_t>::type            base_t;
    typedef T                                               data_t;
    typedef nt2::table<type_t,index_t>                      result_type;

    template<class Input>
    cholesky_result ( char uplo, Input& xpr )
                    : values_(xpr)
                    , height_( nt2::height(xpr) )
                    , leading_( values_.leading_size() )
                    , info_(0)
                    , uplo_(uplo)
                    , that_(of_size(0, 1))
    {
      BOOST_ASSERT_MSG(issquare(values_), "matrix must be square"); 
      nt2::details::potrf ( &uplo_, &height_
                          , values_.raw(), &leading_, &info_
                          );
    }

    cholesky_result& operator=(cholesky_result const& src)
    {
      values_   = src.values_;
      height_   = src.height_;
      leading_  = src.leading_;
      info_     = src.info_;
      uplo_     = src.uplo_;
      that_     = src.that_; 
      return *this;
    }

    //==========================================================================
    // Return raw values
    //==========================================================================
    data_t values() const { return values_; }

    //==========================================================================
    // Return properly formatted result depending on up/low options
    //==========================================================================
    const result_type& result() const
    {
      if (isempty(that_))
      {
        result_type that_;
        if(uplo_ == 'U')  that_ = nt2::triu(values_);
        else              that_ = nt2::tril(values_);
        
        if(info_ > 0) that_ = nt2::expand(that_, info_-1, info_-1 );
      }
      return that_;
    }

    //==========================================================================
    // Return upper formatted result
    //==========================================================================
    typename  meta::
              call< tag::expand_
                    ( typename  meta::call<tag::triu_(data_t const&)>::type
                    , nt2_la_int
                    , nt2_la_int
                    )
                  >::type
    upper_result() const
    {
      BOOST_ASSERT_MSG( (uplo_ == 'U')
                      , "Lower Cholesky can't return upper result"
                      );

      nt2_la_int p = info_ > 0 ? info_-1 : height_;
      return nt2::expand(nt2::triu(values_), p, p);
    }

    //==========================================================================
    // Return lower formatted result
    //==========================================================================
    typename  meta::
              call< tag::expand_
                    ( typename  meta::call<tag::tril_(data_t const&)>::type
                    , nt2_la_int
                    , nt2_la_int
                    )
                  >::type
    lower_result() const
    {
      BOOST_ASSERT_MSG( (uplo_ == 'L')
                      , "Upper Cholesky can't return lower result"
                      );

      nt2_la_int p = info_ > 0 ? info_-1 : height_;
      return nt2::expand(nt2::tril(values_), p, p);
    }

    //==========================================================================
    // Return post-computation status
    //==========================================================================
    nt2_la_int  status() const { return info_; }

    //==========================================================================
    // Reverse conditioning evaluation
    //==========================================================================
    base_t rcond() const
    {
      char norm = '1';
      base_t anorm = nt2::details::lange( &norm,  &height_,  &height_
                                        , values_.raw(), &leading_
                                        );

      base_t res;
      nt2::details::pocon ( &uplo_, &height_
                          , values_.raw(), &leading_
                          , &anorm, &res, &info_
                          );

      return res;
    }

    //==========================================================================
    // Solver interface
    //==========================================================================
    template<class XPR> result_type solve(const XPR& b ) const
    {
      result_type bb = b;
      inplace_solve(bb);
      return bb;
    }

    template<class Xpr> nt2_la_int inplace_solve(Xpr& b ) const
    {
      nt2_la_int nrhs = nt2::size(b, 2);
      nt2_la_int ldb  = b.leading_size();
      nt2_la_int info; 
      nt2::details::potrs ( &uplo_, &height_, &nrhs
                          , values_.raw(), &leading_
                          , b.raw(), &ldb
                          , &info
                          );
      return info; 
    }

    private:
    data_t      values_;
    nt2_la_int  height_, leading_, info_;
    char        uplo_;
    result_type that_;
  };
} }

#endif
