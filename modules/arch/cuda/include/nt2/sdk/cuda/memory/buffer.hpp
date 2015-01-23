//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_CUDA_MEMORY_BUFFER_HPP_INCLUDED
#define NT2_SDK_CUDA_MEMORY_BUFFER_HPP_INCLUDED

#include <nt2/sdk/cuda/cuda.hpp>
#include <cublas.h>
#include <boost/throw_exception.hpp>
#include <boost/assert.hpp>
#include <boost/swap.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/include/functions/resize.hpp>
#include <nt2/include/functions/size.hpp>
#include <limits>

#define CUDA_ERROR(status)                                   \
  {                                                               \
    BOOST_ASSERT_MSG( status == cudaSuccess                       \
                    , cudaGetErrorString(status));                \
  }                                                               \


namespace nt2 { namespace memory
{
  //============================================================================
  /**!
   * @brief cuda_buffer is a dynamically-sized sequence using dynamic storage.
   **/
  //===========================================================================
  template<class T>
  class cuda_buffer
  {
  public:
    //==========================================================================
    // Container types
    //==========================================================================

    typedef T               value_type;
    typedef T*              pointer;
    typedef T const*        const_pointer;
    typedef T*              iterator;
    typedef T const*        const_iterator;
    typedef T&              reference;
    typedef T const&        const_reference;
    typedef std::size_t     size_type;
    typedef std::ptrdiff_t  difference_type;

    //==========================================================================
    // Default constructor
    //==========================================================================
    cuda_buffer() : begin_(0), end_(0), stream_(0)
    {}

  public:
    //==========================================================================
    // Size constructor
    //==========================================================================
    cuda_buffer( int n)
          :  begin_(0), end_(0), stream_(0)
    {
      if(!n) return;

      CUDA_ERROR(cudaMalloc( reinterpret_cast<void**>(&begin_)
                           , n* sizeof(value_type)
                           ));
      end_ = begin_ + n;
    }

    //==========================================================================
    // Copy constructor
    //==========================================================================
    cuda_buffer( cuda_buffer const& src )
          : begin_(0), end_(0), stream_(0)
    {
      if(!src.size()) return;

      CUDA_ERROR(cudaMalloc( reinterpret_cast<void**>(&begin_)
                           , src.size()*sizeof(value_type)
                           ));

       CUDA_ERROR(cudaMemcpyAsync( begin_
                                 , src.data()
                                 , src.size()* sizeof(value_type)
                                 , cudaMemcpyDeviceToDevice
                                 , stream_
                                 ));

      end_ = begin_ + src.size();
    }

    template<typename Container>
    cuda_buffer( Container const& src )
          : begin_(0), end_(0), stream_(0)
    {
      if(!src.size()) return;

      CUDA_ERROR(cudaMalloc( reinterpret_cast<void**>(&begin_)
                           , src.size()*sizeof(value_type)
                           ));

      CUDA_ERROR(cudaMemcpyAsync( begin_
                                , src.data()
                                , 10 * sizeof(value_type)
                                ,  cudaMemcpyHostToDevice
                                , stream_
                                ));
      end_ = begin_ + src.size();
    }

    //==========================================================================
    // Destructor
    //==========================================================================
    ~cuda_buffer()
    {
      if(stream_ != NULL)
      {
        cudaStreamDestroy(stream_);
      }

      if(begin_)
      {
        cudaFree(begin_);
      }
    }

    //==========================================================================
    // Assignment
    //==========================================================================
    cuda_buffer& operator=(cuda_buffer const& src)
    {
      if(!src.size()) return *this;

      if( src.size() > this->size() )
      {
        cudaFree(begin_);
        CUDA_ERROR(cudaMalloc( reinterpret_cast<void**>(&begin_)
                             , src.size()*sizeof(value_type)
                             ));

        end_ = begin_ + src.size();
      }

      CUDA_ERROR(cudaMemcpyAsync( begin_
                                , src.data()
                                , src.size()*sizeof(value_type)
                                , cudaMemcpyDeviceToDevice
                                , stream_
                                ));

      return *this;
    }

    template<class Container>
    cuda_buffer& operator=(Container const& src)
    {
      if(!src.size()) return *this;

      if( src.size() > this->size() )
      {
        cudaFree(begin_);
        CUDA_ERROR(cudaMalloc( reinterpret_cast<void**>(&begin_)
                             , src.size()*sizeof(value_type)
                             ));

        end_ = begin_ + src.size();
      }

      CUDA_ERROR(cudaMemcpyAsync( begin_
                                , src.data()
                                , src.size()* sizeof(value_type)
                                , cudaMemcpyHostToDevice
                                , stream_
                                ));

      return *this;
    }

    //==========================================================================
    // Swap
    //==========================================================================
    void swap( cuda_buffer& src )
    {
      boost::swap(begin_          , src.begin_          );
      boost::swap(end_            , src.end_            );
      boost::swap(stream_         , src.stream_         );
    }

    //==========================================================================
    // Iterators
    //==========================================================================
    iterator        begin()       { return begin_;  }
    const_iterator  begin() const { return begin_;  }
    iterator        end()         { return end_;    }
    const_iterator  end()   const { return end_;    }

    //==========================================================================
    // Raw values
    //==========================================================================
    pointer        data()       { return begin_;  }
    const_pointer  data() const { return begin_;  }

    template<typename Container>
    void data(Container & dst) const
    {
      if(!this->size()) return;
      if ( dst.size() != this->size() ) dst.resize(nt2::of_size(this->size(),1));

      CUDA_ERROR(cudaMemcpyAsync( dst.data()
                                , this->begin_
                                , this->size() * sizeof(value_type)
                                , cudaMemcpyDeviceToHost, stream_
                                ));
    }

    //==========================================================================
    // Size related members
    //==========================================================================
    inline size_type  size()      const { return end_ - begin_;       }
    inline bool       empty()     const { return size() == 0;         }
    inline size_type  max_size()  const
    {
      return (std::numeric_limits<size_type>::max)() / sizeof(T);
    }

    //==========================================================================
    // Stream related -- if neccesary
    //==========================================================================
    inline cudaStream_t   stream()     const { return stream_;  }
    inline cudaError_t   setStream()     const
      { return cudaStreamCreate(&stream_); }


  private:
    pointer     begin_, end_;
    cudaStream_t stream_;
  };

  //============================================================================
  /**!
   * Swap the contents of two buffer
   * \param x First \c pointer_buffer to swap
   * \param y Second \c pointer_buffer to swap
   **/
  //============================================================================
  template<class T> inline void swap(cuda_buffer<T>& x, cuda_buffer<T>& y)
  {
    x.swap(y);
  }

} }

#endif
