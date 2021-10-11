<Qucs Schematic 0.0.19>
<Properties>
  <View=0,0,800,800,1,250,0>
  <Grid=10,10,1>
  <DataSet=ejercicio_1.dat>
  <DataDisplay=ejercicio_1.dpl>
  <OpenDisplay=1>
  <Script=ejercicio_1.m>
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
  <Vdc V1 1 160 340 18 -26 0 1 "10 V" 1>
  <R R1 1 310 240 -26 15 0 0 "1 kOhm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "US" 0>
  <VProbe Sonda_V 1 600 340 -16 28 0 3>
  <IProbe Sonda_I 1 330 430 -26 -40 0 2>
  <C C1 1 460 330 26 -18 1 1 "10 uF" 1 "0" 0 "neutral" 0>
  <GND * 1 200 430 0 0 0 0>
  <.TR TR1 1 250 610 0 79 0 0 "lin" 1 "0" 1 "0.05 s" 1 "11" 0 "Trapezoidal" 0 "2" 0 "1 ns" 0 "1e-16" 0 "150" 0 "0.001" 0 "1 pA" 0 "1 uV" 0 "26.85" 0 "1e-3" 0 "1e-6" 0 "1" 0 "CroutLU" 0 "no" 0 "yes" 0 "0" 0>
</Components>
<Wires>
  <160 240 160 310 "" 0 0 0 "">
  <160 240 280 240 "" 0 0 0 "">
  <340 240 460 240 "" 0 0 0 "">
  <460 240 460 280 "" 0 0 0 "">
  <460 360 460 400 "" 0 0 0 "">
  <160 430 200 430 "" 0 0 0 "">
  <160 370 160 430 "" 0 0 0 "">
  <360 430 460 430 "" 0 0 0 "">
  <540 330 580 330 "" 0 0 0 "">
  <540 280 540 330 "" 0 0 0 "">
  <460 280 460 300 "" 0 0 0 "">
  <460 280 540 280 "" 0 0 0 "">
  <580 350 580 400 "" 0 0 0 "">
  <460 400 460 430 "" 0 0 0 "">
  <460 400 580 400 "" 0 0 0 "">
  <200 430 300 430 "" 0 0 0 "">
</Wires>
<Diagrams>
  <Rect 490 680 240 160 3 #c0c0c0 1 00 1 0 0.2 1 1 -0.1 0.5 1.1 1 -0.1 0.5 1.1 315 0 225 "" "" "">
	<"Sonda_V.Vt" #0000ff 0 3 0 0 0>
  </Rect>
</Diagrams>
<Paintings>
</Paintings>
