[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::result_of<nt2::meta::floating(T)>::type',
            },
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
         'simd_types' : ['real_']   
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 08/12/2010',
             'included' : ['#include <nt2/include/functions/expm1.hpp>',
                           '#include <nt2/include/functions/sqrt1pm1.hpp>',
                           'extern "C" { long double cephes_log1pl(long double); }'],
             'notes' : [],
             'stamp' : 'modified by jt the 14/12/2010',
            },
         'ranges' : {
             'real_' : [['T(0.1)', 'T(10)']],
             'signed_int_' : [['0', '100']],
             'unsigned_int_' : [['0', '100']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'nt2::Inf<T>()' : {'result' :'nt2::Inf<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Minf<T>()' :{'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Mone<T>()' : {'result' :'nt2::Minf<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Nan<T>()' : {'result' :'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::One<T>()' : {'result' :'nt2::Log_2<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' :{'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Eps<T>()' :{'result' : 'nt2::Eps<r_t>()','ulp_thresh' : '0.5',},
                },
             'signed_int_' : {
                 'nt2::Mone<T>()' :{'result' : 'nt2::Minf<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::One<T>()' : {'result' :'nt2::Log_2<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' :{'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
             'unsigned_int_' : {
                 'nt2::One<T>()' : {'result' :'nt2::Log_2<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' :'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'real_' : ['nt2::log1p(a0)','nt2::log1p(nt2::expm1(a0))', 'nt2::log1p(nt2::sqrt1pm1(a0))'],
                },
             'property_value' : {
                 'real_' : ['::cephes_log1pl(a0)','a0', 'nt2::Half<T>()*nt2::log1p(a0)'],
                },
             'ulp_thresh' : {
                 'default' : ['1','1.5', '2.0'],
                },
            },
        },
     'version' : '0.1',
    },
]
