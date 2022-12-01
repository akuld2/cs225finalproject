DIR=/bin
if [ ! -d "$DIR" ];
then
	mkdir bin
fi
make exec
./bin/exec