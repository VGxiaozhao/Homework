#! /bin/bash  

function GetIPByMAC()
{
	mac1=$1;
	mac=`echo ${mac1//:/}`;		#去除冒号
	res=`arp -a | awk 'gsub(/\(/,b)gsub(/\)/,b)gsub(/:/,b) {print $4,$2} ' | grep $mac | awk '{print $2}'`;
	echo $res;
}

function GetIPMACByFile()
{
	filename=$1;
	res=`cat $filename|awk 'gsub(/\(/,b)gsub(/\)/,b)gsub(/:/,b) {print $4, $2}'`
	echo $res;
}

#read -p "请输入MAC地址,支持模糊查询:" n;  
#GetIPByMAC $n;

#read -p "请输入文件名:" n; 
#GetIPMACByFile $n;
