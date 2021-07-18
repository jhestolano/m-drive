%% Sampling rates.
FastTsample = 1. / 30e3;
MainTsample = 1e-3;

%% Fast sampling time 30khz
TsFast = Simulink.Parameter;
TsFast.StorageClass = 'Auto';
TsFast.Description = 'Fast sampling time (30khz)';
TsFast.DataType = 'single';
TsFast.Min = [];
TsFast.Max = [];
TsFast.DocUnits = '';
TsFast.Value = FastTsample;
TsFast.CoderInfo.StorageClass = 'Custom';
TsFast.CoderInfo.CustomStorageClass = 'ExportToFile';
TsFast.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
TsFast.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Bus voltage.
Cfg_VBus = Simulink.Parameter;
Cfg_VBus.StorageClass = 'Auto';
Cfg_VBus.Description = 'Bus voltage';
Cfg_VBus.DataType = 'single';
Cfg_VBus.Min = [];
Cfg_VBus.Max = [];
Cfg_VBus.DocUnits = '';
Cfg_VBus.Value = 12.0;
Cfg_VBus.CoderInfo.StorageClass = 'Custom';
Cfg_VBus.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_VBus.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_VBus.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Number of pole pairs.
Cfg_PolePairs = Simulink.Parameter;
Cfg_PolePairs.StorageClass = 'Auto';
Cfg_PolePairs.Description = 'Number of pole pairs.';
Cfg_PolePairs.DataType = 'uint8';
Cfg_PolePairs.Min = [];
Cfg_PolePairs.Max = [];
Cfg_PolePairs.DocUnits = '';
Cfg_PolePairs.Value = 4;
Cfg_PolePairs.CoderInfo.StorageClass = 'Custom';
Cfg_PolePairs.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_PolePairs.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_PolePairs.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Motor Inductance.
Cfg_Ls = Simulink.Parameter;
Cfg_Ls.StorageClass = 'Auto';
Cfg_Ls.Description = 'Motor inductance (phase)';
Cfg_Ls.DataType = 'single';
Cfg_Ls.Min = [];
Cfg_Ls.Max = [];
Cfg_Ls.DocUnits = '';
Cfg_Ls.Value = 0.0013;
Cfg_Ls.CoderInfo.StorageClass = 'Custom';
Cfg_Ls.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_Ls.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_Ls.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Motor Resistance.
Cfg_Rs = Simulink.Parameter;
Cfg_Rs.StorageClass = 'Auto';
Cfg_Rs.Description = 'Motor resistance (phase).';
Cfg_Rs.DataType = 'single';
Cfg_Rs.Min = [];
Cfg_Rs.Max = [];
Cfg_Rs.DocUnits = '';
Cfg_Rs.Value = 1.4;
Cfg_Rs.CoderInfo.StorageClass = 'Custom';
Cfg_Rs.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_Rs.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_Rs.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Motor Flux.
Cfg_MFlux = Simulink.Parameter;
Cfg_MFlux.StorageClass = 'Auto';
Cfg_MFlux.Description = 'Motor flux';
Cfg_MFlux.DataType = 'single';
Cfg_MFlux.Min = [];
Cfg_MFlux.Max = [];
Cfg_MFlux.DocUnits = '';
Cfg_MFlux.Value = 0.0058;
Cfg_MFlux.CoderInfo.StorageClass = 'Custom';
Cfg_MFlux.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_MFlux.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_MFlux.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Enable offset calibration.
Cfg_TmOfsCal = Simulink.Parameter;
Cfg_TmOfsCal.StorageClass = 'Auto';
Cfg_TmOfsCal.Description = 'Offset calibration time window (seconds).';
Cfg_TmOfsCal.DataType = 'single';
Cfg_TmOfsCal.Min = [];
Cfg_TmOfsCal.Max = [];
Cfg_TmOfsCal.DocUnits = '';
Cfg_TmOfsCal.Value = 0.5;
Cfg_TmOfsCal.CoderInfo.StorageClass = 'Custom';
Cfg_TmOfsCal.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_TmOfsCal.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_TmOfsCal.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Enable offset calibration.
Cfg_EnblOfsCal = Simulink.Parameter;
Cfg_EnblOfsCal.StorageClass = 'Auto';
Cfg_EnblOfsCal.Description = 'Enable offset calibration at startup.';
Cfg_EnblOfsCal.DataType = 'boolean';
Cfg_EnblOfsCal.Min = [];
Cfg_EnblOfsCal.Max = [];
Cfg_EnblOfsCal.DocUnits = '';
Cfg_EnblOfsCal.Value = true;
Cfg_EnblOfsCal.CoderInfo.StorageClass = 'Custom';
Cfg_EnblOfsCal.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_EnblOfsCal.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_EnblOfsCal.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Initial angle during offset calibration.
Cfg_OfsCalAnglInit = Simulink.Parameter;
Cfg_OfsCalAnglInit.StorageClass = 'Auto';
Cfg_OfsCalAnglInit.Description = 'Initial angle during offset calibration';
Cfg_OfsCalAnglInit.DataType = 'int32';
Cfg_OfsCalAnglInit.Min = [];
Cfg_OfsCalAnglInit.Max = [];
Cfg_OfsCalAnglInit.DocUnits = '';
Cfg_OfsCalAnglInit.Value = -MtrParams.EncCnts / 4.;
Cfg_OfsCalAnglInit.CoderInfo.StorageClass = 'Custom';
Cfg_OfsCalAnglInit.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_OfsCalAnglInit.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_OfsCalAnglInit.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Duty cycle during angle offset cal.
Cfg_AnglOfsCalPwmDuty = Simulink.Parameter;
Cfg_AnglOfsCalPwmDuty.StorageClass = 'Auto';
Cfg_AnglOfsCalPwmDuty.Description = 'Duty cycle during angle offset cal';
Cfg_AnglOfsCalPwmDuty.DataType = 'single';
Cfg_AnglOfsCalPwmDuty.Min = [];
Cfg_AnglOfsCalPwmDuty.Max = [];
Cfg_AnglOfsCalPwmDuty.DocUnits = '';
Cfg_AnglOfsCalPwmDuty.Value = 0.20;
Cfg_StepToEncCnts.CoderInfo.StorageClass = 'Custom';
Cfg_StepToEncCnts.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_StepToEncCnts.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_StepToEncCnts.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Step to cnts convesion.
Cfg_StepToEncCnts = Simulink.Parameter;
Cfg_StepToEncCnts.StorageClass = 'Auto';
Cfg_StepToEncCnts.Description = 'Defines how many encoder counts per step.';
Cfg_StepToEncCnts.DataType = 'int32';
Cfg_StepToEncCnts.Min = [];
Cfg_StepToEncCnts.Max = [];
Cfg_StepToEncCnts.DocUnits = '';
Cfg_StepToEncCnts.Value = 10;
Cfg_StepToEncCnts.CoderInfo.StorageClass = 'Custom';
Cfg_StepToEncCnts.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_StepToEncCnts.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_StepToEncCnts.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Use observer position estimate as actual position signal.
Cfg_UseObsPosEst = Simulink.Parameter;
Cfg_UseObsPosEst.StorageClass = 'Auto';
Cfg_UseObsPosEst.Description = 'Use observer position estimate.';
Cfg_UseObsPosEst.DataType = 'boolean';
Cfg_UseObsPosEst.Min = [];
Cfg_UseObsPosEst.Max = [];
Cfg_UseObsPosEst.DocUnits = '';
Cfg_UseObsPosEst.Value = false;
Cfg_UseObsPosEst.CoderInfo.StorageClass = 'Custom';
Cfg_UseObsPosEst.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_UseObsPosEst.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_UseObsPosEst.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Motor resistance.
Cfg_MtrRs = Simulink.Parameter;
Cfg_MtrRs.StorageClass = 'Auto';
Cfg_MtrRs.Description = 'Motor resistance';
Cfg_MtrRs.DataType = 'single';
Cfg_MtrRs.Min = [];
Cfg_MtrRs.Max = [];
Cfg_MtrRs.DocUnits = '';
Cfg_MtrRs.Value = MtrParams.Rs;
Cfg_MtrRs.CoderInfo.StorageClass = 'Custom';
Cfg_MtrRs.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_MtrRs.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_MtrRs.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Motor inductance.
Cfg_MtrLs = Simulink.Parameter;
Cfg_MtrLs.StorageClass = 'Auto';
Cfg_MtrLs.Description = 'Motor inductance';
Cfg_MtrLs.DataType = 'single';
Cfg_MtrLs.Min = [];
Cfg_MtrLs.Max = [];
Cfg_MtrLs.DocUnits = '';
Cfg_MtrLs.Value = MtrParams.Ls;
Cfg_MtrLs.CoderInfo.StorageClass = 'Custom';
Cfg_MtrLs.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_MtrLs.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_MtrLs.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Motor inertia.
Cfg_MtrJm = Simulink.Parameter;
Cfg_MtrJm.StorageClass = 'Auto';
Cfg_MtrJm.Description = 'Motor rotor inertia.';
Cfg_MtrJm.DataType = 'single';
Cfg_MtrJm.Min = [];
Cfg_MtrJm.Max = [];
Cfg_MtrJm.DocUnits = '';
Cfg_MtrJm.Value = MtrParams.Jm;
Cfg_MtrJm.CoderInfo.StorageClass = 'Custom';
Cfg_MtrJm.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_MtrJm.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_MtrJm.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Motor friction.
Cfg_MtrKf = Simulink.Parameter;
Cfg_MtrKf.StorageClass = 'Auto';
Cfg_MtrKf.Description = 'Rotor friction coefficient';
Cfg_MtrKf.DataType = 'single';
Cfg_MtrKf.Min = [];
Cfg_MtrKf.Max = [];
Cfg_MtrKf.DocUnits = '';
Cfg_MtrKf.Value = MtrParams.Kf;
Cfg_MtrKf.CoderInfo.StorageClass = 'Custom';
Cfg_MtrKf.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_MtrKf.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_MtrKf.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%%  Motor torque constant.
Cfg_MtrKtrq = Simulink.Parameter;
Cfg_MtrKtrq.StorageClass = 'Auto';
Cfg_MtrKtrq.Description = 'Motor torque constant';
Cfg_MtrKtrq.DataType = 'single';
Cfg_MtrKtrq.Min = [];
Cfg_MtrKtrq.Max = [];
Cfg_MtrKtrq.DocUnits = '';
Cfg_MtrKtrq.Value = MtrParams.Ktrq;
Cfg_MtrKtrq.CoderInfo.StorageClass = 'Custom';
Cfg_MtrKtrq.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_MtrKtrq.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_MtrKtrq.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Enable distrubance compensation.
Cfg_DistTrqFfwdEnbl = Simulink.Parameter;
Cfg_DistTrqFfwdEnbl.StorageClass = 'Auto';
Cfg_DistTrqFfwdEnbl.Description = 'Enable disturbance compensation';
Cfg_DistTrqFfwdEnbl.DataType = 'boolean';
Cfg_DistTrqFfwdEnbl.Min = [];
Cfg_DistTrqFfwdEnbl.Max = [];
Cfg_DistTrqFfwdEnbl.DocUnits = '';
Cfg_DistTrqFfwdEnbl.Value = true;
Cfg_DistTrqFfwdEnbl.CoderInfo.StorageClass = 'Custom';
Cfg_DistTrqFfwdEnbl.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_DistTrqFfwdEnbl.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_DistTrqFfwdEnbl.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Enable x-coupling and b-emf comp.
Cfg_EnblDynComp = Simulink.Parameter;
Cfg_EnblDynComp.StorageClass = 'Auto';
Cfg_EnblDynComp.Description = 'Enable x-coupling and b-emf comp';
Cfg_EnblDynComp.DataType = 'boolean';
Cfg_EnblDynComp.Min = [];
Cfg_EnblDynComp.Max = [];
Cfg_EnblDynComp.DocUnits = '';
Cfg_EnblDynComp.Value = false;
Cfg_EnblDynComp.CoderInfo.StorageClass = 'Custom';
Cfg_EnblDynComp.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_EnblDynComp.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_EnblDynComp.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Enable autocalibration at startup.
Cfg_AutoCalEnbl = Simulink.Parameter;
Cfg_AutoCalEnbl.StorageClass = 'Auto';
Cfg_AutoCalEnbl.Description = 'Enable ifbk loop autocalibration at startup';
Cfg_AutoCalEnbl.DataType = 'boolean';
Cfg_AutoCalEnbl.Min = [];
Cfg_AutoCalEnbl.Max = [];
Cfg_AutoCalEnbl.DocUnits = '';
Cfg_AutoCalEnbl.Value = false;
Cfg_AutoCalEnbl.CoderInfo.StorageClass = 'Custom';
Cfg_AutoCalEnbl.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_AutoCalEnbl.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_AutoCalEnbl.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Current contoller bandwith.
Cfg_IfbkCtrlBW = Simulink.Parameter;
Cfg_IfbkCtrlBW.StorageClass = 'Auto';
Cfg_IfbkCtrlBW.Description = 'Current controller bandwith (rad/s)';
Cfg_IfbkCtrlBW.DataType = 'single';
Cfg_IfbkCtrlBW.Min = [];
Cfg_IfbkCtrlBW.Max = [];
Cfg_IfbkCtrlBW.DocUnits = '';
Cfg_IfbkCtrlBW.Value = 2e3;
Cfg_IfbkCtrlBW.CoderInfo.StorageClass = 'Custom';
Cfg_IfbkCtrlBW.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_IfbkCtrlBW.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_IfbkCtrlBW.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Configuration parameters.
Cfg_SpdSnsEnbl = Simulink.Parameter;
Cfg_SpdSnsEnbl.StorageClass = 'Auto';
Cfg_SpdSnsEnbl.Description = 'System has speed sensor.';
Cfg_SpdSnsEnbl.DataType = 'boolean';
Cfg_SpdSnsEnbl.Min = [];
Cfg_SpdSnsEnbl.Max = [];
Cfg_SpdSnsEnbl.DocUnits = '';
Cfg_SpdSnsEnbl.Value = false;
Cfg_SpdSnsEnbl.CoderInfo.StorageClass = 'Custom';
Cfg_SpdSnsEnbl.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_SpdSnsEnbl.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_SpdSnsEnbl.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Enable Load Observer.
Cfg_EnblLoadObs = Simulink.Parameter;
Cfg_EnblLoadObs.StorageClass = 'Auto';
Cfg_EnblLoadObs.Description = 'Enable active load compensation.';
Cfg_EnblLoadObs.DataType = 'boolean';
Cfg_EnblLoadObs.Min = [];
Cfg_EnblLoadObs.Max = [];
Cfg_EnblLoadObs.DocUnits = '';
Cfg_EnblLoadObs.Value = 0;
Cfg_EnblLoadObs.CoderInfo.StorageClass = 'Custom';
Cfg_EnblLoadObs.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_EnblLoadObs.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_EnblLoadObs.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';


