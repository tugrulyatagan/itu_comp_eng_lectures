#!/bin/bash

dpkg -r linux-image-3.8.13.6-custom
dpkg -r linux-headers-3.8.13.6-custom

dpkg -i linux-image-3.8.13.6-custom_3.8.13.6-custom-10.00.Custom_i386.deb
dpkg -i linux-headers-3.8.13.6-custom_3.8.13.6-custom-10.00.Custom_i386.deb

reboot
