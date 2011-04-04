function [n,data] = xmfc_reader(in_filename)
    
    l_fp = fopen(in_filename);
    ndp  = fread(l_fp,3,"int32");
    
    data = read_data(l_fp,ndp(1),ndp(2),ndp(3));
    
    
    
function l_data = read_data(in_filePointer, in_NSensors, in_dataFlags, in_processFlags)
    
    l_nElemsPerSensor = 0;
    
    
    if(bitand(in_dataFlags,bitshift(1,1)) ~= 0) %accel
        l_nElemsPerSensor += 3;
        disp "accel data";
    end
    
    if(bitand(in_dataFlags,bitshift(1,2)) ~= 0) %gyro
        l_nElemsPerSensor += 3;
        disp "gyroscope data";
    end
    
    if(bitand(in_dataFlags,bitshift(1,3)) ~= 0) %magno
        l_nElemsPerSensor += 3;
        disp "magnetometer data";
    end
    
    if(bitand(in_dataFlags,bitshift(1,6)) ~= 0) %raw data
        l_nElemsPerSensor *= 2;
        disp "raw data available";
    end
    
    if(bitand(in_dataFlags,bitshift(1,0)) ~= 0) %time
        l_nElemsPerSensor += 2; %64 bit time stamps...
        disp "time available";
    end
    
    if(bitand(in_dataFlags,bitshift(1,4)) ~= 0) %euler
        l_nElemsPerSensor += 3;
        disp "Euler angles available";
    end
    
    if(bitand(in_dataFlags,bitshift(1,5)) ~= 0) %quaternion
        l_nElemsPerSensor += 4;
        disp "Quaternion data available";
    end

    raw_data = fread(in_filePointer,Inf,'float64');
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

    
    % accel data
    figure;
    plot(x,l_data(:,1),'r');
    hold on;
    plot(x,l_data(:,2),'g');
    plot(x,l_data(:,3),'b');
    title("Accelerometer");
    legend('x','y','z');
    hold off;
    
    
    %gyro data
    figure;
    plot(x,l_data(:,4),'r');
    hold on;
    plot(x,l_data(:,5),'g');
    plot(x,l_data(:,6),'b');
    title("Gyroscope");
    legend('x','y','z');
    hold off;
    
    %gyro data
    figure;
    plot(x,l_data(:,7),'r');
    hold on;
    plot(x,l_data(:,8),'g');
    plot(x,l_data(:,9),'b');
    title("Magnetometer");
    legend('x','y','z');
    hold off;

    figure;
    plot(x,l_data(:,1),'r');
    hold on;
    plot(x,l_data(:,4),'g');
    plot(x,l_data(:,7),'b');
    title("Combined - X");
    legend('acc.x','gyr.x','magn.x');
    hold off;