%% Cycle counts during motor torque identification.
Cfg_TrqCnstIDCntThshld = Simulink.Parameter;
Cfg_TrqCnstIDCntThshld.StorageClass = 'Auto';
Cfg_TrqCnstIDCntThshld.Description = 'Motor voltage during torque constant ID.';
Cfg_TrqCnstIDCntThshld.DataType = 'int32';
Cfg_TrqCnstIDCntThshld.Min = [];
Cfg_TrqCnstIDCntThshld.Max = [];
Cfg_TrqCnstIDCntThshld.DocUnits = '';
Cfg_TrqCnstIDCntThshld.Value = 200e-3 / TsFast.Value;
Cfg_TrqCnstIDCntThshld.CoderInfo.StorageClass = 'Custom';
Cfg_TrqCnstIDCntThshld.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_TrqCnstIDCntThshld.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_TrqCnstIDCntThshld.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Voltage applied during torque constant identification.
Cfg_TrqCnstIDMtrVin = Simulink.Parameter;
Cfg_TrqCnstIDMtrVin.StorageClass = 'Auto';
Cfg_TrqCnstIDMtrVin.Description = 'Motor voltage during torque constant ID';
Cfg_TrqCnstIDMtrVin.DataType = 'single';
Cfg_TrqCnstIDMtrVin.Min = [];
Cfg_TrqCnstIDMtrVin.Max = [];
Cfg_TrqCnstIDMtrVin.DocUnits = '';
Cfg_TrqCnstIDMtrVin.Value = 12;
Cfg_TrqCnstIDMtrVin.CoderInfo.StorageClass = 'Custom';
Cfg_TrqCnstIDMtrVin.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_TrqCnstIDMtrVin.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_TrqCnstIDMtrVin.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Current sensor offset identification counts.
Cfg_OfsIDCntThshld = Simulink.Parameter;
Cfg_OfsIDCntThshld.StorageClass = 'Auto';
Cfg_OfsIDCntThshld.Description = 'Inductance ID cycles.';
Cfg_OfsIDCntThshld.DataType = 'int32';
Cfg_OfsIDCntThshld.Min = [];
Cfg_OfsIDCntThshld.Max = [];
Cfg_OfsIDCntThshld.DocUnits = '';
Cfg_OfsIDCntThshld.Value = 1000;
Cfg_OfsIDCntThshld.CoderInfo.StorageClass = 'Custom';
Cfg_OfsIDCntThshld.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_OfsIDCntThshld.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_OfsIDCntThshld.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Ifbk autocal cycle counts: inductance.
Cfg_IndIDCntThshld = Simulink.Parameter;
Cfg_IndIDCntThshld.StorageClass = 'Auto';
Cfg_IndIDCntThshld.Description = 'Inductance ID cycles.';
Cfg_IndIDCntThshld.DataType = 'int32';
Cfg_IndIDCntThshld.Min = [];
Cfg_IndIDCntThshld.Max = [];
Cfg_IndIDCntThshld.DocUnits = '';
Cfg_IndIDCntThshld.Value = 0.5 / TsFast.Value;
Cfg_IndIDCntThshld.CoderInfo.StorageClass = 'Custom';
Cfg_IndIDCntThshld.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_IndIDCntThshld.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_IndIDCntThshld.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Ifbk autocal cycle counts: resistance.
Cfg_ResIDCntThshld = Simulink.Parameter;
Cfg_ResIDCntThshld.StorageClass = 'Auto';
Cfg_ResIDCntThshld.Description = 'Resistance ID cycles.';
Cfg_ResIDCntThshld.DataType = 'int32';
Cfg_ResIDCntThshld.Min = [];
Cfg_ResIDCntThshld.Max = [];
Cfg_ResIDCntThshld.DocUnits = '';
Cfg_ResIDCntThshld.Value = 300;
Cfg_ResIDCntThshld.CoderInfo.StorageClass = 'Custom';
Cfg_ResIDCntThshld.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_ResIDCntThshld.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_ResIDCntThshld.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Inductance ID phase voltage.
Cfg_IndIDMtrVin = Simulink.Parameter;
Cfg_IndIDMtrVin.StorageClass = 'Auto';
Cfg_IndIDMtrVin.Description = 'Inductance ID Phase motor input voltage';
Cfg_IndIDMtrVin.DataType = 'single';
Cfg_IndIDMtrVin.Min = [];
Cfg_IndIDMtrVin.Max = [];
Cfg_IndIDMtrVin.DocUnits = '';
Cfg_IndIDMtrVin.Value = 12;
Cfg_IndIDMtrVin.CoderInfo.StorageClass = 'Custom';
Cfg_IndIDMtrVin.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_IndIDMtrVin.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_IndIDMtrVin.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Inductance On/Off switching ticks.
Cfg_IndIDTs = Simulink.Parameter;
Cfg_IndIDTs.StorageClass = 'Auto';
Cfg_IndIDTs.Description = 'Indutance ID sampling time.';
Cfg_IndIDTs.DataType = 'single';
Cfg_IndIDTs.Min = [];
Cfg_IndIDTs.Max = [];
Cfg_IndIDTs.DocUnits = '';
Cfg_IndIDTs.Value = 1e-3;
Cfg_IndIDTs.CoderInfo.StorageClass = 'Custom';
Cfg_IndIDTs.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_IndIDTs.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_IndIDTs.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Inductance On/Off switching ticks.
Cfg_IndIDSwTicks = Simulink.Parameter;
Cfg_IndIDSwTicks.StorageClass = 'Auto';
Cfg_IndIDSwTicks.Description = 'Indutance ID On/Off switching ticks';
Cfg_IndIDSwTicks.DataType = 'int32';
Cfg_IndIDSwTicks.Min = [];
Cfg_IndIDSwTicks.Max = [];
Cfg_IndIDSwTicks.DocUnits = '';
Cfg_IndIDSwTicks.Value = Cfg_IndIDTs.Value / TsFast.Value;
Cfg_IndIDSwTicks.CoderInfo.StorageClass = 'Custom';
Cfg_IndIDSwTicks.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_IndIDSwTicks.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_IndIDSwTicks.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Inductance ID done cooldown ticks.
Cfg_IndIDCoolDownTicks = Simulink.Parameter;
Cfg_IndIDCoolDownTicks.StorageClass = 'Auto';
Cfg_IndIDCoolDownTicks.Description = 'Inductance ID done cooldown ticks';
Cfg_IndIDCoolDownTicks.DataType = 'int32';
Cfg_IndIDCoolDownTicks.Min = [];
Cfg_IndIDCoolDownTicks.Max = [];
Cfg_IndIDCoolDownTicks.DocUnits = '';
Cfg_IndIDCoolDownTicks.Value = 100e-3 / TsFast.Value;
Cfg_IndIDCoolDownTicks.CoderInfo.StorageClass = 'Custom';
Cfg_IndIDCoolDownTicks.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_IndIDCoolDownTicks.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_IndIDCoolDownTicks.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Inductance ID done cooldown ticks.
Cfg_ResIDCoolDownTicks = Simulink.Parameter;
Cfg_ResIDCoolDownTicks.StorageClass = 'Auto';
Cfg_ResIDCoolDownTicks.Description = 'Resistance ID done cooldown ticks';
Cfg_ResIDCoolDownTicks.DataType = 'int32';
Cfg_ResIDCoolDownTicks.Min = [];
Cfg_ResIDCoolDownTicks.Max = [];
Cfg_ResIDCoolDownTicks.DocUnits = '';
Cfg_ResIDCoolDownTicks.Value = 100e-3 / TsFast.Value;
Cfg_ResIDCoolDownTicks.CoderInfo.StorageClass = 'Custom';
Cfg_ResIDCoolDownTicks.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_ResIDCoolDownTicks.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_ResIDCoolDownTicks.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Resistance ID motor input voltage.
Cfg_ResIDMtrVin = Simulink.Parameter;
Cfg_ResIDMtrVin.StorageClass = 'Auto';
Cfg_ResIDMtrVin.Description = 'Resistance ID motor input voltage';
Cfg_ResIDMtrVin.DataType = 'single';
Cfg_ResIDMtrVin.Min = [];
Cfg_ResIDMtrVin.Max = [];
Cfg_ResIDMtrVin.DocUnits = '';
Cfg_ResIDMtrVin.Value = 12.0;
Cfg_ResIDMtrVin.CoderInfo.StorageClass = 'Custom';
Cfg_ResIDMtrVin.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_ResIDMtrVin.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_ResIDMtrVin.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Resistance maximum value for identification.
Cfg_ResIDMaxThshld = Simulink.Parameter;
Cfg_ResIDMaxThshld.StorageClass = 'Auto';
Cfg_ResIDMaxThshld.Description = 'Resistance maximum value for Identification';
Cfg_ResIDMaxThshld.DataType = 'single';
Cfg_ResIDMaxThshld.Min = [];
Cfg_ResIDMaxThshld.Max = [];
Cfg_ResIDMaxThshld.DocUnits = '';
Cfg_ResIDMaxThshld.Value = 1000.0;
Cfg_ResIDMaxThshld.CoderInfo.StorageClass = 'Custom';
Cfg_ResIDMaxThshld.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_ResIDMaxThshld.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_ResIDMaxThshld.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Resistance minimum value for identification.
Cfg_ResIDMinThshld = Simulink.Parameter;
Cfg_ResIDMinThshld.StorageClass = 'Auto';
Cfg_ResIDMinThshld.Description = 'Resistance minimum value for Identification';
Cfg_ResIDMinThshld.DataType = 'single';
Cfg_ResIDMinThshld.Min = [];
Cfg_ResIDMinThshld.Max = [];
Cfg_ResIDMinThshld.DocUnits = '';
Cfg_ResIDMinThshld.Value = 1e-4;
Cfg_ResIDMinThshld.CoderInfo.StorageClass = 'Custom';
Cfg_ResIDMinThshld.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_ResIDMinThshld.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_ResIDMinThshld.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Inductance minimum value for identification.
Cfg_IndIDMinThshld = Simulink.Parameter;
Cfg_IndIDMinThshld.StorageClass = 'Auto';
Cfg_IndIDMinThshld.Description = 'Inductance minimum value for Identification';
Cfg_IndIDMinThshld.DataType = 'single';
Cfg_IndIDMinThshld.Min = [];
Cfg_IndIDMinThshld.Max = [];
Cfg_IndIDMinThshld.DocUnits = '';
Cfg_IndIDMinThshld.Value = 1e-6;
Cfg_IndIDMinThshld.CoderInfo.StorageClass = 'Custom';
Cfg_IndIDMinThshld.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_IndIDMinThshld.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_IndIDMinThshld.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Inductance maximum value for identification.
Cfg_IndIDMaxThshld = Simulink.Parameter;
Cfg_IndIDMaxThshld.StorageClass = 'Auto';
Cfg_IndIDMaxThshld.Description = 'Inductance maximum value for Identification';
Cfg_IndIDMaxThshld.DataType = 'single';
Cfg_IndIDMaxThshld.Min = [];
Cfg_IndIDMaxThshld.Max = [];
Cfg_IndIDMaxThshld.DocUnits = '';
Cfg_IndIDMaxThshld.Value = 0.1;
Cfg_IndIDMaxThshld.CoderInfo.StorageClass = 'Custom';
Cfg_IndIDMaxThshld.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_IndIDMaxThshld.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_IndIDMaxThshld.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% PID-P term.
IfbkCtrl_Kp = Simulink.Parameter;
IfbkCtrl_Kp.StorageClass = 'Auto';
IfbkCtrl_Kp.Description = 'PI proportional term for current controller.';
IfbkCtrl_Kp.DataType = 'single';
IfbkCtrl_Kp.Min = [];
IfbkCtrl_Kp.Max = [];
IfbkCtrl_Kp.DocUnits = '';
IfbkCtrl_Kp.Value = 95.8;
IfbkCtrl_Kp.CoderInfo.StorageClass = 'Custom';
IfbkCtrl_Kp.CoderInfo.CustomStorageClass = 'ExportToFile';
IfbkCtrl_Kp.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
IfbkCtrl_Kp.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% PID-I term.
IfbkCtrl_Ki = Simulink.Parameter;
IfbkCtrl_Ki.StorageClass = 'Auto';
IfbkCtrl_Ki.Description = 'PI integral term for current controller.';
IfbkCtrl_Ki.DataType =  'single';
IfbkCtrl_Ki.Min = [];
IfbkCtrl_Ki.Max = [];
IfbkCtrl_Ki.DocUnits = '';
IfbkCtrl_Ki.Value = 9.4539e4;
IfbkCtrl_Ki.CoderInfo.StorageClass = 'Custom';
IfbkCtrl_Ki.CoderInfo.CustomStorageClass = 'ExportToFile';
IfbkCtrl_Ki.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
IfbkCtrl_Ki.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Speed Control bandwith in autocal mode.
Cfg_SpdCtrlBW = Simulink.Parameter;
Cfg_SpdCtrlBW.StorageClass = 'Auto';
Cfg_SpdCtrlBW.Description = 'Speed controller bandwith.';
Cfg_SpdCtrlBW.DataType = 'single';
Cfg_SpdCtrlBW.Min = [];
Cfg_SpdCtrlBW.Max = [];
Cfg_SpdCtrlBW.DocUnits = '';
Cfg_SpdCtrlBW.Value = CtrlParams.SpdBW;
Cfg_SpdCtrlBW.CoderInfo.StorageClass = 'Custom';
Cfg_SpdCtrlBW.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_SpdCtrlBW.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_SpdCtrlBW.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% PID-P term.
SpdCtrl_Kp = Simulink.Parameter;
SpdCtrl_Kp.StorageClass = 'Auto';
SpdCtrl_Kp.Description = 'PI proportional term for speed controller.';
SpdCtrl_Kp.DataType = 'single';
SpdCtrl_Kp.Min = [];
SpdCtrl_Kp.Max = [];
SpdCtrl_Kp.DocUnits = '';
SpdCtrl_Kp.Value = CtrlParams.SpdKp;
SpdCtrl_Kp.CoderInfo.StorageClass = 'Custom';
SpdCtrl_Kp.CoderInfo.CustomStorageClass = 'ExportToFile';
SpdCtrl_Kp.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
SpdCtrl_Kp.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';


