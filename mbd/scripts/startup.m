clear; clc;
proj = simulinkproject;
Simulink.fileGenControl('set', ...
    'CodeGenFolder', fullfile(proj.RootFolder, 'codegen'), ...)
    'CacheFolder', fullfile(proj.RootFolder, 'cache'), ...
    'CreateDir', true);
motor_DD;
ctrl_DD;
dbg_bus;
