function ctrl_bus_types() 
% CTRL_BUS_TYPES initializes a set of bus objects in the MATLAB base workspace 

% Bus object: Calib_OutType 
clear elems;
elems(1) = Simulink.BusElement;
elems(1).Name = 'ctrl_md_rqst';
elems(1).Dimensions = 1;
elems(1).DimensionsMode = 'Fixed';
elems(1).DataType = 'Enum: MtrCtrlMd_T';
elems(1).SampleTime = -1;
elems(1).Complexity = 'real';
elems(1).Min = [];
elems(1).Max = [];
elems(1).DocUnits = '';
elems(1).Description = '';

elems(2) = Simulink.BusElement;
elems(2).Name = 'cal_mgr_st_rqst';
elems(2).Dimensions = 1;
elems(2).DimensionsMode = 'Fixed';
elems(2).DataType = 'Enum: CalMgrSt_T';
elems(2).SampleTime = -1;
elems(2).Complexity = 'real';
elems(2).Min = [];
elems(2).Max = [];
elems(2).DocUnits = '';
elems(2).Description = '';

elems(3) = Simulink.BusElement;
elems(3).Name = 'mtr_cmd_rqst';
elems(3).Dimensions = 3;
elems(3).DimensionsMode = 'Fixed';
elems(3).DataType = 'single';
elems(3).SampleTime = -1;
elems(3).Complexity = 'real';
elems(3).Min = [];
elems(3).Max = [];
elems(3).DocUnits = '';
elems(3).Description = '';

Calib_OutType = Simulink.Bus;
Calib_OutType.HeaderFile = '';
Calib_OutType.Description = sprintf('This structure holds all calibration routine requests.');
Calib_OutType.DataScope = 'Auto';
Calib_OutType.Alignment = -1;
Calib_OutType.Elements = elems;
clear elems;
assignin('base','Calib_OutType', Calib_OutType);

% Bus object: Calib_ParamType 
clear elems;
elems(1) = Simulink.BusElement;
elems(1).Name = 'enc_ofs';
elems(1).Dimensions = 1;
elems(1).DimensionsMode = 'Fixed';
elems(1).DataType = 'int32';
elems(1).SampleTime = -1;
elems(1).Complexity = 'real';
elems(1).Min = [];
elems(1).Max = [];
elems(1).DocUnits = '';
elems(1).Description = '';

elems(2) = Simulink.BusElement;
elems(2).Name = 'ind';
elems(2).Dimensions = 1;
elems(2).DimensionsMode = 'Fixed';
elems(2).DataType = 'single';
elems(2).SampleTime = -1;
elems(2).Complexity = 'real';
elems(2).Min = [];
elems(2).Max = [];
elems(2).DocUnits = '';
elems(2).Description = '';

elems(3) = Simulink.BusElement;
elems(3).Name = 'ppoles';
elems(3).Dimensions = 1;
elems(3).DimensionsMode = 'Fixed';
elems(3).DataType = 'int32';
elems(3).SampleTime = -1;
elems(3).Complexity = 'real';
elems(3).Min = [];
elems(3).Max = [];
elems(3).DocUnits = '';
elems(3).Description = '';

elems(4) = Simulink.BusElement;
elems(4).Name = 'res';
elems(4).Dimensions = 1;
elems(4).DimensionsMode = 'Fixed';
elems(4).DataType = 'single';
elems(4).SampleTime = -1;
elems(4).Complexity = 'real';
elems(4).Min = [];
elems(4).Max = [];
elems(4).DocUnits = '';
elems(4).Description = '';

elems(5) = Simulink.BusElement;
elems(5).Name = 'ifbk_ofs';
elems(5).Dimensions = 3;
elems(5).DimensionsMode = 'Fixed';
elems(5).DataType = 'single';
elems(5).SampleTime = -1;
elems(5).Complexity = 'real';
elems(5).Min = [];
elems(5).Max = [];
elems(5).DocUnits = '';
elems(5).Description = '';