%% PID-I term.
SpdCtrl_Ki = Simulink.Parameter;
SpdCtrl_Ki.StorageClass = 'Auto';
SpdCtrl_Ki.Description = 'PI integral term for speed controller.';
SpdCtrl_Ki.DataType =  'single';
SpdCtrl_Ki.Min = [];
SpdCtrl_Ki.Max = [];
SpdCtrl_Ki.DocUnits = '';
SpdCtrl_Ki.Value = CtrlParams.SpdKi;
SpdCtrl_Ki.CoderInfo.StorageClass = 'Custom';
SpdCtrl_Ki.CoderInfo.CustomStorageClass = 'ExportToFile';
SpdCtrl_Ki.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
SpdCtrl_Ki.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';


%% PID-P term.
PosCtrl_Kp = Simulink.Parameter;
PosCtrl_Kp.StorageClass = 'Auto';
PosCtrl_Kp.Description = 'PI proportional term for position controller.';
PosCtrl_Kp.DataType = 'single';
PosCtrl_Kp.Min = [];
PosCtrl_Kp.Max = [];
PosCtrl_Kp.DocUnits = '';
PosCtrl_Kp.Value = CtrlParams.PosKp;
PosCtrl_Kp.CoderInfo.StorageClass = 'Custom';
PosCtrl_Kp.CoderInfo.CustomStorageClass = 'ExportToFile';
PosCtrl_Kp.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
PosCtrl_Kp.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% PID-I term.
PosCtrl_Ki = Simulink.Parameter;
PosCtrl_Ki.StorageClass = 'Auto';
PosCtrl_Ki.Description = 'PI integral term for position controller.';
PosCtrl_Ki.DataType =  'single';
PosCtrl_Ki.Min = [];
PosCtrl_Ki.Max = [];
PosCtrl_Ki.DocUnits = '';
PosCtrl_Ki.Value = CtrlParams.PosKi;
PosCtrl_Ki.CoderInfo.StorageClass = 'Custom';
PosCtrl_Ki.CoderInfo.CustomStorageClass = 'ExportToFile';
PosCtrl_Ki.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
PosCtrl_Ki.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Sliding mode differentiator P-term.
SmDiff_Kp = Simulink.Parameter;
SmDiff_Kp.StorageClass = 'Auto';
SmDiff_Kp.Description = 'Proportional gain for motor position sliding mode differentiator.';
SmDiff_Kp.DataType = 'single';
SmDiff_Kp.Min = [];
SmDiff_Kp.Max = [];
SmDiff_Kp.DocUnits = '';
SmDiff_Kp.Value = SmDiffParams.Kp;
SmDiff_Kp.CoderInfo.StorageClass = 'Custom';
SmDiff_Kp.CoderInfo.CustomStorageClass = 'ExportToFile';
SmDiff_Kp.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
SmDiff_Kp.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Sliding mode differentiator I-term.
SmDiff_Ki = Simulink.Parameter;
SmDiff_Ki.StorageClass = 'Auto';
SmDiff_Ki.Description = 'Integral gain for motor position sliding mode differentiator.';
SmDiff_Ki.DataType = 'single';
SmDiff_Ki.Min = [];
SmDiff_Ki.Max = [];
SmDiff_Ki.DocUnits = '';
SmDiff_Ki.Value = SmDiffParams.Ki;
SmDiff_Ki.CoderInfo.StorageClass = 'Custom';
SmDiff_Ki.CoderInfo.CustomStorageClass = 'ExportToFile';
SmDiff_Ki.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
SmDiff_Ki.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% SM differentiator filter constant. Calculated as: tau / (ts + tau).
SmDiff_FiltCnst = Simulink.Parameter;
SmDiff_FiltCnst.StorageClass = 'Auto';
SmDiff_FiltCnst.Description = ' SM differentiator filter constant. Calculated as: tau / (ts + tau).';
SmDiff_FiltCnst.DataType = 'single';
SmDiff_FiltCnst.Min = [];
SmDiff_FiltCnst.Max = [];
SmDiff_FiltCnst.DocUnits = '';
SmDiff_FiltCnst.Value = 0.9615;
SmDiff_FiltCnst.CoderInfo.StorageClass = 'Custom';
SmDiff_FiltCnst.CoderInfo.CustomStorageClass = 'ExportToFile';
SmDiff_FiltCnst.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
SmDiff_FiltCnst.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Disturbance observer.
DistObs_K1 = Simulink.Parameter;
DistObs_K1.StorageClass = 'Auto';
DistObs_K1.Description = 'Disturbance obser gain k1.';
DistObs_K1.DataType = 'single';
DistObs_K1.Min = [];
DistObs_K1.Max = [];
DistObs_K1.DocUnits = '';
DistObs_K1.Value = AdrcParams.K1;
DistObs_K1.CoderInfo.StorageClass = 'Custom';
DistObs_K1.CoderInfo.CustomStorageClass = 'ExportToFile';
DistObs_K1.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
DistObs_K1.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

