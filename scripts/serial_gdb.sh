# Check that env_init is sourced
if [ -z "$ENV_INIT" ]
then
    echo ""
    echo "Please source env_init.sh"
    echo ""
    exit
fi

# Check base dir
if [ $PWD != $BASE_DIR ] ;
then
    echo "Please run from ${BASE_DIR}"
    exit
fi

read -p 'Have you booted and logged into device? (y/n): ' build
if [ "$build" = "y" ]; then
    minicom -S ./scripts/minicom_gdb_startup.txt < ./scripts/escape.txt
else
    echo "Please log in.."
    exit
fi

