#ifndef NT2_TOOLBOX_MATLAB_DETAILS_MCR_HPP_INCLUDED
#define NT2_TOOLBOX_MATLAB_DETAILS_MCR_HPP_INCLUDED

#include <nt2/toolbox/matlab/details/libnt2_mw.h>

namespace nt2 { namespace matlab { namespace details
{
    struct mcr
    {
        mcr()
        {
            mclInitializeApplication(NULL, 0);
            libnt2_mwInitialize();
        }
        
        ~mcr()
        {
            libnt2_mwTerminate();
            mclTerminateApplication();
        }
        
        static void instance()
        {
            static mcr m;
        }
    };
}
}}

#endif
