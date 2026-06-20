s=[0,9,14,19,27,33,39,44,55,61,66,70,76,90];
angle=(s*180)/(15.92*3.1416);
flow_rate=[0,5,10,20,30,40,50,60,80,100,125,150,200,250];
%%
p=polyfit(angle,flow_rate,3);
angle_p=0:1:360;
flow_rate_p=polyval(p,angle_p);
plot(angle,flow_rate,'o',angle_p,flow_rate_p,':.');
xlabel("Angle(degree)");
ylabel("Flowrate(mL/hour)");
xlim([0 360]);

