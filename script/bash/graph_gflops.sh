#!/bin/bash
FIRST=0
LAST=$#
args=( "$@" )

if [ "$1" == "-s" ];then
  run=$2
  ((FIRST=${FIRST}+2))
else
  run=""
fi

var=args[${FIRST}]
while [ ${!var} == "-o" ];do
  var1=args[${FIRST}+1]
  var2=args[${FIRST}+2]
  RUN_ARGS=("${RUN_ARGS} ${!var} ${!var1} ${!var2}")
  ((FIRST=${FIRST}+3))
  var=args[${FIRST}]
done

((NUM_TEST=${LAST}-${FIRST}))

var=args[${FIRST}]
if [ "$1" == "arm" ];then
  ${run} ./${!var} "${RUN_ARGS}" | tee res.txt
else
  ${run} ./${!var} ${RUN_ARGS} | tee res.txt
fi
sed 1,4d res.txt > temp.txt; mv temp.txt res.txt
nb_sizes=$(cat res.txt | wc -l)

EXTENSION=$(head -n 1 res.txt  |  tr "_"  "\n" | sed 1d  | tr "<" "\n" | sed -n 1p)
LEGEND="legend(\"${EXTENSION}\" "

BENCH_NAME=$(head -n 1 res.txt | tr "_"  "\n"|sed -n 1p)
TYPE=$(head -n 1 res.txt | tr "_"  "\n" | sed 1d | tr "<" "\n" | tr ">" "\n" | sed -n 2p)
for ((i=${FIRST}+1;i<${LAST};i++));do
    var=args[${i}]
    if [ "$1" == "arm" ];then
      ${run} ./${!var} "${RUN_ARGS}" | sed 1,4d  | tee temp.txt; cat temp.txt >> res.txt
    else
      ${run} ./${!var} ${RUN_ARGS} | sed 1,4d  | tee temp.txt; cat temp.txt >> res.txt
    fi
    EXTENSION=$(dirname "$(dirname -- "$(dirname -- "${!var}")")")
    TEMP=$(head -n 1 temp.txt |   tr "_"  "\n" | sed 1d | tr "<" "\n" | sed -n 1p)
    if [ "${TEMP}" == "mkl" ];then
      EXTENSION="mkl"
    fi
    if [ "${TEMP}" == "nt2" ];then
      EXTENSION="${EXTENSION} nt2"
    fi
    LEGEND="${LEGEND} ,\"${EXTENSION}\" "
done
LEGEND="${LEGEND} )"

TITLE="title("
TITLE="${TITLE}\"${BENCH_NAME} ${TYPE}"
TITLE="${TITLE}\" )"

i=0
while read p; do
  SIZE[i]=$(echo $p | tr "(" "\n" | tr ")" "\n" | sed -n 2p)
  CYC[i]=$(echo $p | awk  '{ print $3 }')
  UNIT=$(echo $p | awk '{print $4 }')
  ((i++))
done < res.txt

