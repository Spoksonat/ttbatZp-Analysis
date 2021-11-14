ims = [];
num_im = 300;

for i = 1:num_im
   prefix = "C:\\Users\\nandi\\Desktop\\Lab Avanzado\\Imagenes\\CORR";
   name = sprintf("%s\\corr_%i.txt", prefix, i);
   T = readmatrix(name); 
   ims(:,:,i) = T;
end
ims(:,:,10);
imagesc(ims(:,:,10));
axis square;
colorbar
colormap bone;
xlabel('This is the label caption');

sinograms = [];
num_of_slices = 256;
tamano = floor(256/num_of_slices);
for i = 1:num_of_slices
    sinogram = sinograma(ims, tamano*(i-1)+1, tamano*i, num_im);
    sinograms(:,:,i) = sinogram;
end
imagesc(sinograms(:,:,50));

angulo = 0.6;
angulo_final = angulo*num_im;
theta = 0:angulo:angulo_final-angulo;

projections = [];
for i = 1:num_of_slices
    I = iradon(sinograms(:,:,i),theta, 'pchip', 'Hann', 1, 256);
    projections(:,:,i) = I;
end

imagesc(projections(:,:,50))


function sino = sinograma(M, row_in, row_fin, num_im)
   sino = [];
   if row_in ~= row_fin
       for i = 1:num_im
           S = sum(M(row_in:row_fin,:,i));
           sino = [sino transpose(S)];
       end
   else
       for i = 1:num_im
           S = M(row_in:row_fin,:,i);
           sino = [sino transpose(S)];
       end
   end    
end