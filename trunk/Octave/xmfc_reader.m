function [l_data,l_config,l_flags] = xmfc_reader(in_filename)
    
    l_fp = fopen(in_filename,'r');
    
    l_ndp  = fread(l_fp,3,'int32');
    
    l_ids  = fread(l_fp,l_ndp(1),'int32');
    
    [l_data,l_flags] = read_data(l_fp,l_ndp(1),l_ids,l_ndp(2),l_ndp(3));
    
    l_config = get_config();
    
    for(i = 1:size(l_data,2))
        
        l_id = l_data(i).devID;
        
        if(l_id == l_config.locations.thigh_R.devID)
            l_config.locations.thigh_R.('dataIdx') = i;
            continue;
        end
        
        if(l_id == l_config.locations.thigh_L.devID)
            l_config.locations.thigh_L.('dataIdx') = i;
            continue;
        end
        
        if(l_id == l_config.locations.shin_R.devID)
            l_config.locations.shin_R.('dataIdx') = i;
            continue;
        end
        
        if(l_id == l_config.locations.shin_L.devID)
            l_config.locations.shin_L.('dataIdx') = i;
            continue;
        end
    end
    
    
end
    
