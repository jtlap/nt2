[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' :['Cubic root: \\\\f$\\\\sqrt[3]{a_0}\\\\f$'] ,  
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_floating<T>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
         'simd_types' : ['real_']   
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 08/12/2010',
             'cover_included' : ['#include <nt2/include/functions/sqr.hpp>', 'extern "C" { long double cephes_cbrtl(long double);}'],
             'notes' : [],
             'stamp' : 'modified by jt the 14/12/2010',
            },
         'ranges' : {
             'real_' : [['T(-10)', 'T(10)']],
             'signed_int_' : [['-100', '100']],
             'unsigned_int_' : [['0', '100']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'T(8)' : {'result' : 'T(2)','ulp_thresh' : '0.5',},
                 'nt2::Inf<T>()'  :{'result' :  'nt2::Inf<r_t>()', 'ulp_thresh' : '0.5',},
                 'nt2::Minf<T>()' :{'result' :  'nt2::Minf<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Mone<T>()' :{'result' :  'nt2::Mone<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Nan<T>()'  :{'result' :  'nt2::Nan<r_t>()', 'ulp_thresh' : '0.5',},
                 'nt2::One<T>()'  :{'result' :  'nt2::One<r_t>()', 'ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' :{'result' :  'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
             'signed_int_' : {
                 'nt2::Mone<T>()' :{'result' :  'nt2::Mone<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::One<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' :{'result' :  'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
             'unsigned_int_' : {
                 'nt2::One<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' :{'result' :  'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::cbrt(a0)', 'nt2::sqr(nt2::cbrt(a0))*nt2::cbrt(a0)'],
                },
             'property_value' : {
                 'default' : ['r_t(::cephes_cbrtl(a0))', 'r_t(a0)'],
                },
             'ulp_thresh' : {
                 'default' : ['2', '3'],
                },
            },
        },
     'version' : '0.1',
    },
]
