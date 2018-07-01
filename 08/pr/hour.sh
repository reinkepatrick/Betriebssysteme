if [ $(date '+%H') -ge 0 ] && [ $(date '+%H') -lt 12 ]; then
	echo "Guten Morgen $(whoami)"
elif [ $(date '+%H') -ge 12 ] && [ $(date '+%H') -lt 17 ]; then
	echo "Guten Tag $(whoami)"
else
	echo "Guten Abend $(whoami)"
fi
