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

./buildroot/output/host/bin/aarch64-linux-gdb -iex "set auto-load safe-path ./buildroot/output/build/linux-custom/" $KERNEL_DEBUG_IMG -x $BASE_DIR/scripts/gdb_cmds.txt