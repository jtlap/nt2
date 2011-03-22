[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '1',
         'call_types' : ['T'],
         'ret_arity' : '2',
         'rturn' : {
             'default' : 'boost::fusion::vector<T,T>',
            },
         'simd_types' : [],
         'special' : ['fdlibm'],
         'type_defs' : [],
         'types' : ['double'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 03/03/2011',
             'included' : ['#include <nt2/include/functions/trunc.hpp>',
                           '#include <nt2/include/functions/frac.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 03/03/2011',
            },
         'ranges' : {
             'default' : [['T(-10)', 'T(10)']],
            },
         'specific_values' : {
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::fdlibm::modf(a0)'],
                },
             'property_value' : {
                 'default' : [['nt2::frac(a0)','nt2::trunc(a0)']],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'default' : ['1'],
                },
            },
        },
    },
]
