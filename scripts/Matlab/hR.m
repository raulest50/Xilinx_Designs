function y=hR(x)

if x<0
    y=0;
else
    tau11=0.0122;%%ps
    tau22=0.032;%%ps
    y=((tau11^2+tau22^2)/(tau11*tau22^2))*exp(-x./tau22).*sin(x./tau11);
end

end