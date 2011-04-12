function [data,l_flags] = read_data(in_filePointer, in_NSensors, in_sensorIDs, ...
                            in_dataFlags, in_processFlags)
    
    l_nElemsPerSensor = 0;
    l_flags = struct('accel',false,...
                     'gyro', false,...
                     'magn', false,...
                     'euler',false,...
                     'quat', false,...
                     'time', false,...
                     'raw',  false);
                 
    if(bitand(in_dataFlags,bitshift(1,1)) ~= 0) %accel
        l_nElemsPerSensor = l_nElemsPerSensor + 3;
        l_flags.accel = true;
        disp('accel data');
    end
    
    if(bitand(in_dataFlags,bitshift(1,2)) ~= 0) %gyro
        l_nElemsPerSensor = l_nElemsPerSensor + 3;
        l_flags.gyro = true;
        disp('gyroscope data');
    end
    
    if(bitand(in_dataFlags,bitshift(1,3)) ~= 0) %magno
        l_nElemsPerSensor = l_nElemsPerSensor + 3;
        l_flags.magn = true;
        disp('magnetometer data');
    end
    
    if(bitand(in_dataFlags,bitshift(1,6)) ~= 0) %raw data
        l_nElemsPerSensor = l_nElemsPerSensor * 2;
        l_flags.raw = true;
        disp('raw data available');
    end
    
    if(bitand(in_dataFlags,bitshift(1,0)) ~= 0) %time
        l_nElemsPerSensor = l_nElemsPerSensor + 1; % time stamps...
        l_flags.time = true;
        disp('time available');
    end
    
    if(bitand(in_dataFlags,bitshift(1,4)) ~= 0) %euler
        l_nElemsPerSensor = l_nElemsPerSensor + 3;
        l_flags.euler = true;
        disp('Euler angles available');
    end
    
    if(bitand(in_dataFlags,bitshift(1,5)) ~= 0) %quaternion
        l_nElemsPerSensor = l_nElemsPerSensor + 4;
        l_flags.quat = true;
        disp('Quaternion data available');
    end
   

    raw_data = fread(in_filePointer,Inf,'float64');

    raw_data = reshape(raw_data,(l_nElemsPerSensor*in_NSensors),[]);
    
    raw_data = raw_data';

    
    for(sensor=0:in_NSensors-1)
        l_start = sensor*(l_nElemsPerSensor) + 1;
        l_end   = l_start + l_nElemsPerSensor - 1;
        data(sensor+1) = populate_data(l_flags,raw_data(:,l_start:l_end));
        data(sensor+1).devID = in_sensorIDs(sensor+1);
    end

end
   