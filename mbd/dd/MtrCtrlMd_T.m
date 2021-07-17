classdef MtrCtrlMd_T < Simulink.IntEnumType
    %MTRCTLMD Controller mode.
    %   Defines controller mode: position, speed and current modes.
    enumeration
      CTRL_MD_OFF(0),
      CTRL_MD_CAL (1),
      CTRL_MD_RAW_PWM(2),
      CTRL_MD_DQ_PWM(3),
      CTRL_MD_IFBK(4),
      CTRL_MD_TRQ(5),
      CTRL_MD_SPD(6),
      CTRL_MD_POS(7),
      CTRL_MD_STEP_DIR(8),
    end
end