DistObs_K2 = Simulink.Parameter;
DistObs_K2.StorageClass = 'Auto';
DistObs_K2.Description = 'Disturbance obser gain k2.';
DistObs_K2.DataType = 'single';
DistObs_K2.Min = [];
DistObs_K2.Max = [];
DistObs_K2.DocUnits = '';
DistObs_K2.Value = AdrcParams.K2;
DistObs_K2.CoderInfo.StorageClass = 'Custom';
DistObs_K2.CoderInfo.CustomStorageClass = 'ExportToFile';
DistObs_K2.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
DistObs_K2.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

DistObs_K3 = Simulink.Parameter;
DistObs_K3.StorageClass = 'Auto';
DistObs_K3.Description = 'Disturbance obser gain k3.';
DistObs_K3.DataType = 'single';
DistObs_K3.Min = [];
DistObs_K3.Max = [];
DistObs_K3.DocUnits = '';
DistObs_K3.Value = AdrcParams.K3;
DistObs_K3.CoderInfo.StorageClass = 'Custom';
DistObs_K3.CoderInfo.CustomStorageClass = 'ExportToFile';
DistObs_K3.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
DistObs_K3.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

DistObs_J = Simulink.Parameter;
DistObs_J.StorageClass = 'Auto';
DistObs_J.Description = 'Motor Inertia at Disturbance Observer.';
DistObs_J.DataType = 'single';
DistObs_J.Min = [];
DistObs_J.Max = [];
DistObs_J.DocUnits = '';
DistObs_J.Value = MtrParams.Jm;
DistObs_J.CoderInfo.StorageClass = 'Custom';
DistObs_J.CoderInfo.CustomStorageClass = 'ExportToFile';
DistObs_J.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
DistObs_J.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Encoder definition.
Cfg_EncCnts = Simulink.Parameter;
Cfg_EncCnts.StorageClass = 'Auto';
Cfg_EncCnts.Description = 'Encoder counts';
Cfg_EncCnts.DataType = 'single';
Cfg_EncCnts.Min = [];
Cfg_EncCnts.Max = [];
Cfg_EncCnts.DocUnits = '';
Cfg_EncCnts.Value = MtrParams.EncCnts;
Cfg_EncCnts.CoderInfo.StorageClass = 'Custom';
Cfg_EncCnts.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_EncCnts.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_EncCnts.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Encoder definition.
Cfg_EncCntsInt = Simulink.Parameter;
Cfg_EncCntsInt.StorageClass = 'Auto';
Cfg_EncCntsInt.Description = 'Encoder counts w/ int32 data type.';
Cfg_EncCntsInt.DataType = 'int32';
Cfg_EncCntsInt.Min = [];
Cfg_EncCntsInt.Max = [];
Cfg_EncCntsInt.DocUnits = '';
Cfg_EncCntsInt.Value = MtrParams.EncCnts;
Cfg_EncCntsInt.CoderInfo.StorageClass = 'Custom';
Cfg_EncCntsInt.CoderInfo.CustomStorageClass = 'ExportToFile';
Cfg_EncCntsInt.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
Cfg_EncCntsInt.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Encoder to radians.
EncCntsToRads = Simulink.Parameter;
EncCntsToRads.StorageClass = 'Auto';
EncCntsToRads.Description = 'Encoder to radians conversion.';
EncCntsToRads.DataType = 'single';
EncCntsToRads.Min = [];
EncCntsToRads.Max = [];
EncCntsToRads.DocUnits = '';
EncCntsToRads.Value = 2. * pi / MtrParams.EncCnts;
EncCntsToRads.CoderInfo.StorageClass = 'Custom';
EncCntsToRads.CoderInfo.CustomStorageClass = 'ExportToFile';
EncCntsToRads.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
EncCntsToRads.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Encoder resolution.
EncResDeg = Simulink.Parameter;
EncResDeg.StorageClass = 'Auto';
EncResDeg.Description = 'Encoder resolution in degrees';
EncResDeg.DataType = 'single';
EncResDeg.Min = [];
EncResDeg.Max = [];
EncResDeg.DocUnits = '';
EncResDeg.Value = 360. / MtrParams.PPR;
EncResDeg.CoderInfo.StorageClass = 'Custom';
EncResDeg.CoderInfo.CustomStorageClass = 'ExportToFile';
EncResDeg.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
EncResDeg.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Main sampling time (1khz)
TsMain = Simulink.Parameter;
TsMain.StorageClass = 'Auto';
TsMain.Description = 'Main sampling time (1khz)';
TsMain.DataType = 'single';
TsMain.Min = [];
TsMain.Max = [];
TsMain.DocUnits = '';
TsMain.Value = MainTsample;
TsMain.CoderInfo.StorageClass = 'Custom';
TsMain.CoderInfo.CustomStorageClass = 'ExportToFile';
TsMain.CoderInfo.CustomAttributes.HeaderFile = 'cfg_params.h';
TsMain.CoderInfo.CustomAttributes.DefinitionFile = 'cfg_params.c';

