if [ $# != 1 ]; then
    echo "error plz pass 1 arg that is nic if name"
    exit
fi

if ! test -d /sys/class/net/$1/statistics; then
    echo "error invalid nic name"
    exit
fi

