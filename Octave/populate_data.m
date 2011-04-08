function out_data = populate_data(in_flags,in_raw)

    l_start = 1;
    
    out_data = make_structure(in_flags);
    
    if(in_flags.time)
        out_data.time = in_raw(:,l_start:(l_start+1));
        l_start = l_start + 2;
    end
    
    if(in_flags.accel) 
        out_data.accel.d = in_raw(:,l_start:(l_start+2));
        l_start = l_start + 3;
        if(in_flags.raw)
            out_data.accel.r = in_raw(:,l_start:(l_start+2));
            l_start = l_start + 3;
        end
    end
    
    if(in_flags.gyro)
        out_data.gyro.d = in_raw(:,l_start:(l_start+2));
        l_start = l_start + 3;
        if(in_flags.raw)
            out_data.gyro.r = in_raw(:,l_start:(l_start+2));
            l_start = l_start + 3;
        end
    end
    
    if(in_flags.magn)
        out_data.magn.d = in_raw(:,l_start:(l_start+2));
        l_start = l_start + 3;
        if(in_flags.raw)
            out_data.magn.r = in_raw(:,l_start:(l_start+2));
            l_start = l_start + 3;
        end
    end
    
    if(in_flags.euler)
        out_data.euler = in_raw(:,l_start:(l_start+2));
        l_start = l_start + 3;
    end
    
    if(in_flags.quat)
        out_data.quat = in_raw(:,l_start:(l_start+3));
%        l_start = l_start + 4;
    end
    
 end