for ((ii=10#0;ii<${nb_sizes};ii++));do
  for ((jj=10#0;jj<(${NUM_TEST});jj++));do
    q=(${ii}+${jj}*${nb_sizes})
    CYC2[${jj}+${ii}*(${NUM_TEST})]=${CYC[q]}
  done
done

for ((ii=0;ii<${nb_sizes};ii++));do
  declare "cyc${ii}=cyc${ii}"
done
((size_x_axis=${nb_sizes}))
for ((ii=0;ii<${NUM_TEST};ii++));do
  eval cyc${ii}='cyc${ii}=['
done

echo "hold on" > create_plot.m
echo "CYC2=[">>create_plot.m
for ((ii=10#0;ii<${nb_sizes};ii++));do
  for ((jj=10#0;jj<(${NUM_TEST});jj++));do
    echo ${CYC2[${jj}+${ii}*(${NUM_TEST})]}>>create_plot.m
  done
done
echo "]">>create_plot.m
X="x=["

for ((i = 1 ; i <= ${size_x_axis} ; i++)); do
  X="$X $i"
done
for ((ii=10#0;ii<(${NUM_TEST});ii++));do
  for ((jj=10#0;jj<${nb_sizes};jj++));do
    ((q= ${jj} + ${ii}*${nb_sizes}))
    var=cyc${ii}
    temp="${!var} ${CYC[${q}]}"
    eval cyc${ii}='$temp'
    var=cyc${ii}
  done
done

for ((ii=0;ii<${NUM_TEST};ii++));do
  var=cyc${ii}
  temp="${!var} ]"
  eval cyc${ii}='$temp'
done

for ((ii=10#0;ii<(${NUM_TEST});ii++));do
  var=cyc${ii}
  echo ${!var} >> create_plot.m
done

echo ${TITLE}  >> create_plot.m

X="$X ];"
echo $X>>create_plot.m

echo "num_y_ticks = round(max(CYC2))">>create_plot.m
((q=${gap}+1))
echo "num_div=1;">>create_plot.m

echo "max_y=max(CYC2)*1.2">>create_plot.m
echo "y_inc = max_y/num_y_ticks">>create_plot.m
echo "x_points=ones(1,num_y_ticks);">>create_plot.m
echo "y_points=zeros(1,num_y_ticks);">>create_plot.m
echo "if (max(CYC2)>1000)">>create_plot.m
echo "  num_div=100;">>create_plot.m
echo "elseif (max(CYC2)>160)">>create_plot.m
echo "  num_div=16;">>create_plot.m
echo "elseif (max(CYC2)>80)">>create_plot.m
echo "  num_div=8;">>create_plot.m
echo "elseif (max(CYC2)>40)">>create_plot.m
echo "  num_div=4;">>create_plot.m
echo "elseif (max(CYC2)>20)">>create_plot.m
echo "  num_div=2;">>create_plot.m
echo "elseif (max(CYC2)>10)">>create_plot.m
echo "  num_div=1;">>create_plot.m
echo "endif">>create_plot.m
echo "num_y_ticks/=num_div;">>create_plot.m
echo "y_points(1)=y_inc*num_div;">>create_plot.m
echo "for i=2:num_y_ticks">>create_plot.m
echo "  y_points(i)=y_points(i-1)+y_inc*num_div;">>create_plot.m
echo "endfor">>create_plot.m

echo "w=0.4;">>create_plot.m

COLORS[0]=" '+r' "
COLORS[1]=" '+g' "
COLORS[2]=" '+b' "
COLORS[3]=" '+c' "
COLORS[4]=" '+y' "
COLORS[5]=" \"+4\" "
COLORS[6]=" '+','color',[255/255,140/255,0] "
COLORS[7]=" '+','color',[0,0,0] "
COLORS[8]=" '+','color',[34/255,139/255,34/255] "
COLORS[9]=" '+','color',[218/255,165/255,32/255] "
COLORS[10]=" '+','color',[255/255,140/255,0] "
j=0
for ((ii=0;ii<(${NUM_TEST});ii++));do
    echo "plot(x,cyc${ii},${COLORS[${ii}]},\"linestyle\",'-',\"linewidth\",2);">>create_plot.m
done

for ((ii=0;ii<${nb_sizes};ii++));do
  for ((jj=${gap}+1;jj<${gap}+(${NUM_TEST});jj++));do
    ((q= ${jj} + 1 + ${ii}*(${gap}+(${NUM_TEST}))))
    ((r=(${ii})*(${gap}+(${NUM_TEST}))+${gap}+1))
  done
done

echo "max_x = max(x);">>create_plot.m
echo ${LEGEND}>>create_plot.m
echo "xx=[1 max_x max_x 1 1];">>create_plot.m
echo "text(0.8,max_y/2-num_div,\"${UNIT}\",\"rotation\",90)">>create_plot.m
echo "yy=[0 0 max_y max_y 0];">>create_plot.m
echo "plot(xx,yy,'k')">>create_plot.m
echo "ylim([-num_div*0.5 max_y])">>create_plot.m
echo "axis off" >>create_plot.m
echo "xlim([0.75 max_x]);">>create_plot.m

for ((ii=1;ii<=${nb_sizes};ii++));do
  echo "text(x(${ii}),-num_div*0.3,\"${SIZE[ii-1]}\")">>create_plot.m
done

echo "box on" >>create_plot.m
echo "plot(x_points,y_points,'+k')" >>create_plot.m
echo "for i=1:num_y_ticks" >>create_plot.m
echo "  text(x_points(i)-0.1,y_points(i),mat2str(i*num_div));" >>create_plot.m
echo "endfor" >>create_plot.m
echo "print ('-dpng','-color',\"${BENCH_NAME}.png\")">>create_plot.m
echo "h = figure;">>create_plot.m
echo "W = 12; H = 3;">>create_plot.m
echo "set(h,'PaperUnits','inches')">>create_plot.m
echo "set(h,'PaperOrientation','portrait');">>create_plot.m
echo "set(h,'PaperSize',[H,W])">>create_plot.m
echo "set(h,'PaperPosition',[0,0,W,H])">>create_plot.m
echo "refresh">>create_plot.m

octave create_plot.m &>  /dev/null; display "${BENCH_NAME}.png" &
