#!/bin/sh

PORT=/dev/ttyACM0

ls -lah images

echo "Copying Mackerel image..."
echo "load 100000" > $PORT
sleep 1
ctt -p $PORT -f images/mackerel.rom

sleep 1
echo "Booting Linux..."
echo "runrom" > $PORT

echo "Done"
