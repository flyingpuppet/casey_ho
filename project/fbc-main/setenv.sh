TEST=`which hcac`
if [ -z $TEST ]; then
  TEST=`which arc-elf32-gcc`
  if [ -z $TEST ]; then
    CC_DIR=`dirname $TEST`
    export ARC_COMPILER="GNU"
    export ARC_TOOLCHAIN_PATH=$CC_DIR
    echo "Use GNU toolchain for ARC in $ARC_TOOLCHAIN_PATH."
  else 
    echo "No compiler for ARC find, please install or add PATH of hcac or aec-elf32-gcc."
  fi
else
  CC_DIR=`dirname $TEST`
  export ARC_COMPILER="METAWARE"
  export ARC_TOOLCHAIN_PATH=$CC_DIR
  echo "Use Metaware toolchain for ARC in $ARC_TOOLCHAIN_PATH."
fi
