function c = get_config()

c = struct();

TR = hex2dec('320316'); % right thigh
SR = hex2dec('320281'); % right shin

TL = hex2dec('320282'); % left thigh
SL = hex2dec('320315'); % left shin

c.('locations') = struct();
c.locations.('thigh_R') = struct('devID',TR);
c.locations.('thigh_L') = struct('devID',TL);
c.locations.('shin_R')  = struct('devID',SR);
c.locations.('shin_L')  = struct('devID',SL);

end