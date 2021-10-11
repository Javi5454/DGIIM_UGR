<Qucs Schematic 0.0.19>
<Properties>
  <View=0,-92,1207,800,1,0,0>
  <Grid=10,10,1>
  <DataSet=ejercicio_3.dat>
  <DataDisplay=ejercicio_3.dpl>
  <OpenDisplay=1>
  <Script=ejercicio_3.m>
  <RunScript=0>
  <showFrame=0>
  <FrameText0=Title>
  <FrameText1=Drawn By:>
  <FrameText2=Date:>
  <FrameText3=Revision:>
</Properties>
<Symbol>
</Symbol>
<Components>
  <Vdc V1 1 370 270 18 -26 0 1 "10 V" 1>
  <VProbe Sonda_V 1 530 60 28 -31 0 0>
  <R R1 1 700 270 15 -26 0 1 "1 kOhm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "US" 0>
  <IProbe Sonda_I 1 630 190 -26 16 0 0>
  <GND * 1 650 370 0 0 0 0>
  <.TR TR1 1 80 210 0 79 0 0 "lin" 1 "0" 1 "50 us" 1 "30" 0 "Trapezoidal" 0 "2" 0 "1 ns" 0 "1e-16" 0 "150" 0 "0.001" 0 "1 pA" 0 "1 uV" 0 "26.85" 0 "1e-3" 0 "1e-6" 0 "1" 0 "CroutLU" 0 "no" 0 "yes" 0 "0" 0>
  <L L1 1 500 190 -26 10 0 0 "10 mH" 1 "0" 0>
</Components>
<Wires>
  <370 190 370 240 "" 0 0 0 "">
  <370 370 650 370 "" 0 0 0 "">
  <370 300 370 370 "" 0 0 0 "">
  <370 190 460 190 "" 0 0 0 "">
  <520 80 520 120 "" 0 0 0 "">
  <460 120 520 120 "" 0 0 0 "">
  <460 120 460 190 "" 0 0 0 "">
  <540 80 540 120 "" 0 0 0 "">
  <540 120 550 120 "" 0 0 0 "">
  <550 120 550 190 "" 0 0 0 "">
  <700 300 700 370 "" 0 0 0 "">
  <700 190 700 240 "" 0 0 0 "">
  <660 190 700 190 "" 0 0 0 "">
  <550 190 600 190 "" 0 0 0 "">
  <650 370 700 370 "" 0 0 0 "">
  <530 190 550 190 "" 0 0 0 "">
  <460 190 470 190 "" 0 0 0 "">
</Wires>
<Diagrams>
  <Rect 920 460 240 160 3 #c0c0c0 1 00 1 0 1e-05 5e-05 1 0.01 1e-18 0.01 1 -1 1 1 315 0 225 "" "" "">
	<"Sonda_I.It" #0000ff 0 3 0 0 0>
  </Rect>
  <Rect 930 250 240 160 3 #c0c0c0 1 00 1 0 0.2 1 1 -0.1 0.5 1.1 1 -0.1 0.5 1.1 315 0 225 "" "" "">
	<"Sonda_V.Vt" #0000ff 0 3 0 0 0>
  </Rect>
</Diagrams>
<Paintings>
</Paintings>
