DIR=/bin
if [ ! -d "$DIR" ];
then
	mkdir bin
fi
make tests
./bin/tests