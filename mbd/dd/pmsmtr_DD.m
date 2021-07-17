SimParams.PwmFrq = 30.0e3;

% Used by local simscape solver inside motor model.
SimParams.Ts = 1.0e-5;

%% Motor parameters.
MtrParams = struct;
MtrParams.Vdc = 12;
MtrParams.SpdNom = 4000.;

MtrParams.Rs = 1.8 / 2.;
MtrParams.Ls = 2.6e-3 / 2.;
MtrParams.Lm = 0.;
MtrParams.Ms = 0.;
MtrParams.Ld = MtrParams.Ls + MtrParams.Ms + (3/2) * MtrParams.Lm;
MtrParams.Lq = MtrParams.Ls + MtrParams.Ms - (3/2) * MtrParams.Lm;
MtrParams.Kf = 0.;

MtrParams.Poles = 4; % Number of pole pairs.
MtrParams.Ktrq   = 0.035;
MtrParams.MFlux = MtrParams.Ktrq / ((3/2) * MtrParams.Poles);
MtrParams.Jm = 24.e-6;

MtrParams.PPR = 600;
MtrParams.EncCnts = 4 * MtrParams.PPR;

MtrParams.IfbkSnsNoise = 0.1; % Sensor noise on current measurement.
MtrParams.IfbkOfs = [0., 0., 0.]; % Current sensor offset.

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
CtrlParams.IfbkBW = 4e3;
CtrlParams.IfbkKi = CtrlParams.IfbkBW * MtrParams.Rs;
CtrlParams.IfbkKp = CtrlParams.IfbkBW * MtrParams.Ls;

CtrlParams.SpdBW = 1e3;
CtrlParams.SpdKi = CtrlParams.SpdBW * MtrParams.Kf;
CtrlParams.SpdKp = CtrlParams.SpdBW * MtrParams.Jm;
% CtrlParams.SpdKi = CtrlParams.SpdBW / MtrParams.Kdc;
% CtrlParams.SpdKp = MtrParams.Tau * CtrlParams.SpdKi;

CtrlParams.TsPos = 0.01;
CtrlParams.PosKp = (4 / CtrlParams.TsPos);
CtrlParams.PosKi = 0.0;

SmDiffParams.AccMax = 9e4;
SmDiffParams.Ki = 1.1 * SmDiffParams.AccMax;
SmDiffParams.Kp = sqrt(SmDiffParams.AccMax);

%% Disturbance observer tuning.
% Observer form:
% e = z1 - y;
% dz1/dt = z1 - k1 * e;
% dz2/dt = z2 + b * u - K2 * e;
% dz3/dt = z3 - k3 * e;

% Observer tuning:
AdrcParams.Tsettle = 0.002;
AdrcParams.w0 = 4. / AdrcParams.Tsettle;
AdrcParams.K1 = 3 * AdrcParams.w0;
AdrcParams.K2 = 3 * AdrcParams.w0 ^ 2;
AdrcParams.K3 = AdrcParams.w0 ^ 3;

% Update code generating DD.
disp('Updating Ctrl_DD data dictionary.');
run('ctrl_DD');
