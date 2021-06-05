function task_bus() 
% TASK_BUS initializes a set of bus objects in the MATLAB base workspace 

% Bus object: TASK_BUS 
clear elems;
elems(1) = Simulink.BusElement;
elems(1).Name = 'v_abc';
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
elems(2).Name = 'ctrl_mgr_st';
elems(2).Dimensions = 1;
elems(2).DimensionsMode = 'Fixed';
elems(2).DataType = 'Enum: CtrlMgrSt';
elems(2).SampleTime = -1;
elems(2).Complexity = 'real';
elems(2).Min = [];
elems(2).Max = [];
elems(2).DocUnits = '';
elems(2).Description = '';

elems(3) = Simulink.BusElement;
elems(3).Name = 'enc_ofs_cnts';
elems(3).Dimensions = 1;
elems(3).DimensionsMode = 'Fixed';
elems(3).DataType = 'int32';
elems(3).SampleTime = -1;
elems(3).Complexity = 'real';
elems(3).Min = [];
elems(3).Max = [];
elems(3).DocUnits = '';
elems(3).Description = '';

TASK_BUS = Simulink.Bus;
TASK_BUS.HeaderFile = '';
TASK_BUS.Description = '';
TASK_BUS.DataScope = 'Auto';
TASK_BUS.Alignment = -1;
TASK_BUS.Elements = elems;
clear elems;
assignin('base','TASK_BUS', TASK_BUS);

