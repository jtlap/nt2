#ifndef NT2_SDK_MATLAB_MATLAB_HPP_INCLUDED
#define NT2_SDK_MATLAB_MATLAB_HPP_INCLUDED

#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/construct.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/sdk/meta/primitive_of.hpp>
#include <functional>

#include <boost/mpl/bool.hpp>
namespace nt2 { namespace meta
{
  template<typename T, typename Dummy = void>
  struct is_complex : boost::mpl::false_
  {
  };
} }

#include <nt2/sdk/matlab/class.hpp>

namespace nt2 { namespace matlab
{
  namespace details
  {
    template<typename T>
    typename meta::primitive_of<T>::type* get_data(mxArray* p)
    {
      return static_cast<typename meta::primitive_of<T>::type*>(mxGetData(p));
    }
    
    template<class T, class Out>
    struct linearizer
    {
      linearizer(T const& t_, Out out_) : t(t_), out(out_) {}
      T const& t;
      mutable Out out;
      
      template<class P>
      void operator()(P const& pos) const
      {
        typedef typename boost::dispatch::meta::semantic_of<T>::type semantic;
        typedef typename boost::remove_reference<typename meta::primitive_of<semantic>::type>::type target;
        *out++ = nt2::run(t, pos, nt2::meta::as_<target>());
      }
    };
    
    template<class T, class Out>
    Out linearize(T const& t, Out out)
    {
      linearizer<T, Out> lin(t, out);
      meta::for_each( typename T::index_type::type()
                    , nt2::extent(t)
                    , 1
                    , lin
                    );
      return lin.out;
    }
  }

  template<typename T>
  mxArray* to_matlab(T const& t)
  {
    typename meta::call<tag::extent_(T const&)>::type dims = nt2::extent(t);
        
    typedef typename meta::primitive_of<T>::type Primitive;
    mxArray* p = 
      mxCreateNumericArray(
        dims.size(),
        dims.data(), 
        class_<Primitive>::value,
        meta::is_complex<T>::value ? mxCOMPLEX : mxREAL
      )
    ;
        
    details::linearize(t, details::get_data<T>(p));
    return p;
  }
    
  template<typename T>
  T from_matlab(mxArray* t)
  {
    typedef typename meta::primitive_of<T>::type Primitive;

    const mwSize* dims = mxGetDimensions(t);
    mwSize dims_size = mxGetNumberOfDimensions(t);

    mwSize nb_elems =
      std::accumulate(
        dims,
        dims + dims_size,
        1,
        std::multiplies<mwSize>()
      )
    ;
        
    T out;
    nt2::construct( out
                  , nt2::of_size_max(dims, dims + dims_size)
                  , details::get_data<T>(t)
                  , details::get_data<T>(t) + nb_elems*sizeof(Primitive)
                  );
    return out;
  }
} }

#endif
