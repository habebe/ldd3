# ztop_hello_world example

sudo insmod ztop_hello_world.ko 

dmesg | grep ztop
lsmod | grep ztop_hello_world
modinfo ztop_hello_world.ko
sudo rmmod ztop_hello_world.ko
lsmod | grep ztop_hello_world
