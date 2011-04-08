function process_data(in_filename)

[l_data,l_config]   = xmfc_reader(in_filename);

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


l_titles.('acceleration') = cell(4,1);
l_titles.('rotation')     = cell(4,1);
l_titles.('magnetometer') = cell(4,1);

p_data.('acceleration')     = cell(4,1);
p_data.('rotation')         = cell(4,1);
p_data.('magnetometer')     = cell(4,1);

s_accel = 'acceleration';
l_titles.acceleration{1} = [s_ls s_accel];
l_titles.acceleration{2} = [s_rs s_accel];
l_titles.acceleration{3} = [s_lt s_accel];
l_titles.acceleration{4} = [s_rt s_accel];

s_rotation = 'rotation';
l_titles.rotation{1} = [s_ls s_rotation];
l_titles.rotation{2} = [s_rs s_rotation];
l_titles.rotation{3} = [s_lt s_rotation];
l_titles.rotation{4} = [s_rt s_rotation];

s_magnetometer = 'magnetometer';
l_titles.magnetometer{1} = [s_ls s_magnetometer];
l_titles.magnetometer{2} = [s_rs s_magnetometer];
l_titles.magnetometer{3} = [s_lt s_magnetometer];
l_titles.magnetometer{4} = [s_rt s_magnetometer];


%accel data
p_data.acceleration{1}  = l_SL.accel.d;
p_data.acceleration{2}  = l_SR.accel.d;
p_data.acceleration{3}  = l_TL.accel.d;
p_data.acceleration{4}  = l_TR.accel.d;

% rotation data
p_data.rotation{1}      = l_SL.gyro.d;
p_data.rotation{2}      = l_SR.gyro.d;
p_data.rotation{3}      = l_TL.gyro.d;
p_data.rotation{4}      = l_TR.gyro.d;

% magnetometer data
p_data.magnetometer{1}  = l_SL.magn.d;
p_data.magnetometer{2}  = l_SR.magn.d;
p_data.magnetometer{3}  = l_TL.magn.d;
p_data.magnetometer{4}  = l_TR.magn.d;


plot_data(p_data.acceleration,l_titles.acceleration);
plot_data(p_data.rotation,l_titles.rotation);
plot_data(p_data.magnetometer,l_titles.magnetometer);