%% Signal definitions

%% Current feedback Phase-A.
MtrIf_Ifbk = Simulink.Signal;
MtrIf_Ifbk.CoderInfo.Alias = '';
MtrIf_Ifbk.Description = 'Actual motor current from Phase-A';
MtrIf_Ifbk.DataType =  'Ifbk';
MtrIf_Ifbk.Min = [];
MtrIf_Ifbk.Max = [];
MtrIf_Ifbk.DocUnits = 'mA';
MtrIf_Ifbk.Dimensions = 1;
MtrIf_Ifbk.Complexity =  'auto';
MtrIf_Ifbk.SampleTime = -1;
MtrIf_Ifbk.SamplingMode =  'auto';
MtrIf_Ifbk.InitialValue = '';
% Generate GetSet function:
MtrIf_Ifbk.CoderInfo.StorageClass =  'Custom';
MtrIf_Ifbk.CoderInfo.CustomStorageClass =  'GetSet';
MtrIf_Ifbk.CoderInfo.CustomAttributes.HeaderFile = 'app.h';
MtrIf_Ifbk.CoderInfo.CustomAttributes.GetFunction = 'App_GetIfbkPhA';
MtrIf_Ifbk.CoderInfo.CustomAttributes.SetFunction = '';

%% PWM voltage for Phase-A.
MtrIf_Vin = Simulink.Signal;
MtrIf_Vin.CoderInfo.Alias = '';
MtrIf_Vin.Description = 'PWM voltage for Phase-A';
MtrIf_Vin.DataType =  'Volts';
MtrIf_Vin.Min = [];
MtrIf_Vin.Max = [];
MtrIf_Vin.DocUnits = 'mV';
MtrIf_Vin.Dimensions = 1;
MtrIf_Vin.Complexity =  'auto';
MtrIf_Vin.SampleTime = -1;
MtrIf_Vin.SamplingMode =  'auto';
MtrIf_Vin.InitialValue = '';
% Generate GetSet function:
MtrIf_Vin.CoderInfo.StorageClass =  'Custom';
MtrIf_Vin.CoderInfo.CustomStorageClass =  'GetSet';
MtrIf_Vin.CoderInfo.CustomAttributes.HeaderFile = 'app.h';
MtrIf_Vin.CoderInfo.CustomAttributes.SetFunction = 'App_SetPwmVoltChA';
MtrIf_Vin.CoderInfo.CustomAttributes.GetFunction = '';

