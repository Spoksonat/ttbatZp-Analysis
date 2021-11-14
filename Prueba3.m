a = 50;
f = figure;
colormap(hot)
h = contourslice(projections(50:200, 50:200, :),[],[],[a],50);
view(3);
axis tight 
b = uicontrol('Parent',f,'Style','slider','value',a, 'min',0, 'max',100);
b.Callback = @(es,ed) updateSystem(h,contourslice(projections(50:200, 50:200, :),[],[],es.Value,50)); 