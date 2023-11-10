# Check that env_init is sourced
if [ -z "$ENV_INIT" ]
then
    echo ""
    echo "Please source env_init.sh"
    echo ""
    exit
fi

if [ $# != 1 ]; then
    echo "error usage ./rebuild_app <app>"
    exit
fi

if [ $PWD != $BASE_DIR ] ;
then
    echo "Please run from ${BASE_DIR}"
    exit
fi

# delete indicated apps source and rootfs
rm -r ${BUILDROOT_DIR}/output/build/$1-*
rm -r ${ROOTFS}

# delete metadata
rm -rf ${BUILDROOT_DIR}/package/$1

# copy meta data
mkdir ${BUILDROOT_DIR}/package/$1
cp ${USERSPACE_APPS_DIR}/$1/Config.in  ${BUILDROOT_DIR}/package/$1/Config.in
cp ${USERSPACE_APPS_DIR}/$1/$1.mk  ${BUILDROOT_DIR}/package/$1/$1.mk

#rebuild
cd ${BUILDROOT_DIR}
make $1
make
cd ..