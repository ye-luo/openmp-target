for folder in [0-9]-*
do
  cd $folder
  make clean; make ENABLE_CXX=1 ENABLE_FC=1
  cd ..
done