Calib_ParamType = Simulink.Bus;
Calib_ParamType.HeaderFile = '';
Calib_ParamType.Description = sprintf('This structure holds all calibration (estimated) parameters.');
Calib_ParamType.DataScope = 'Auto';
Calib_ParamType.Alignment = -1;
Calib_ParamType.Elements = elems;
clear elems;
assignin('base','Calib_ParamType', Calib_ParamType);

% Bus object: CtrlMgr_OutType 
clear elems;
elems(1) = Simulink.BusElement;
elems(1).Name = 'ctrl_tgt';
elems(1).Dimensions = 3;
elems(1).DimensionsMode = 'Fixed';
elems(1).DataType = 'single';
elems(1).SampleTime = -1;
elems(1).Complexity = 'real';
elems(1).Min = [];
elems(1).Max = [];
elems(1).DocUnits = '';
elems(1).Description = '';

elems(2) = Simulink.BusElement;
elems(2).Name = 'ctrl_cal_act';
elems(2).Dimensions = 1;
elems(2).DimensionsMode = 'Fixed';
elems(2).DataType = 'Enum: MtrCtrlCal_T';
elems(2).SampleTime = -1;
elems(2).Complexity = 'real';
elems(2).Min = [];
elems(2).Max = [];
elems(2).DocUnits = '';
elems(2).Description = '';

elems(3) = Simulink.BusElement;
elems(3).Name = 'ctrl_md_act';
elems(3).Dimensions = 1;
elems(3).DimensionsMode = 'Fixed';
elems(3).DataType = 'Enum: MtrCtrlMd_T';
elems(3).SampleTime = -1;
elems(3).Complexity = 'real';
elems(3).Min = [];
elems(3).Max = [];
elems(3).DocUnits = '';
elems(3).Description = '';

elems(4) = Simulink.BusElement;
elems(4).Name = 'ENBL_CTRL_FLAGS';
elems(4).Dimensions = 1;
elems(4).DimensionsMode = 'Fixed';
elems(4).DataType = 'Bus: enbl_ctrl_flags_type';
elems(4).SampleTime = -1;
elems(4).Complexity = 'real';
elems(4).Min = [];
elems(4).Max = [];
elems(4).DocUnits = '';
elems(4).Description = '';

CtrlMgr_OutType = Simulink.Bus;
CtrlMgr_OutType.HeaderFile = '';
CtrlMgr_OutType.Description = sprintf('Output structured bus of control manager.\n\nThe control manager receives requests for different control modes\nand calibration routines.');
CtrlMgr_OutType.DataScope = 'Auto';
CtrlMgr_OutType.Alignment = -1;
CtrlMgr_OutType.Elements = elems;
clear elems;
assignin('base','CtrlMgr_OutType', CtrlMgr_OutType);

% Bus object: EncOfsCal_OutType 
clear elems;
elems(1) = Simulink.BusElement;
elems(1).Name = 'enc_ofs_cal';
elems(1).Dimensions = 1;
elems(1).DimensionsMode = 'Fixed';
elems(1).DataType = 'int32';
elems(1).SampleTime = -1;
elems(1).Complexity = 'real';
elems(1).Min = [];
elems(1).Max = [];
elems(1).DocUnits = '';
elems(1).Description = '';

elems(2) = Simulink.BusElement;
elems(2).Name = 'ctrl_md_rqst';
elems(2).Dimensions = 1;
elems(2).DimensionsMode = 'Fixed';
elems(2).DataType = 'Enum: MtrCtrlMd_T';
elems(2).SampleTime = -1;
elems(2).Complexity = 'real';
elems(2).Min = [];
elems(2).Max = [];
elems(2).DocUnits = '';
elems(2).Description = '';

elems(3) = Simulink.BusElement;
elems(3).Name = 'ctrl_mgr_st_rqst';
elems(3).Dimensions = 1;
elems(3).DimensionsMode = 'Fixed';
elems(3).DataType = 'Enum: CalMgrSt_T';
elems(3).SampleTime = -1;
elems(3).Complexity = 'real';
elems(3).Min = [];
elems(3).Max = [];
elems(3).DocUnits = '';
elems(3).Description = '';

