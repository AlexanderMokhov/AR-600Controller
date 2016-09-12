:: RESULTS FILE COPY
:: V1.0 BOMJ EDITION
@echo off
set dest=H:\Tarasov\EXP\JULY 2016

set date=%date:~0,2%.%date:~3,2%.%date:~6,4%
set name=%1
set dest=%dest%\%date%\%name%

mkdir "%dest%"
copy sinhron\drive*.txt "%dest%"
copy sinhron\fm*.txt "%dest%"
copy sinhron\rezr*.txt "%dest%"