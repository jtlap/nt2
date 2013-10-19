#include <nt2/sdk/tbb/tbb.hpp>

#if defined(NT2_USE_TBB)

#include <nt2/sdk/shared_memory/spawner/spawner.hpp>
#include <nt2/sdk/shared_memory/spawner/parfor.hpp>

#ifndef BOOST_NO_EXCEPTIONS
#include <boost/exception_ptr.hpp>
#endif

namespace nt2
{
  template<class Site>
  struct spawner< tag::parfor_, tag::tbb_<Site> >
  {

    spawner(){}

    template<typename Worker>
    void operator()(Worker worker_, std::size_t begin_, std::size_t size_, std::size_t grain_)
    {

#ifndef BOOST_NO_EXCEPTIONS
      boost::exception_ptr exception;
#endif

      #ifndef BOOST_NO_EXCEPTIONS
            try
            {
      #endif

             tbb::parallel_for( nt2::blocked_range<std::size_t>(begin_,begin_+size_,grain_),
                                worker_);

      #ifndef BOOST_NO_EXCEPTIONS
            }
            catch(...)
            {
              exception = boost::current_exception();
            }
      #endif
    }
};
}

#endif