elems(4) = Simulink.BusElement;
elems(4).Name = 'enc_cnts_out';
elems(4).Dimensions = 1;
elems(4).DimensionsMode = 'Fixed';
elems(4).DataType = 'int32';
elems(4).SampleTime = -1;
elems(4).Complexity = 'real';
elems(4).Min = [];
elems(4).Max = [];
elems(4).DocUnits = '';
elems(4).Description = '';

elems(5) = Simulink.BusElement;
elems(5).Name = 'pwm_rqst';
elems(5).Dimensions = 3;
elems(5).DimensionsMode = 'Fixed';
elems(5).DataType = 'single';
elems(5).SampleTime = -1;
elems(5).Complexity = 'real';
elems(5).Min = [];
elems(5).Max = [];
elems(5).DocUnits = '';
elems(5).Description = '';

EncOfsCal_OutType = Simulink.Bus;
EncOfsCal_OutType.HeaderFile = '';
EncOfsCal_OutType.Description = sprintf('Encoder offset calibration outputs and requests.');
EncOfsCal_OutType.DataScope = 'Auto';
EncOfsCal_OutType.Alignment = -1;
EncOfsCal_OutType.Elements = elems;
clear elems;
assignin('base','EncOfsCal_OutType', EncOfsCal_OutType);

% Bus object: FoCtrl_OutType 
clear elems;
elems(1) = Simulink.BusElement;
elems(1).Name = 'mtrif_mod_wave';
elems(1).Dimensions = 3;
elems(1).DimensionsMode = 'Fixed';
elems(1).DataType = 'single';
elems(1).SampleTime = -1;
elems(1).Complexity = 'real';
elems(1).Min = [];
elems(1).Max = [];
elems(1).DocUnits = '';
elems(1).Description = '';

elems(2) = Simulink.BusElement;
elems(2).Name = 'mtrif_spd_est';
elems(2).Dimensions = 1;
elems(2).DimensionsMode = 'Fixed';
elems(2).DataType = 'single';
elems(2).SampleTime = -1;
elems(2).Complexity = 'real';
elems(2).Min = [];
elems(2).Max = [];
elems(2).DocUnits = '';
elems(2).Description = '';

elems(3) = Simulink.BusElement;
elems(3).Name = 'mtrif_pwm_dc';
elems(3).Dimensions = 3;
elems(3).DimensionsMode = 'Fixed';
elems(3).DataType = 'single';
elems(3).SampleTime = -1;
elems(3).Complexity = 'real';
elems(3).Min = [];
elems(3).Max = [];
elems(3).DocUnits = '';
elems(3).Description = '';

elems(4) = Simulink.BusElement;
elems(4).Name = 'mtrif_trq_act';
elems(4).Dimensions = 1;
elems(4).DimensionsMode = 'Fixed';
elems(4).DataType = 'single';
elems(4).SampleTime = -1;
elems(4).Complexity = 'real';
elems(4).Min = [];
elems(4).Max = [];
elems(4).DocUnits = '';
elems(4).Description = '';

elems(5) = Simulink.BusElement;
elems(5).Name = 'obs_enc_cnts';
elems(5).Dimensions = 1;
elems(5).DimensionsMode = 'Fixed';
elems(5).DataType = 'int32';
elems(5).SampleTime = -1;
elems(5).Complexity = 'real';
elems(5).Min = [];
elems(5).Max = [];
elems(5).DocUnits = '';
elems(5).Description = '';

elems(6) = Simulink.BusElement;
elems(6).Name = 'mtrif_ifbk_dq';
elems(6).Dimensions = 2;
elems(6).DimensionsMode = 'Fixed';
elems(6).DataType = 'single';
elems(6).SampleTime = -1;
elems(6).Complexity = 'real';
elems(6).Min = [];
elems(6).Max = [];
elems(6).DocUnits = '';
elems(6).Description = '';

