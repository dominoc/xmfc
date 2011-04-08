function s = make_structure(in_flags) 
    s = struct();
    
    s.('devID') = 0;
    
   if(in_flags.accel)
        s.('accel') = struct('d',[]);
        if(in_flags.raw)
           s.accel.('r') = [];
        end
    end
    
    if(in_flags.gyro)
         s.('gyro') = struct('d',[]);
        if(in_flags.raw)
           s.gyro.('r') = [];
        end
    end
    
    if(in_flags.magn)
         s.('magn') = struct('d',[]);
        if(in_flags.raw)
           s.magn.('r') = [];
        end
    end
    
    if(in_flags.euler)
        s.('euler') = [];
    end
    
    if(in_flags.quat)
        s.('quat') = [];
    end
    
    if(in_flags.time)
        s.('time') = [];
    end
end
