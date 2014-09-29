//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_MAGMA_BUFFER_HPP_INCLUDED
#define NT2_LINALG_DETAILS_MAGMA_BUFFER_HPP_INCLUDED

#include <nt2/sdk/magma/magma.hpp>
#include <cublas.h>
#include <cstddef>
#include <boost/throw_exception.hpp>
#include <boost/assert.hpp>
#include <new>

namespace nt2 { namespace details
{

  //============================================================================
  // Allocate a raw buffer of bytes using MAGMA
  //============================================================================
  template<class T> struct magma_buffer
  {
    //============================================================================
    // Internal typedefs
    //============================================================================
    typedef T               value_type;
    typedef T*              pointer;
    typedef T const*        const_pointer;
    typedef T&              reference;
    typedef T const&        const_reference;
    typedef std::size_t     size_type;
    typedef std::ptrdiff_t  difference_type;

    magma_buffer( size_type h, size_type w, const_pointer host = 0 )
                : gpu_ptr_(0), height_(h), width_(w)
    {
      void *ptr;
      cudaError_t status = cudaMalloc ( reinterpret_cast<void**>(&ptr)
                                      , h*w*sizeof(value_type)
                                      );

      if(status != cudaSuccess) BOOST_THROW_EXCEPTION( std::bad_alloc() );

      gpu_ptr_ = reinterpret_cast<pointer>(ptr);

      if(host)
      {
        cublasStatus_t e = cublasSetMatrix( h,w,sizeof(value_type)
                                          , host    , h
                                          , gpu_ptr_, h
                                          );

        BOOST_ASSERT_MSG( e == CUBLAS_STATUS_SUCCESS , "Error in cublasSetMatrix");
      }
    }


    ~magma_buffer() { cudaFree(gpu_ptr_); }

    pointer raw() const { return gpu_ptr_; }

    void* raw( pointer host ) const
    {
      cublasGetMatrix ( height_, width_, sizeof(value_type)
                      , gpu_ptr_, height_, host, height_
                      );
      return host;
    }

    private:
    pointer   gpu_ptr_;
    size_type height_, width_;
  };


} }

#endif