elems(7) = Simulink.BusElement;
elems(7).Name = 'mtrif_pwm_dq';
elems(7).Dimensions = 2;
elems(7).DimensionsMode = 'Fixed';
elems(7).DataType = 'single';
elems(7).SampleTime = -1;
elems(7).Complexity = 'real';
elems(7).Min = [];
elems(7).Max = [];
elems(7).DocUnits = '';
elems(7).Description = '';

FoCtrl_OutType = Simulink.Bus;
FoCtrl_OutType.HeaderFile = '';
FoCtrl_OutType.Description = '';
FoCtrl_OutType.DataScope = 'Auto';
FoCtrl_OutType.Alignment = -1;
FoCtrl_OutType.Elements = elems;
clear elems;
assignin('base','FoCtrl_OutType', FoCtrl_OutType);

% Bus object: MotnCtrl_OutType 
clear elems;
elems(1) = Simulink.BusElement;
elems(1).Name = 'motn_ctrl_cmd';
elems(1).Dimensions = 1;
elems(1).DimensionsMode = 'Fixed';
elems(1).DataType = 'single';
elems(1).SampleTime = -1;
elems(1).Complexity = 'real';
elems(1).Min = [];
elems(1).Max = [];
elems(1).DocUnits = '';
elems(1).Description = '';

MotnCtrl_OutType = Simulink.Bus;
MotnCtrl_OutType.HeaderFile = '';
MotnCtrl_OutType.Description = sprintf('Holds all outputs of main (motion) controller.');
MotnCtrl_OutType.DataScope = 'Auto';
MotnCtrl_OutType.Alignment = -1;
MotnCtrl_OutType.Elements = elems;
clear elems;
assignin('base','MotnCtrl_OutType', MotnCtrl_OutType);

% Bus object: MtrIf_InType 
clear elems;
elems(1) = Simulink.BusElement;
elems(1).Name = 'mtrif_enc_cnts';
elems(1).Dimensions = 1;
elems(1).DimensionsMode = 'Fixed';
elems(1).DataType = 'int32';
elems(1).SampleTime = -1;
elems(1).Complexity = 'real';
elems(1).Min = [];
elems(1).Max = [];
elems(1).DocUnits = '';
elems(1).Description = '';

elems(2) = Simulink.BusElement;
elems(2).Name = 'mtrif_ifbk_act';
elems(2).Dimensions = 3;
elems(2).DimensionsMode = 'Fixed';
elems(2).DataType = 'single';
elems(2).SampleTime = -1;
elems(2).Complexity = 'real';
elems(2).Min = [];
elems(2).Max = [];
elems(2).DocUnits = '';
elems(2).Description = '';

elems(3) = Simulink.BusElement;
elems(3).Name = 'mtrif_spd_sns';
elems(3).Dimensions = 1;
elems(3).DimensionsMode = 'Fixed';
elems(3).DataType = 'single';
elems(3).SampleTime = -1;
elems(3).Complexity = 'real';
elems(3).Min = [];
elems(3).Max = [];
elems(3).DocUnits = '';
elems(3).Description = '';

elems(4) = Simulink.BusElement;
elems(4).Name = 'mtrif_ctrl_md';
elems(4).Dimensions = 1;
elems(4).DimensionsMode = 'Fixed';
elems(4).DataType = 'Enum: MtrCtrlMd_T';
elems(4).SampleTime = -1;
elems(4).Complexity = 'real';
elems(4).Min = [];
elems(4).Max = [];
elems(4).DocUnits = '';
elems(4).Description = '';

elems(5) = Simulink.BusElement;
elems(5).Name = 'mtrif_tgt';
elems(5).Dimensions = 3;
elems(5).DimensionsMode = 'Fixed';
elems(5).DataType = 'single';
elems(5).SampleTime = -1;
elems(5).Complexity = 'real';
elems(5).Min = [];
elems(5).Max = [];
elems(5).DocUnits = '';
elems(5).Description = '';

