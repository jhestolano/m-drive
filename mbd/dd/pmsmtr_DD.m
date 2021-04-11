MtrParams = struct;
MtrParams.Vdc = 48;
MtrParams.SpdNom  = 3e3;

%% BLDC motor parameters;
MtrParams.Rs = 0.25;
MtrParams.Ls = 1.4e-4;
MtrParams.Lm = 0;
MtrParams.Ms = 7.5e-7;
MtrParams.Ld = MtrParams.Ls + MtrParams.Ms + (3/2) * MtrParams.Lm;
MtrParams.Lq = MtrParams.Ls + MtrParams.Ms - (3/2) * MtrParams.Lm;

MtrParams.Poles = 4;
MtrParams.Ktrq   = 0.12;
MtrParams.MFlux = MtrParams.Ktrq / ((3/2) * MtrParams.Poles);
MtrParams.Jm = 1.9e-4;

%% Open loop parameters;
fsw = 10e3;

%% Machine PI control parameters;
% Kp_ids = 0.5;
% Ki_ids = 10;
% Kp_iqs = 0.7;
% Ki_iqs = 12;

Kp_ids = 0.5;
Ki_ids = 15;
Kp_iqs = 0.7;
Ki_iqs = 17;

% Kp_wr = 1.2;
% Ki_wr = 30;
% Kp_Te = 1.08;
% Ki_Te = 210.02;
% Kp_pos = 0.06;
% Ki_pos = 2;

% Control saturations;
id_max = 1;
iq_max = 1;
Vd_max = 1;
Vq_max = 1;

%% From measurements to engenering units - Parameters;
CPR = 500;
