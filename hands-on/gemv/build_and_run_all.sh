for folder in [0-9]-*
do
  cd $folder
  echo ------------ $folder ----------------
  make clean
  echo -- CXX --
  make ENABLE_CXX=1
  echo -- FC --
  make ENABLE_FC=1
  echo
  cd ..
done