%% Motor position.
MtrIf_PosAct = Simulink.Signal;
MtrIf_PosAct.CoderInfo.Alias = '';
MtrIf_PosAct.Description = 'Motor position';
MtrIf_PosAct.DataType =  'Degs';
MtrIf_PosAct.Min = [];
MtrIf_PosAct.Max = [];
MtrIf_PosAct.DocUnits = 'deg';
MtrIf_PosAct.Dimensions = 1;
MtrIf_PosAct.Complexity =  'auto';
MtrIf_PosAct.SampleTime = -1;
MtrIf_PosAct.SamplingMode =  'auto';
MtrIf_PosAct.InitialValue = '';
% Generate GetSet function:
MtrIf_PosAct.CoderInfo.StorageClass =  'Custom';
MtrIf_PosAct.CoderInfo.CustomStorageClass =  'GetSet';
MtrIf_PosAct.CoderInfo.CustomAttributes.HeaderFile = 'app.h';
MtrIf_PosAct.CoderInfo.CustomAttributes.GetFunction = 'App_GetMtrPos';
MtrIf_PosAct.CoderInfo.CustomAttributes.SetFunction = '';

%% Motor position target.
MtrIf_PosTgt = Simulink.Signal;
MtrIf_PosTgt.CoderInfo.Alias = '';
MtrIf_PosTgt.Description = 'Motor position target';
MtrIf_PosTgt.DataType =  'Degs';
MtrIf_PosTgt.Min = [];
MtrIf_PosTgt.Max = [];
MtrIf_PosTgt.DocUnits = 'deg';
MtrIf_PosTgt.Dimensions = 1;
MtrIf_PosTgt.Complexity =  'auto';
MtrIf_PosTgt.SampleTime = -1;
MtrIf_PosTgt.SamplingMode =  'auto';
MtrIf_PosTgt.InitialValue = '';
% Generate GetSet function:
MtrIf_PosTgt.CoderInfo.StorageClass =  'Custom';
MtrIf_PosTgt.CoderInfo.CustomStorageClass =  'GetSet';
MtrIf_PosTgt.CoderInfo.CustomAttributes.HeaderFile = 'app.h';
MtrIf_PosTgt.CoderInfo.CustomAttributes.GetFunction = 'App_GetMtrPosTgt';
MtrIf_PosTgt.CoderInfo.CustomAttributes.SetFunction = 'App_SetMtrPosTgt';