elems(6) = Simulink.BusElement;
elems(6).Name = 'mtrif_cal_rqst';
elems(6).Dimensions = 1;
elems(6).DimensionsMode = 'Fixed';
elems(6).DataType = 'Enum: MtrCtrlCal_T';
elems(6).SampleTime = -1;
elems(6).Complexity = 'real';
elems(6).Min = [];
elems(6).Max = [];
elems(6).DocUnits = '';
elems(6).Description = '';

MtrIf_InType = Simulink.Bus;
MtrIf_InType.HeaderFile = '';
MtrIf_InType.Description = sprintf('Structure that holds all neccessary controller input signals.');
MtrIf_InType.DataScope = 'Auto';
MtrIf_InType.Alignment = -1;
MtrIf_InType.Elements = elems;
clear elems;
assignin('base','MtrIf_InType', MtrIf_InType);

% Bus object: enbl_ctrl_flags_type 
clear elems;
elems(1) = Simulink.BusElement;
elems(1).Name = 'ctrl_md_off';
elems(1).Dimensions = 1;
elems(1).DimensionsMode = 'Fixed';
elems(1).DataType = 'boolean';
elems(1).SampleTime = -1;
elems(1).Complexity = 'real';
elems(1).Min = [];
elems(1).Max = [];
elems(1).DocUnits = '';
elems(1).Description = '';

elems(2) = Simulink.BusElement;
elems(2).Name = 'enbl_raw_pwm';
elems(2).Dimensions = 1;
elems(2).DimensionsMode = 'Fixed';
elems(2).DataType = 'boolean';
elems(2).SampleTime = -1;
elems(2).Complexity = 'real';
elems(2).Min = [];
elems(2).Max = [];
elems(2).DocUnits = '';
elems(2).Description = '';

elems(3) = Simulink.BusElement;
elems(3).Name = 'enbl_mod_wave';
elems(3).Dimensions = 1;
elems(3).DimensionsMode = 'Fixed';
elems(3).DataType = 'boolean';
elems(3).SampleTime = -1;
elems(3).Complexity = 'real';
elems(3).Min = [];
elems(3).Max = [];
elems(3).DocUnits = '';
elems(3).Description = '';

elems(4) = Simulink.BusElement;
elems(4).Name = 'enbl_ifbk_ctrl';
elems(4).Dimensions = 1;
elems(4).DimensionsMode = 'Fixed';
elems(4).DataType = 'boolean';
elems(4).SampleTime = -1;
elems(4).Complexity = 'real';
elems(4).Min = [];
elems(4).Max = [];
elems(4).DocUnits = '';
elems(4).Description = '';

elems(5) = Simulink.BusElement;
elems(5).Name = 'enbl_spd_ctrl';
elems(5).Dimensions = 1;
elems(5).DimensionsMode = 'Fixed';
elems(5).DataType = 'boolean';
elems(5).SampleTime = -1;
elems(5).Complexity = 'real';
elems(5).Min = [];
elems(5).Max = [];
elems(5).DocUnits = '';
elems(5).Description = '';

elems(6) = Simulink.BusElement;
elems(6).Name = 'enbl_pos_ctrl';
elems(6).Dimensions = 1;
elems(6).DimensionsMode = 'Fixed';
elems(6).DataType = 'boolean';
elems(6).SampleTime = -1;
elems(6).Complexity = 'real';
elems(6).Min = [];
elems(6).Max = [];
elems(6).DocUnits = '';
elems(6).Description = '';

enbl_ctrl_flags_type = Simulink.Bus;
enbl_ctrl_flags_type.HeaderFile = '';
enbl_ctrl_flags_type.Description = '';
enbl_ctrl_flags_type.DataScope = 'Auto';
enbl_ctrl_flags_type.Alignment = -1;
enbl_ctrl_flags_type.Elements = elems;
clear elems;
assignin('base','enbl_ctrl_flags_type', enbl_ctrl_flags_type);

