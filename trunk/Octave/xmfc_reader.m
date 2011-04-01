function [n,data] = xmfc_reader(in_filename)
    
    l_fp = fopen(in_filename);
    ndp  = fread(l_fp,3,"int32");
    
    data = read_data(l_fp,ndp(1),ndp(2),ndp(3));
    
    
    
function l_data = read_data(in_filePointer, in_NSensors, in_dataFlags, in_processFlags)
    
    l_nElemsPerSensor = 0;
    
    
    if(bitand(in_dataFlags,bitshift(1,0))) %accel
        l_nElemsPerSensor += 3;
    end
    
    if(bitand(in_dataFlags,bitshift(1,1))) %gyro
        l_nElemsPerSensor += 3;
    end
    
    if(bitand(in_dataFlags,bitshift(1,2))) %magno
        l_nElemsPerSensor += 3;
    end
    
    if(bitand(in_dataFlags,bitshift(1,5))) %raw data
        l_nElemsPerSensor *= 2;
    end
    
    if(bitand(in_dataFlags,bitshift(1,3))) %euler
        l_nElemsPerSensor += 3;
    end
    
    if(bitand(in_dataFlags,bitshift(1,4))) %quaternion
        l_nElemsPerSensor += 4;
    end

    raw_data = fread(in_filePointer,Inf,'int32');
    %reshape: data,rows,columns
    raw_data = reshape(raw_data,[],(l_nElemsPerSensor* ...
                                    in_NSensors));

    for(sensor=0:in_NSensors-1)
        l_start = sensor*(l_nElemsPerSensor) + 1;
        l_end   = l_start + l_nElemsPerSensor - 1;
        
        data(sensor+1,:,:) = raw_data(:,l_start:l_end);
    end
    
    l_data = squeeze(data(1,:,:));
    x = 1:size(l_data,1);

    plot(x,l_data(:,1),'r');
    hold on;
    plot(x,l_data(:,2),'g');
    plot(x,l_data(:,3),'b');
    legend("x","y","z");
    hold off;