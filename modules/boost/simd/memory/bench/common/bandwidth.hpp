//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BANDWIDTH_HPP_INCLUDED
#define BANDWIDTH_HPP_INCLUDED

#include <boost/simd/include/functions/store.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <vector>

#include <nt2/sdk/bench/benchmark.hpp>

template<typename T, typename Mode> class bandwidth;

//==============================================================================
// Base benchmark
//==============================================================================
template<typename T> class bandwidth_base
{
  public:
  typedef typename boost::dispatch::meta::scalar_of<T>::type type;

  bandwidth_base( std::size_t byte_size )
                : size(byte_size/sizeof(type))
  {}

  double compute(nt2::benchmark_result_t const& r) const
  {
    return (double(2*size*sizeof(type))/r.second*1e6)/(1<<30);
  }

  void info(std::ostream& os) const { os << double(size*sizeof(type))/(1<<20); }

  void reset() const
  {
    in.resize(size);
    out.resize(size);
  }

  protected:
          std::size_t                                             size;
  mutable std::vector<type, boost::simd::memory::allocator<T> >   in;
  mutable std::vector<type, boost::simd::memory::allocator<T> >   out;
};

//==============================================================================
// NT2 based impementation
//==============================================================================
struct nt2_ {};

template<typename T>  NT2_EXPERIMENT((bandwidth<T,nt2_>))
                    , public bandwidth_base<T>
{
  typedef bandwidth_base<T> base;

  public:
  bandwidth( std::size_t byte_size, double d )
            : NT2_EXPRIMENT_CTOR(d,"Gb/s")
            , base(byte_size)
  {}

  virtual void run() const
  {
    for ( std::size_t i=0
        ; i<base::size
        ; i+=boost::simd::meta::cardinal_of<T>::value
        )
    boost::simd::store( boost::simd::load<T>(&base::in[i])
                      , &base::out[i]
                      );
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return base::compute(r);
  }

  virtual void info(std::ostream& os) const { base::info(os); }
  virtual void reset() const { base::reset(); }
};

//==============================================================================
// C based impementation
//==============================================================================
struct C_       {};

template<typename T>  NT2_EXPERIMENT((bandwidth<T,C_>))
                    , public bandwidth_base<T>
{
  typedef bandwidth_base<T> base;

  public:
  bandwidth( std::size_t byte_size, double d )
            : NT2_EXPRIMENT_CTOR(d,"Gb/s")
            , base(byte_size)
  {}

  virtual void run() const
  {
    for ( std::size_t i=0
        ; i<base::size
        ; i+=boost::simd::meta::cardinal_of<T>::value
        )
    base::out[i] = base::in[i];
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return base::compute(r);
  }

  virtual void info(std::ostream& os) const { base::info(os); }
  virtual void reset() const { base::reset(); }
};

//==============================================================================
// memcpy based implementation
//==============================================================================
struct memcpy_  {};

template<typename T>  NT2_EXPERIMENT((bandwidth<T,memcpy_>))
                    , public bandwidth_base<T>
{
  typedef bandwidth_base<T> base;

  public:
  bandwidth( std::size_t byte_size, double d )
            : NT2_EXPRIMENT_CTOR(d,"Gb/s")
            , base(byte_size)
  {}

  virtual void run() const
  {
    ::memcpy(&base::out[0], &base::in[0], base::size*sizeof(T));
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return base::compute(r);
  }

  virtual void info(std::ostream& os) const { base::info(os); }
  virtual void reset() const { base::reset(); }
};

#endif
