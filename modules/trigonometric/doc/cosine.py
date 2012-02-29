[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' :['templated cosine.','\par',
                         'cosine is a templated version of cos',
                         'the template parameter T is a mode that allows some control on the computation',
                         'accuracy','\par',
                         'In fact the control is on the reduction routine of the angle to the',
                         '\\\\f$[-\pi/4, \pi/4]\\\\f$ interval',
                         'they actually are 3 reduction routines protocol that respectly are',
                         'sufficient for small, medium and big angle values to have within',
                         'cover test one ulp of difference with the according crlibm result.',
                         '\par',
                         'Each one covers respectively intervals \\\\f$[-A, A]\\\\f$ with :',
                         '\\\\verbatim',
                         '|--------------|-------------------|----------------|',
                         '|              |   float  A        |  double  A     |',
                         '|--------------|-------------------|----------------|',
                         '|    small     |   20*pi           | 20*pi          |',
                         '|--------------|-------------------|----------------|',
                         '|    medium    |   2^6*pi          | 2^18*pi        |',
                         '|--------------|-------------------|----------------|',
                         '|    big       |   Inf<float>      |  Inf<double>   |',
                         '|--------------|------------------------------------|',
                         '\endverbatim',
                         'In fact for each scalar singleton or simd vector of angles',
                         'There are two possibilities :',
                         '\\\\arg one is to test if all vector element(s) are in the proper range',
                         'for the consecutive increasing values of A until we reach a good',
                         'one or the last :',
                         'the corresponding template tags are small, medium and big',
                         '\\\\arg the second is to force directly a reduction method',
                         'The corresponding template tags are direct_small, direct_medium',
                         'and direct_big','\par',
                         'direct_small is NOT equivalent to small because there are also',
                         'two other methods for \\\\f$[0, \pi/4]\\\\f$ (no reduction)',
                         'and \\\\f$[\pi/4, \pi/2]\\\\f$',
                         '(straight reduction) that are not considered in direct small',
                         '\par',
                         'Note that for float the big case is both early an hyper costly and',
                         'shall be avoided whenever possible. To partially achieve this aim',
                         'when double are available on the platform, this part of reduction',
                         'is delegated to the double precision routines.',
                         '\par Advices',
                         '\\\\arg If there is no restrictions ever on your angles and you care for precision',
                         'use nt2::cosine<big> which is equivalent to nt2::cos',
                         '\\\\arg if you do not care for precision you can use',
                         'nt2::cosine<medium> or nt2::cosine<small>',
                         'that will be accurate for their proper range and degrade',
                         'with greater values',
                         '\par',
                         'Now, the choice of direct or not relies on probabilities',
                         'computations:',
                         'assuming that a vector contains k elements and that testing all',
                         'values that are in an interval takes c cycles and the probability of a value',
                         'to be in interval \\\\f$[a, b]\\\\f$ is \\\\f$p(a, b)\\\\f$',
                         'the number of cycles used by a',
                         '\\\\f$direct_i\\\\f$ method is simply the reduction time:',
                         '\\\\f[N(direct_i)\\\\f]',
                         'On the other side the number of cycles for the non-direct methods will have a more',
                         'complicated expression :',
                         '\\\\f[\sum_{i=1}^{m} p(Ai-1, A_i)^k N(direct_i)\\\\f]',
                         'So the non direct methods will be interesting only if you want accurate',
                         'results everywhere and have anyhow a big proportion of small angles.',
                         'This is even more true (if possible) in simd and the more k is big, because',
                         'of the kth power',
                         '\par'
                         'For instance in the medium float case:',
                         '\\\\arg  if angles are equidistributed  on \\\\f$[0 2^16*\pi]\\\\f$,',
                         'the \\\\f$p(0, 20*\pi)\\\\f$ will be',
                         'less than \\\\f$2^11\\\\f$ and thus in sse2 there will be 1 quadruple over',
                         '1.76e+13 falling in the small case...',
                         'Even sorting will do no good because the sort cost will be against ',
                         'the ratio of 1 successful quadruplet over 2048.',
                         '\\\\arg  Contrarily if your angles have a gaussian distribution with 0 mean and',
                         '\\\\f$10\pi\\\\f$ standard deviation,  80% of the intervals will be in the "small"',
                         'case (95% of the values).',
                         '\\\\arg Finally for those that are sure of their angles taking place in a fixed',
                         'range and want speed, three other template tags can be of choice:',
                         '            clipped_pio4,  clipped_small and clipped_medium',
                         'they use the fastest adapted reduction and return Nan for any outsider.',
                         'cosine<clipped_pio4> have a perhaps still faster equivalent the non template',
                         'nt2::fast_cos. ',      
                         ],
