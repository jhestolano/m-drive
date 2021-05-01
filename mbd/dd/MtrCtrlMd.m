classdef MtrCtrlMd < Simulink.IntEnumType
    %MTRCTLMD Controller mode.
    %   Defines controller mode: position, speed and current modes.
    enumeration
      PwmCtrlMd(0),
      IfbkCtrlMd(1),
      TrqCtrlMd(2),
      SpdCtrlMd(3),
      PosCtrlMd(4),
      StepDirCtrlMd(5),
      OffCtrlMd(255),
    end
end

