#! /bin/bash

cwd=`pwd`

function build_for_board()
{
	rm -rf build/

	echo "*************** $1 $2 ***********************"

	#Build steps to build UART Application
	if [[ "$2" == "UART" ]]
	then
		i="../zephyr-ia/samples/intel/uart/"
	fi

	#Build steps to build DMA Application
	if [[ "$2" == "DMA" ]]
	then
		i="../zephyr-ia/samples/intel/dma/"
	fi

	#Build steps to build GPIO Application
	if [[ "$2" == "GPIO" ]]
	then
		i="../zephyr-ia/samples/intel/gpio/"
	fi

	#Build steps to build TGPIO Application
	if [[ "$2" == "TGPIO" ]]
	then
		i="../zephyr-ia/samples/intel/tgpio/"
	fi

	#Build steps to build ETHERNET Application
	if [[ "$2" == "ETHERNET" ]]
	then
		west build -d ../build/echo_server -p -b ehl_crb samples/net/sockets/echo_server \
		-- -DOVERLAY_CONFIG=../../../../../zephyr-iotg/samples/intel/ethernet/echo_server/overlay-ehl.conf \
		-DCONFIG_THREAD_STACK_INFO=n -DCONFIG_THREAD_MONITOR=n -DCONFIG_THREAD_NAME=n -DCONFIG_THREAD_RUNTIME_STATS=n
	fi

	#Build steps to build SPI Application
	if [[ "$2" == "SPI" ]]
	then
		i="../zephyr-ia/samples/intel/spi/spi_loopback/"
	fi

	#Build steps to build PWM Application
	if [[ "$2" == "PWM" ]]
	then
		i="../zephyr-ia/samples/intel/pwm/"
	fi

	#Build steps to build EMMC Application
	if [[ "$2" == "EMMC" ]]
	then
		i="../zephyr-ia/samples/intel/emmc/"
	fi

	#Build steps to build CAN Application
	if [[ "$2" == "CAN" ]]
	then
		i="../zephyr-ia/samples/intel/can/"
	fi

	#Build steps to build SOCKET CAN Application
	if [[ "$2" == "SOCKET_CAN" ]]
	then
		i="../zephyr-ia/samples/intel/socket_can/"
	fi

	#Build steps to build HECI Application
	if [[ "$2" == "HECI" ]]
	then
		i="../zephyr-ia/samples/intel/heci/host/"
	fi

	west build -p auto -b ehl_crb $i | tee result.txt ||:
	cat result.txt >> all_result.txt

	if [ -e "build/zephyr/zephyr.efi" ]
        then
		cp "build/zephyr/zephyr.efi" $cwd/BDBA/zephyr_$2.efi

	else
		echo "BUILD Failed!!!!!"
	fi
}

rm -rf build/
rm -rf result.txt all_result.txt

mkdir $cwd/BDBA

build_for_board "ehl_crb" "UART"
build_for_board "ehl_crb" "DMA"
build_for_board "ehl_crb" "GPIO"
build_for_board "ehl_crb" "TGPIO"
build_for_board "ehl_crb" "ETHERNET"
build_for_board "ehl_crb" "SPI"
build_for_board "ehl_crb" "PWM"
build_for_board "ehl_crb" "EMMC"
build_for_board "ehl_crb" "CAN"
build_for_board "ehl_crb" "SOCKET_CAN"
build_for_board "ehl_crb" "HECI"
