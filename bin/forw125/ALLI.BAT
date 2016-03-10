CALL IFORINI.BAT
del *.ftt
del *.f
copy fm481.f32 fm481.ftt
rem upper 04/05/10 06:14pm
ren fm481.f32 fm4811
dblprep *.f32
ren fm4811 fm481.f32
ren *.ftt *.f
ifort /c /QaxSSE2 /Zi /w /WB /4Ns /Qsave /NODEFAULTLIB /threads /fpscomp:ioformat *.f
rem SINHRON компилируется без препроцессора двойной точности
rem после работы пакета источники для компилятора INTEL имеют расширение *.f
xiLIB @libi.dat
copy rashidb.lib c:\utilf