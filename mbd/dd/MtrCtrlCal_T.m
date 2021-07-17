classdef MtrCtrlCal_T < Simulink.IntEnumType
    %MTRCTLCAL_T Calibration request.
    %   Defines the calibration request.
    enumeration
      CAL_ENC_OFS(0),
      CAL_RES_ID(1),
      CAL_IND_ID(2),
      CAL_IFBK_OFS(3),
      CAL_MECH_PARAMS(4),
      CAL_IFBK_CTRL(5),
      CAL_MOTN_CTRL(6),
      CAL_NONE(255),
    end
end

