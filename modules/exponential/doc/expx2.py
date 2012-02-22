[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' :['exponential of square function: \f$e^{a_0^2}\f$','\par',
                         'provisions are made for otaining correct results for large a0'] ,  
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
             'first_stamp' : ' created by jt the 08/12/2010',
             'cover_included' : ['#include <nt2/include/functions/log.hpp>',
                           '#include <nt2/include/functions/sqrt.hpp>',
                           'extern "C" { long double cephes_expx2l(long double); }'],
             'notes' : [],
             'stamp' : 'modified by jt the 14/12/2010',
            },
         'ranges' : {
             'real_' : [['T(1)', 'T(5)']],
             'signed_int_' : [['0', '5']],
             'unsigned_int_' : [['0', '5']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'nt2::Inf<T>()' : {"result" :'nt2::Inf<r_t>()',"ulp_thresh" : '1.0',},
                 'nt2::Minf<T>()' : {"result" :'nt2::Inf<r_t>()',"ulp_thresh"  : '1.0',},
                 'nt2::Mone<T>()' : {"result" :'nt2::Exp_1<r_t>()',"ulp_thresh"  : '1.0',},
                 'nt2::Nan<T>()' : {"result" :'nt2::Nan<r_t>()',"ulp_thresh"  : '1.0',},
                 'nt2::One<T>()' : {"result" :'nt2::Exp_1<r_t>()',"ulp_thresh"  : '1.0',},
                 'nt2::Zero<T>()' : {"result" :'nt2::One<r_t>()',"ulp_thresh"  : '1.0',},
                },
             'signed_int_' : {
                 'nt2::Mone<T>()' : {"result" :'nt2::Exp_1<r_t>()',"ulp_thresh"  : '1.0',},
                 'nt2::One<T>()' : {"result" :'nt2::Exp_1<r_t>()',"ulp_thresh"  : '1.0',},
                 'nt2::Zero<T>()' :{"result" : 'nt2::One<r_t>()',"ulp_thresh"  : '1.0',},
                },
             'unsigned_int_' : {
                 'nt2::One<T>()' : {"result" :'nt2::Exp_1<r_t>()',"ulp_thresh"  : '1.0',},
                 'nt2::Zero<T>()' :{"result" : 'nt2::One<r_t>()',"ulp_thresh"  : '1.0',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'real_' : ['nt2::log(nt2::expx2(nt2::sqrt(a0)))'],
                },
             'property_value' : {
                 'real_' : ['a0'],
                },
             'ulp_thresh' : {
                 'default' : ['7'],
                },
            },
        },
     'version' : '0.1',
    },
]
