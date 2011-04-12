function [p_data, locations] = process_data(in_filename)

[l_data,l_config,l_flags]   = xmfc_reader(in_filename);

p_data      = struct();
l_titles    = struct();

l_SL = l_data(l_config.locations.shin_L.dataIdx);
l_SR = l_data(l_config.locations.shin_R.dataIdx);
l_TL = l_data(l_config.locations.thigh_L.dataIdx);
l_TR = l_data(l_config.locations.thigh_R.dataIdx);

s_ls = 'Left shin ';
s_rs = 'Right shin ';
s_lt = 'Left thigh ';
s_rt = 'Right thigh ';


if(l_flags.accel)
    l_titles.('acceleration')   = cell(4,1);
    p_data.('acceleration')     = cell(4,1);
    s_accel                     = 'acceleration';
    l_titles.acceleration{1}    = [s_ls s_accel];
    l_titles.acceleration{2}    = [s_rs s_accel];
    l_titles.acceleration{3}    = [s_lt s_accel];
    l_titles.acceleration{4}    = [s_rt s_accel];
    
    p_data.acceleration{1}      = l_SL.accel.d;
    p_data.acceleration{2}      = l_SR.accel.d;
    p_data.acceleration{3}      = l_TL.accel.d;
    p_data.acceleration{4}      = l_TR.accel.d;
end

if(l_flags.gyro)
    l_titles.('rotation')       = cell(4,1);
    p_data.('rotation')         = cell(4,1);
    s_rotation                  = 'rotation';
    l_titles.rotation{1}        = [s_ls s_rotation];
    l_titles.rotation{2}        = [s_rs s_rotation];
    l_titles.rotation{3}        = [s_lt s_rotation];
    l_titles.rotation{4}        = [s_rt s_rotation];
    
    p_data.rotation{1}          = l_SL.gyro.d;
    p_data.rotation{2}          = l_SR.gyro.d;
    p_data.rotation{3}          = l_TL.gyro.d;
    p_data.rotation{4}          = l_TR.gyro.d;

end

if(l_flags.magn)
    l_titles.('magnetometer')   = cell(4,1);
    p_data.('magnetometer')     = cell(4,1);
    s_magnetometer              = 'magnetometer';
    l_titles.magnetometer{1}    = [s_ls s_magnetometer];
    l_titles.magnetometer{2}    = [s_rs s_magnetometer];
    l_titles.magnetometer{3}    = [s_lt s_magnetometer];
    l_titles.magnetometer{4}    = [s_rt s_magnetometer];
    
    p_data.magnetometer{1}      = l_SL.magn.d;
    p_data.magnetometer{2}      = l_SR.magn.d;
    p_data.magnetometer{3}      = l_TL.magn.d;
    p_data.magnetometer{4}      = l_TR.magn.d;
end

if(l_flags.euler)
    p_data.('euler')            = cell(4,1);
end

if(l_flags.quat)
    p_data.('quaternion')       = cell(4,1);
end

if(l_flags.time)
    l_titles.('time')           = cell(4,1);
    p_data.('time')             = cell(4,1);
    s_time                      = 'time (ms)';
    l_titles.time{1}            = [s_ls s_time];
    l_titles.time{2}            = [s_rs s_time];
    l_titles.time{3}            = [s_lt s_time];
    l_titles.time{4}            = [s_rt s_time];
    
    p_data.time{1}              = l_SL.time;
    p_data.time{2}              = l_SR.time;
    p_data.time{3}              = l_TL.time;
    p_data.time{4}              = l_TR.time;
end

locations                       = l_config.locations;

%titles
p_data.('labels')               = l_titles;



%plot_data(p_data.acceleration,l_titles.acceleration);
%plot_data(p_data.rotation,l_titles.rotation);
%plot_data(p_data.magnetometer,l_titles.magnetometer);



