flow=[5,10,20,30,40,50,60,80,100,125,150,200,250];
circ=[8.3,7.8,7,6.3,5.6,5,4.5,3.5,2.8,2.3,1.8,1.3,1];
ang=(circ/10.3)*360;
%%
plot(flow,ang,"r",LineWidth=2,Marker="o");
xlabel("Flow rate(mL/h)");
ylabel("Angle(degree)");
title("Rotation angle vs flow rate curve");