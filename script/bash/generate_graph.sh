nb_data_types=$1
NUM_TEST=$2
nb_sizes=$3
LEGEND=$4
TITLE=$5
PLOT_NAME=$6
kk=$7

i=0
filename="create_plot${kk}.m"
count=0
for ((jj=0;jj<${NUM_TEST};jj++));do
  for ((ll=1;ll<=${nb_sizes};ll++));do
    ((pos=${jj}*${nb_sizes}*${nb_data_types}+${ll}+${kk}*${nb_sizes}))
    SIZE[count]=$(sed -n ${pos}p res.txt | tr "(" "\n" | tr ")" "\n" | sed -n 2p)
    CYC[count]=$(sed -n ${pos}p res.txt | cut -f3 )
    UNIT=$(sed -n ${pos}p res.txt | cut -f4 | tr " " "\n" | sed -n 1p)
    ((count++))
  done
done

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

echo "hold on" > ${filename}
echo "CYC2=[">>${filename}
for ((ii=10#0;ii<${nb_sizes};ii++));do
  for ((jj=10#0;jj<(${NUM_TEST});jj++));do
    echo ${CYC2[${jj}+${ii}*(${NUM_TEST})]}>>${filename}
  done
done
echo "]">>${filename}
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
  echo ${!var} >> ${filename}
done
echo ${TITLE}  >> ${filename}

X="$X ];"
echo $X>>${filename}

echo "num_y_ticks = round(max(CYC2))">>${filename}
((q=${gap}+1))
echo "num_div=1;">>${filename}

echo "max_y=max(CYC2)*1.2">>${filename}
echo "y_inc = max_y/num_y_ticks">>${filename}
echo "x_points=ones(1,num_y_ticks);">>${filename}
echo "y_points=zeros(1,num_y_ticks);">>${filename}
echo "  y_dist=0.5;">>${filename}
echo "if (max(CYC2)>1000)">>${filename}
echo "  num_div=100;">>${filename}
echo "  y_dist=3;">>${filename}
echo "elseif (max(CYC2)>160)">>${filename}
echo "  num_div=16;">>${filename}
echo "  y_dist=2;">>${filename}
echo "elseif (max(CYC2)>80)">>${filename}
echo "  num_div=8;">>${filename}
echo "elseif (max(CYC2)>40)">>${filename}
echo "  num_div=4;">>${filename}
echo "elseif (max(CYC2)>20)">>${filename}
echo "  num_div=2;">>${filename}
echo "elseif (max(CYC2)>10)">>${filename}
echo "  num_div=1;">>${filename}
echo "endif">>${filename}
echo "num_y_ticks/=num_div;">>${filename}
echo "y_points(1)=y_inc*num_div;">>${filename}
echo "for i=2:num_y_ticks">>${filename}
echo "  y_points(i)=y_points(i-1)+y_inc*num_div;">>${filename}
echo "endfor">>${filename}

echo "w=0.4;">>${filename}

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
    echo "plot(x,cyc${ii},${COLORS[${ii}]},\"linestyle\",'-',\"linewidth\",2);">>${filename}
done

for ((ii=0;ii<${nb_sizes};ii++));do
  for ((jj=${gap}+1;jj<${gap}+(${NUM_TEST});jj++));do
    ((q= ${jj} + 1 + ${ii}*(${gap}+(${NUM_TEST}))))
    ((r=(${ii})*(${gap}+(${NUM_TEST}))+${gap}+1))
  done
done

echo "max_x = max(x)+0.25;">>${filename}
echo ${LEGEND}>>${filename}
echo "xx=[1 max_x max_x 1 1];">>${filename}
echo "text(y_dist,max_y/2-num_div,\"${UNIT}\",\"rotation\",90)">>${filename}
echo "yy=[0 0 max_y max_y 0];">>${filename}
echo "plot(xx,yy,'k')">>${filename}
echo "ylim([-num_div*0.5 max_y])">>${filename}
echo "axis off" >>${filename}
echo "xlim([0.5 max_x]);">>${filename}

for ((ii=1;ii<=${nb_sizes};ii++));do
  echo "text(x(${ii}),-num_div*0.3,\"${SIZE[ii-1]}\")">>${filename}
done

echo "box on" >>${filename}
echo "plot(x_points,y_points,'+k')" >>${filename}
echo "for i=1:num_y_ticks" >>${filename}
echo "  text(0.75,y_points(i),mat2str(i*num_div));" >>${filename}
#echo "  text(x_points(i)-0.1,y_points(i),\"potato\");" >>${filename}
echo "endfor" >>${filename}
echo "print ('-dpng','-color',\"${PLOT_NAME}.png\")">>${filename}
echo "h = figure;">>${filename}
echo "W = 12; H = 3;">>${filename}
echo "set(h,'PaperUnits','inches')">>${filename}
echo "set(h,'PaperOrientation','portrait');">>${filename}
echo "set(h,'PaperSize',[H,W])">>${filename}
echo "set(h,'PaperPosition',[0,0,W,H])">>${filename}
echo "refresh">>${filename}

octave ${filename} &>  /dev/null; display "${PLOT_NAME}.png" &
