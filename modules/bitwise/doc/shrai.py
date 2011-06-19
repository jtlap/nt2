[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : ['T', 'iT'],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['unsigned_int_', 'signed_int_'],
         'type_defs' : ['typedef T r_type;'],
         'types' : ['unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 18/02/2011',
             'included' : ['#include <nt2/include/functions/twopower.hpp>'],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 18/02/2011',
            },
         'ranges' : {
             'default' : [['nt2::Valmin<T>()/2', 'nt2::Valmax<T>()/2'], ['T(0)', 'sizeof(T)*8-1']],
            },
         'specific_values' : {
             'signed_int_' : {
                 '-nt2::Four<T>(),1' : {'result' : '-nt2::Two<r_t>()','ulp_thresh' : '0.5',},
                 'T(-3),(1)' : {'result' : '-nt2::Two<r_t>()','ulp_thresh' : '0.5',},
                 'T(-2),(1)' : {'result' : 'nt2::Mone<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Mone<T>(),(sizeof(r_type)*8-1)' : {'result' : 'nt2::Mone<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Mone<T>(),(sizeof(r_type)*8-2)' : {'result' : 'nt2::Mone<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::One<T>(),1' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                 'T(2),(1)' : {'result' : 'nt2::One<T>()','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>(),1' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
             'unsigned_int_' : {
                 'nt2::Mone<T>(),(sizeof(r_type)*8-1)' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Mone<T>(),(sizeof(r_type)*8-2)' : {'result' : 'nt2::Three<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::One<T>(),(1)' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                 'T(2),(1)' : {'result' : 'nt2::One<T>()','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>(),(1)' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'unsigned_int_' : ['nt2::shrai(a0,a1)'],
                },
             'property_value' : {
                 'unsigned_int_' : ['a0/nt2::twopower(a1)'],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
    },
]
