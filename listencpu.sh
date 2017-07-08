#!/bin/bash

function GetSysCPU
{
CpuIdle=`vmstat 1 5 | sed -n '3,$p' | awk '{x = x + $15} END {print x/5}' | awk -F. '{print $1}' `
CpuNum=`echo "100-$CpuIdle" | bc`
echo $CpuNum
}

NUM=3
export LOGNAME=ZhengYuan_vmware #给环境变量 LOGNAME 赋值
while [ $NUM -gt 0 ]; do #循环判断 3 次
	CPU=`GetSysCPU`
	DATE=`date`
	if [ $CPU -gt 90 ]; then #CPU 负载值大于 90
		RESULT=2
		(
			MAC=`ifconfig | grep -m 1 -w "硬件地址" | awk '{print $5}'`
			echo "CPU High Using Waring!the logname is:$LOGNAME ***the MAC of this pc is:$MAC***the system is:$DATE" >> log
		)

	elif [ $CPU -lt 10 ]; then #CPU 负载值小于 10
		RESULT=0
		(
			MAC=`ifconfig | grep -m 1 -w "硬件地址" | awk '{print $5}'`
			echo "CPU Low Using Waring!the logname is:$LOGNAME ***the MAC of this pc is:$MAC***the system is:$DATE" >> log
		)
	else #正常的 CPU 负载值
		RESULT=1
	fi
	case $RESULT in
	"2" )
	printf "Hello %s,The Usage Of System Cpu Is %s, Too High!\nSystem Date is:%s\n""$LOGNAME" "$CPU" "$(DATE)" #CPU 负载过高提示
	;;
	"0" )
	echo -e "Hello $LOGNAME,The Usage Of System Cpu Is $CPU, Too Low!\nSystem Date is:$DATE" #CPU 负载过低提示
	;;
	"1" )
	echo -e "Hello $LOGNAME,The Usage Of System Cpu Is $CPU, Normal!\nSystem Date Is:$DATE"
	;;
	* )
	;;
	esac #根据不同的负载情况分别向系统管理员打印相应情况 
NUM=`expr $NUM - 1` #NUM-1
sleep 5 #休眠 5 秒
done
