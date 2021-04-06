SimParams.PwmFrq = 30.0e3;
SimParams.Ts = 1.0e-5;

MotorParams.R = 23.6347; % Resistance.
MotorParams.L = 0.02395; % Inductance.
MotorParams.K = 0.10028; % Torque Constant.
MotorParams.Kf = 1.6713e-5; % Damping.
MotorParams.J = 5.2668e-6; % Inertia.

% From Sys. ID:
MotorParams.Tau = 1 / 90.56;
MotorParams.Kdc = (805.6 / 90.56) * MotorParams.R;
%MotorParams.Kf = MotorParams.K / MotorParams.Kdc;
%MotorParams.J = MotorParams.Tau * MotorParams.Kf;

MotorParams.AccMax = 1e4 * 180 / pi;
MotorParams.PPR = 400; % Encoder pulses / rev.
MotorParams.IfbkOfs = -20e-3; % Current sensor offset.

CtrlParams.IfbkBW = 4e3;
CtrlParams.IfbkKi = CtrlParams.IfbkBW * MotorParams.R;
CtrlParams.IfbkKp = CtrlParams.IfbkBW * MotorParams.L;

CtrlParams.SpdBW = 1e3;
CtrlParams.SpdKi = CtrlParams.SpdBW * MotorParams.Kf;
CtrlParams.SpdKp = CtrlParams.SpdBW * MotorParams.J;
% CtrlParams.SpdKi = CtrlParams.SpdBW / MotorParams.Kdc;
% CtrlParams.SpdKp = MotorParams.Tau * CtrlParams.SpdKi;

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
% AdrcParams.Tsettle = 0.05;
AdrcParams.Tsettle = 0.005;;
AdrcParams.w0 = 4. / AdrcParams.Tsettle;
AdrcParams.K1 = 3 * AdrcParams.w0;
AdrcParams.K2 = 3 * AdrcParams.w0 ^ 2;
AdrcParams.K3 = AdrcParams.w0 ^ 3;

% Update code generating DD.
disp('Updating Ctrl_DD data dictionary.');
run('ctrl_DD');
