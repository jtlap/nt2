[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' :['base two exponential function: \f$2^{a_0}\f$','\par',
                         'provisions are made for otaining a flint result from a flint input'] ,  
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_floating<T>::type',
            },
         'type_defs' : ['#include <nt2/include/functions/sqr.hpp>'],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
         'simd_types' :    ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 08/12/2010',
             'cover_included' : 
                ['#include <nt2/include/functions/exp2.hpp>',
                 '#include <nt2/include/functions/log2.hpp>',
                 '#include <nt2/include/functions/abs.hpp>',
                  'extern "C" { long double cephes_exp2l(long double); }'],
             'notes' : [],
             'stamp' : 'modified by jt the 15/12/2010',
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
                 'nt2::Inf<T>()' : 'nt2::Inf<r_t>()',
                 'nt2::Minf<T>()' : 'nt2::Zero<r_t>()',
                 'nt2::Mone<T>()' : 'nt2::Half<r_t>()',
                 'nt2::Nan<T>()' : 'nt2::Nan<r_t>()',
                 'nt2::One<T>()' : 'nt2::Two<r_t>()',
                 'nt2::Zero<T>()' : 'nt2::One<r_t>()',
                },
             'signed_int_' : {
                 'nt2::Mone<T>()' : 'nt2::Half<r_t>()',
                 'nt2::One<T>()' : 'nt2::Two<r_t>()',
                 'nt2::Zero<T>()' : 'nt2::One<r_t>()',
                },
             'unsigned_int_' : {
                 'nt2::One<T>()' : 'nt2::Two<r_t>()',
                 'nt2::Zero<T>()' : 'nt2::One<r_t>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::exp2(a0)'],#,'nt2::log2(nt2::exp2(a0))', 'nt2::log2(nt2::sqr(a0))'],
                },
             'property_value' : {
                 'default' : ['cephes_exp2l(a0)'],#,'r_t(a0)', '2*log2(nt2::abs(a0))'],
                },
             'ulp_thresh' : {
                 'default' : ['7','11', '7'],
                },
            },
        },
     'version' : '0.1',
    },
]
