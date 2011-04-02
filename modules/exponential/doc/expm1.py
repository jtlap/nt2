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
             'included' : ['#include <nt2/include/functions/log1p.hpp>',
                           '#include <nt2/include/functions/sqrt1pm1.hpp>',
                           'extern "C" { long double cephes_expm1l(long double); }'],
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
                 'nt2::Inf<T>()' : {"result" :'nt2::Inf<r_t>()','ulp_thresh' : '1.0',},
                 'nt2::Minf<T>()' : {"result" :'nt2::Mone<r_t>()','ulp_thresh' : '1.0',},
                 'nt2::Mone<T>()' : {"result" :'nt2::One<r_t>()/nt2::Exp_1<r_t>()-nt2::One<r_t>()','ulp_thresh' : '1.0'},
                 'nt2::Nan<T>()' : {"result" :'nt2::Nan<r_t>()','ulp_thresh' : '1.0',},
                 'nt2::One<T>()' : {"result" :'nt2::Exp_1<r_t>()-nt2::One<r_t>()','ulp_thresh' : '1.0',},
                 'nt2::Zero<T>()' :{"result" : 'nt2::Zero<r_t>()','ulp_thresh' : '1.0',},
                },
             'signed_int_' : {
                 'nt2::Mone<T>()' : {"result" :'nt2::One<r_t>()/nt2::Exp_1<r_t>()-nt2::One<r_t>()','ulp_thresh' : '1.0',},
                 'nt2::One<T>()' : {"result" :'nt2::Exp_1<r_t>()-nt2::One<r_t>()','ulp_thresh' : '1.0',},
                 'nt2::Zero<T>()' : {"result" :'nt2::Zero<r_t>()','ulp_thresh' : '1.0',},
                },
             'unsigned_int_' : {
                 'nt2::One<T>()' : {"result" :'nt2::Exp_1<r_t>()-nt2::One<r_t>()','ulp_thresh' : '1.0',},
                 'nt2::Zero<T>()' : {"result" :'nt2::Zero<r_t>()','ulp_thresh' : '1.0',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'real_' : ['nt2::expm1(a0)','nt2::log1p(nt2::expm1(a0))', 'nt2::log1p(nt2::sqrt1pm1(a0))'],
                },
             'property_value' : {
                 'real_' : ['::cephes_expm1l(a0)','r_t(a0)', 'nt2::Half<r_t>()*nt2::log1p(a0)'],
                },
             'ulp_thresh' : {
                 'real_' : ['1.0','1.5', '2.'],
                },
            },
        },
     'version' : '0.1',
    },
]