%% Motor speed.
MtrIf_SpdAct = Simulink.Signal;
MtrIf_SpdAct.CoderInfo.Alias = '';
MtrIf_SpdAct.Description = 'Motor speed';
MtrIf_SpdAct.DataType =  'Degs_s';
MtrIf_SpdAct.Min = [];
MtrIf_SpdAct.Max = [];
MtrIf_SpdAct.DocUnits = '';
MtrIf_SpdAct.Dimensions = 1;
MtrIf_SpdAct.Complexity =  'auto';
MtrIf_SpdAct.SampleTime = -1;
MtrIf_SpdAct.SamplingMode =  'auto';
MtrIf_SpdAct.InitialValue = '';
% Generate GetSet function:
MtrIf_SpdAct.CoderInfo.StorageClass =  'Custom';
MtrIf_SpdAct.CoderInfo.CustomStorageClass =  'GetSet';
MtrIf_SpdAct.CoderInfo.CustomAttributes.HeaderFile = 'app.h';
MtrIf_SpdAct.CoderInfo.CustomAttributes.SetFunction = 'App_SetMtrSpd';
MtrIf_SpdAct.CoderInfo.CustomAttributes.GetFunction = 'App_GetMtrSpd';

%% Motor speed filtered.
MtrIf_SpdActFil = Simulink.Signal;
MtrIf_SpdActFil.CoderInfo.Alias = '';
MtrIf_SpdActFil.Description = 'Motor speed filtered';
MtrIf_SpdActFil.DataType =  'Degs_s';
MtrIf_SpdActFil.Min = [];
MtrIf_SpdActFil.Max = [];
MtrIf_SpdActFil.DocUnits = '';
MtrIf_SpdActFil.Dimensions = 1;
MtrIf_SpdActFil.Complexity =  'auto';
MtrIf_SpdActFil.SampleTime = -1;
MtrIf_SpdActFil.SamplingMode =  'auto';
MtrIf_SpdActFil.InitialValue = '';
% Generate GetSet function:
MtrIf_SpdActFil.CoderInfo.StorageClass =  'Custom';
MtrIf_SpdActFil.CoderInfo.CustomStorageClass =  'GetSet';
MtrIf_SpdActFil.CoderInfo.CustomAttributes.HeaderFile = 'app.h';
MtrIf_SpdActFil.CoderInfo.CustomAttributes.SetFunction = 'App_SetMtrSpdFil';
MtrIf_SpdActFil.CoderInfo.CustomAttributes.GetFunction = '';
