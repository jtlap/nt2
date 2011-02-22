#ifndef NT2_TOOLBOX_MATLAB_DETAILS_MCR_HPP_INCLUDED
#define NT2_TOOLBOX_MATLAB_DETAILS_MCR_HPP_INCLUDED

#include <mclmcrrt.h>

struct mcrInstance
{
};

extern "C" mclComponentData __MCC_libnt2_mw_component_data;

namespace nt2 { namespace matlab { namespace details
{

    static int print_handler(const char *s)
    {
        return mclWrite(1 /* stdout */, s, sizeof(char)*strlen(s));
    }
    
    static int error_handler(const char *s)
    {
        int written = 0;
        size_t len = 0;
        len = strlen(s);
        written = mclWrite(2 /* stderr */, s, sizeof(char)*len);
        if (len > 0 && s[ len-1 ] != '\n')
        written += mclWrite(2 /* stderr */, "\n", sizeof(char));
          return written;
    }
    
    struct mcr
    {
        mcr()
        {
            mclInitializeApplication(NULL, 0);
            mclmcrInitialize();
        
            mclInitializeComponentInstanceNonEmbeddedStandalone(
                &inst, &__MCC_libnt2_mw_component_data, true,
                NoObjectType, LibTarget, error_handler, print_handler
            );
        }
        
        ~mcr()
        {
            mclWaitForFiguresToDie(inst);
            mclTerminateInstance(&inst);
            mclTerminateApplication();
        }
        
        mcrInstance* get() const
        {
            return static_cast<mcrInstance*>(inst);
        }
        
    private:
        void* inst;
    };
    
    inline mcrInstance* mcr_instance()
    {
        static mcr m;
        return m.get();
    }
}
}}

#endif