##//////////////////////////////////////////////////////////////////////////////
##/*
##  for float values exhaustive test have been taken. All the values has been
##  compared to the call to crlibm with the rounded to nearest cosine function
##  provided by the library for double entries. I.E. nt2::cos(a0) is compared
##  to float(nt2::crlibm::cos_rn(double(a0))). The results are the following :

##  **********************************************************************
##  * range      *  nb of values *   0 ulp    *  0.5 ulp  * 1 ulp * 27ulp*
##  **********************************************************************
##  * [0, pi/4]  *  1061752796   * 1060453284 *  1299512  *   0   *   0  * 
##  **********************************************************************
##  * [0, 20*pi] *  1115378643   * 1103886629 * 11491888  *  1260 *   0  *
##  **********************************************************************
##  * [0, 64*pi] *  1128861660   * 1114841922 * 14018389  *  1330 *  19  *
##  **********************************************************************
##1128861660
##for a0 = 64.40264893 error if of 1.5 ulps
##for a0 = 83.2522049 error if of 3 ulps
##for a0 = 86.39379883 error if of 1.5 ulps
##for a0 = 98.96016693 error if of 1.5 ulps
##for a0 = 102.1017609 error if of 4.5 ulps
##for a0 = 105.2433548 error if of 2.5 ulps
##for a0 = 117.8097229 error if of 1.5 ulps
##for a0 = 120.9513168 error if of 6 ulps
##for a0 = 124.0929108 error if of 3.5 ulps
##for a0 = 139.8008728 error if of 8.5 ulps
##for a0 = 146.0840607 error if of 1.5 ulps
##for a0 = 155.5088348 error if of 2.5 ulps
##for a0 = 161.7920227 error if of 3 ulps
##for a0 = 168.0752106 error if of 1.5 ulps
##for a0 = 171.2167969 error if of 1.5 ulps
##for a0 = 177.4999847 error if of 27 ulps
##for a0 = 183.7831726 error if of 2 ulps
##for a0 = 193.2079468 error if of 4 ulps
##for a0 = 199.4911346 error if of 4 ulps

##1114841922 values with error less than 0 ulp(s)
##14018389 values with error less than 0.5 ulp(s)
##1330 values with error less than 1 ulp(s)
##7 values with error less than 1.5 ulp(s)
##1 values with error less than 2 ulp(s)
##2 values with error less than 2.5 ulp(s)
##2 values with error less than 3 ulp(s)
##1 values with error less than 3.5 ulp(s)
##2 values with error less than 4 ulp(s)
##1 values with error less than 4.5 ulp(s)
##3 values with error bigger than 5 ulp(s)

##Other test with cosine<direct_small> on all float values
##between 0 and 80.5*pi (that means 1132258802 values)
##we have
##           1106449463 values equal to crlibm value
##             25804651 values at 0.5 ulp
##                 4687 values at 1   ulp
##        1 value  at 11  ulps for 80.5*pi

##  */ 
##//////////////////////////////////////////////////////////////////////////////
         'template' : True ,  
         'param_0' : ['angle in radian'],
         'param_t' : ['used to control accuracy and speed'],   
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_floating<T>::type',
            },
         'simd_types' : ['real_'],
         'special' : ['trigonometric'],
         'tpl'   : '<nt2::medium>',   
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 11/02/2011',
             'included' : ['#include <nt2/toolbox/trigonometric/constants.hpp>',
                 'extern "C" {extern long double cephes_cosl(long double);}'],
             'notes' : [],
             'stamp' : 'modified by jt the 11/02/2011',
            },
         'ranges' : {
             'default' : [['T(-60)', 'T(60)']],
             'real_' : [['-20*nt2::Pi<T>()', '20*nt2::Pi<T>()']],
             'signed_int_' : [['T(-40)', 'T(40)']],
             'unsigned_int_' : [['T(0)', 'T(40)']],
            },
         'specific_values' : {
             'default' : {
                 'nt2::Zero<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0.5',},
                },
             'real_' : {
                 '-nt2::Pi<T>()' : {'result' : 'nt2::Mone<r_t>()','ulp_thresh' : '0.5',},
                 '-nt2::Pi<T>()/T(2)' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                 '-nt2::Pi<T>()/T(4)' : {'result' : 'nt2::Sqrt_2o_2<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Inf<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Minf<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Nan<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Pi<T>()' : {'result' : 'nt2::Mone<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Pi<T>()/T(2)' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Pi<T>()/T(4)' : {'result' : 'nt2::Sqrt_2o_2<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0.5',},
                },
             'signed_int_' : {
                 'nt2::Zero<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'real_' : ['nt2::cosine<nt2::medium>(a0)'],
                },
             'property_value' : {
                 'real_' : ['::cephes_cosl(a0)'],
                },
             'ulp_thresh' : {
                 'real_' : ['0.5'],
                },
            },
        },
    },
]
