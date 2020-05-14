#!/bin/bash

apt update
clear

# instaling SNMP and SNMPD
echo "Downloading SNMP and SNMPD............................."
sudo apt install snmpd snmp libsnmp-dev make gcc libpq-dev snmp-mibs-downloader

clear

# replacing default config with custom config
sudo mv /etc/snmp/snmpd.conf /etc/snmp/snmpd.config.backup
sudo cp ./snmpd.conf /etc/snmp/
sudo cp ./snmp.conf /etc/snmp/
sudo cp AFINITI-TASK-MIB.txt /usr/share/snmp/mibs/
sudo service snmpd stop
sudo service snmpd start

#Test 1
echo
echo Testing Static String..................................
echo

snmpwalk -v2c -c test  127.0.0.1 .1.3.6.1.4.1.53864

