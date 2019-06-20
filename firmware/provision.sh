#!/usr/bin/env bash

export ZSDK_VERSION=0.10.0
export GCC_ARM_NAME=gcc-arm-none-eabi-7-2018-q2-update

## Provision an Ubuntu machine for C++ development.
##
apt-get update
apt-get install -y g++ cmake gdb gdbserver

dpkg --add-architecture i386
apt-get -y update
apt-get -y upgrade

apt-get install --no-install-recommends -y gnupg  ca-certificates
apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 3FA7E0328081BFF6A14DA29AA6A19B38D3D831EF

echo "deb https://download.mono-project.com/repo/ubuntu stable-bionic main" | tee /etc/apt/sources.list.d/mono-official-stable.list
apt-get -y update

apt-get install --no-install-recommends -y \
	autoconf \
	automake \
	build-essential \
	ccache \
	device-tree-compiler \
	dfu-util \
	doxygen \
	file \
	g++ \
	gcc \
	gcc-multilib \
	gcovr \
	git \
	git-core \
	gperf \
	gtk-sharp2 \
	iproute2 \
	lcov \
	libglib2.0-dev \
	libgtk2.0-0 \
	libpcap-dev \
	libsdl2-dev:i386 \
	libtool \
	locales \
	make \
	mono-complete \
	net-tools \
	ninja-build \
	openbox \
	pkg-config \
	python3-pip \
	python3-ply \
	python3-setuptools \
	python-xdg \
	qemu \
	socat \
	sudo \
	texinfo \
	valgrind \
	wget \
	x11vnc \
	xvfb \
	xz-utils

wget -O dtc.deb http://security.ubuntu.com/ubuntu/pool/main/d/device-tree-compiler/device-tree-compiler_1.4.7-1_amd64.deb
dpkg -i dtc.deb

wget -O jlink.deb --post-data="non_emb_ctr=confirmed&accept_license_agreement=accepted&submit=Download software" https://www.segger.com/downloads/jlink/JLink_Linux_x86_64.deb
dpkg -i jlink.deb

wget -O renode.deb https://github.com/renode/renode/releases/download/v1.6.2/renode_1.6.2_amd64.deb
apt install -y ./renode.deb

wget -q "https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v${ZSDK_VERSION}/zephyr-sdk-${ZSDK_VERSION}-setup.run" && \
	sh "zephyr-sdk-${ZSDK_VERSION}-setup.run" --quiet -- -d /opt/toolchains/zephyr-sdk-${ZSDK_VERSION} && \
	rm "zephyr-sdk-${ZSDK_VERSION}-setup.run"

wget -q https://raw.githubusercontent.com/zephyrproject-rtos/zephyr/master/scripts/requirements.txt && \
	pip3 install wheel &&\
	pip3 install -r requirements.txt && \
	pip3 install west &&\
	pip3 install sh

wget -q https://developer.arm.com/-/media/Files/downloads/gnu-rm/7-2018q2/${GCC_ARM_NAME}-linux.tar.bz2  && \
	tar xf ${GCC_ARM_NAME}-linux.tar.bz2 && \
	rm -f ${GCC_ARM_NAME}-linux.tar.bz2 && \
	mv ${GCC_ARM_NAME} /opt/toolchains/${GCC_ARM_NAME}

wget -q https://github.com/Kitware/CMake/releases/download/v3.13.2/cmake-3.13.2-Linux-x86_64.sh && \
	chmod +x cmake-3.13.2-Linux-x86_64.sh && \
	./cmake-3.13.2-Linux-x86_64.sh --skip-license --prefix=/usr/local && \
	rm -f ./cmake-3.13.2-Linux-x86_64.sh

echo "export ZEPHYR_TOOLCHAIN_VARIANT=zephyr" >> /etc/profile
echo "export ZEPHYR_SDK_INSTALL_DIR=/opt/toolchains/zephyr-sdk-${ZSDK_VERSION}" >> /etc/profile
echo "export ZEPHYR_BASE=/workdir" >> /etc/profile
echo "export GNUARMEMB_TOOLCHAIN_PATH=/opt/toolchains/${GCC_ARM_NAME}" >> /etc/profile
echo "export PKG_CONFIG_PATH=/usr/lib/i386-linux-gnu/pkgconfig" >> /etc/profile
echo "export DISPLAY=:0" >> /etc/profile
echo "export ZEPHYR_BASE=/home/vagrant/code/zephyr" >> /etc/profile
