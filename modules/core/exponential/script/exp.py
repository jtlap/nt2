[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' :['exponential function: \f$e^{a_0}\f$'] ,  
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_floating<T>::type',
            },
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
         'simd_types' : ['real_']   
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 08/12/2010',
             'cover_included' : 
                ['#include <nt2/include/functions/log.hpp>',
                 '#include <nt2/include/functions/sqr.hpp>',
                 'extern "C" { long double cephes_expl(long double); }'],
             'notes' : [],
             'stamp' : 'modified by jt the 18/2/2011',
            },
         'ranges' : {
             'real_' : [['T(-10)', 'T(10)']],
             'signed_int_' : [['-10', '10']],
             'unsigned_int_' : [['0', '10']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'nt2::Inf<T>()' : {'result' : 'nt2::Inf<r_t>()','ulp_thresh' : '0.75',},
                 'nt2::Minf<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.75',},
                 'nt2::Mone<T>()' : {'result' : 'nt2::One<r_t>()/nt2::Exp_1<r_t>()','ulp_thresh' : '0.75',},
                 'nt2::Nan<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.75',},
                 'nt2::One<T>()' : {'result' : 'nt2::Exp_1<r_t>()','ulp_thresh' : '0.75',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0.75',},
                },
             'signed_int_' : {
                 'nt2::Mone<T>()' : {'result' : 'nt2::One<r_t>()/nt2::Exp_1<r_t>()','ulp_thresh' : '0.75',},
                 'nt2::One<T>()' : {'result' : 'nt2::Exp_1<r_t>()','ulp_thresh' : '0.75',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0.75',},
                },
             'unsigned_int_' : {
                 'nt2::One<T>()' : {'result' : 'nt2::Exp_1<r_t>()','ulp_thresh' : '0.75',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0.75',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::exp(a0)'],#, 'nt2::log(nt2::exp(a0))', 'nt2::sqr(nt2::exp(a0))'],
                },
             'property_value' : {
                 'default' : ['::cephes_expl(a0)'],#, 'r_t(a0)', 'nt2::exp(2*a0)'],
                },
             'ulp_thresh' : {
                 'default' : ['0.5', '35.0', '1.5'],
                },
            },
        },
     'version' : '0.1',
    },
]
