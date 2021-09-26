#Make a build directory and move to it
mkdir build && cd ./build

#Generate the make files into the build directory
cmake -S ../ -B ./

#Make
make

#Move the executable to the app directory
mv Rhythm_Tool ../

#Move out of the build directory
cd ../

#Remove the build directory
rm -r ./build