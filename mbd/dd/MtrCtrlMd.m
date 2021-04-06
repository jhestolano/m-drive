classdef MtrCtrlMd < Simulink.IntEnumType
    %MTRCTLMD Controller mode.
    %   Defines controller mode: position, speed and current modes.
    enumeration
      IfbkCtrlMd(0),
      SpdCtrlMd(1),
      PosCtrlMd(2),
      TrqCtrlMd(3),
      OpnLoopCtrlMd(4),
      OffCtrlMd(255),
    end
end

