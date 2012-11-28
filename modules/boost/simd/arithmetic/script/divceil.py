[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['return the \c ceil of the operands real division'
                          'in the input type'],
         'module' : 'boost',
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::common_type<T,T>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 01/12/2010',
             'included' : ['#include <boost/simd/include/functions/ceil.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 13/12/2010',
            },
         'ranges' : {
             'real_' : [['T(-10)', 'T(10)'], ['T(-10)', 'T(10)']],
             'signed_int_' : [['-100', '100'], ['-100', '100']],
             'unsigned_int_' : [['0', '100'], ['0', '100']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'T(4),T(3)' : '2',
                 'T(4),T(0)' : 'boost::simd::Inf<r_t>()',
                 'boost::simd::Inf<T>()' : 'boost::simd::Nan<r_t>()',
                 'boost::simd::Minf<T>()' : 'boost::simd::Nan<r_t>()',
                 'boost::simd::Mone<T>()' : 'boost::simd::One<r_t>()',
                 'boost::simd::Mone<T>(),boost::simd::Zero<T>()' : 'boost::simd::Minf<r_t>()',
                 'boost::simd::Nan<T>()' : 'boost::simd::Nan<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::One<r_t>()',
                 'boost::simd::One<T>(),boost::simd::Zero<T>()' : 'boost::simd::Inf<r_t>()',
                 'boost::simd::Zero<T>(),boost::simd::Zero<T>()' : 'boost::simd::Nan<r_t>()',
                },
             'signed_int_' : {
                 'T(4),T(3)' : '2',
                 'T(4),T(0)' : 'boost::simd::Valmax<r_t>()',
                 'T(-4),T(0)' : 'boost::simd::Valmin<r_t>()',
                 'boost::simd::Mone<T>()' : 'boost::simd::One<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::One<r_t>()',
                },
             'unsigned_int_' : {
                 'T(4),T(0)' : 'boost::simd::Valmax<r_t>()',
                 'T(4),T(3)' : '2',
                 'boost::simd::One<T>()' : 'boost::simd::One<r_t>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::divceil(a0,a1)'],
                },
             'property_value' : {
                 'unsigned_int_' : ['r_t(a1 ? boost::simd::ceil((1.0*a0)/a1) : boost::simd::Valmax<r_t>())'],
                 'signed_int_' : ['r_t(a1 ? boost::simd::ceil((1.0*a0)/a1) : ((a0>0)? boost::simd::Valmax<r_t>(): (a0<0) ? boost::simd::Valmin<r_t>() : 0))'],
                 'real_'   : ['r_t(boost::simd::ceil(a0/a1))'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]
