#!/bin/bash

print_mem_used() {
	local mem_used="$(free -m | awk 'NR==2 {print $3}')"
	local mem_total="$(free -m | awk 'NR==2 {print $2}')"
	let mem_used="100 * $mem_used / $mem_total"
	printf "Þ%3s" $mem_used
}

print_volume() {
	local volume="$(amixer get PCM | tail -n1 | sed -r 's/.*\[(.*)%\].*/\1/')"
	volume=$(printf "%3s" $volume)
	if [[ $volume -le 0 ]]; then
		echo -ne "ñ$volume"
	elif [[ $volume -le 40 ]]; then
		echo -ne "ò$volume"
	elif [[ $volume -le 80 ]]; then
		echo -ne "ó$volume"
	else
		echo -ne "ô$volume"
	fi
}

function float_eval() {
	local stat=0
	local result=0.0
	if [[ $# -gt 0 ]]; then
		result=$(echo "scale=3; $*" | bc -q 2>/dev/null)
		stat=$?
		if [[ $stat -eq 0 && -z "$result" ]]; then stat=1; fi
	fi
	echo $result
	return $stat
}

function float_cond() {
	local cond=0
	if [[ $# -gt 0 ]]; then
		cond=$(echo "$*" | bc -q 2>/dev/null)
		if [[ -z "$cond" ]]; then cond=0; fi
		if [[ "$cond" != 0 && "$cond" != 1 ]]; then cond=0; fi
	fi
	local stat=$((cond == 0))
	return $stat
}

print_suffixed() {
	if [[ $# -lt 1 || $1 -lt 0 ]]; then
		echo -ne "ERROR"
		return
	fi
	local val=$1
	local suf="á"
	if float_cond "$val >= 1000"; then
		val=$(float_eval "$val / 1024")
		suf="â"
	fi
	if float_cond "$val >= 1000"; then
		val=$(float_eval "$val / 1024")
		suf="ã"
	fi
	if float_cond "$val >= 1000"; then
		echo -ne ">9000"
		return
	fi
	if float_cond "$val >= 100"; then
		printf "%.3s$suf" $val
	else
		val="${val%.*}à${val##*.}"
		printf "%5.5s$suf" $val
	fi
}

print_datetime() {
	echo -ne "$(date "+%a %d Ý %H:%M")"
}

rx_old=0
tx_old=0

while true; do
	# get new cpu idle and total usage
	eval $(awk '/^cpu /{print "cpu_idle_now=" $5 "; cpu_total_now=" $2+$3+$4+$5 }' /proc/stat)
	cpu_interval=$((cpu_total_now-${cpu_total_old:-0}))
	# calculate cpu usage (%)
	let cpu_used="100 * ($cpu_interval - ($cpu_idle_now-${cpu_idle_old:-0})) / $cpu_interval"

	rx_now=0
	tx_now=0
	for i in /sys/class/net/*; do
		if [[ -d "$i" && ${i##*/} != "lo" ]]; then
			if [[ -f "$i/statistics/rx_bytes" ]]; then
				let rx_now=($rx_now+`cat $i/statistics/rx_bytes`)
			fi
			if [[ -f "$i/statistics/tx_bytes" ]]; then
				let tx_now=($tx_now+`cat $i/statistics/tx_bytes`)
			fi
		fi
	done
	let rx_rate=($rx_now-$rx_old)
	let tx_rate=($tx_now-$tx_old)

	# output vars
	print_cpu_used() { printf "Ï%3s" $cpu_used; }
	print_rx_rate() { echo -ne "Ð$(print_suffixed $rx_rate)"; }
	print_tx_rate() { echo -ne "Ñ$(print_suffixed $tx_rate)"; }

	# Pipe to status bar, not indented due to printing extra spaces/tabs
	xsetroot -name "\
û$(print_rx_rate) $(print_tx_rate)\
û$(print_cpu_used)\
û$(print_mem_used)\
û$(print_volume)\
û$(print_datetime)"

	# reset old rates
	rx_old=$rx_now
	tx_old=$tx_now
	cpu_idle_old=$cpu_idle_now
	cpu_total_old=$cpu_total_now
	# loop stats every 1 second
	sleep 1
done

