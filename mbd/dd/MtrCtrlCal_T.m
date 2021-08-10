classdef MtrCtrlCal_T < Simulink.IntEnumType
    %MTRCTLCAL_T Calibration request.
    %   Defines the calibration request.
    enumeration
      CAL_NONE(0),
      CAL_ENC_OFS(1),
      CAL_RES_ID(2),
      CAL_IND_ID(3),
      CAL_IFBK_OFS(4),
      CAL_MECH_PARAMS(5),
      CAL_IFBK_CTRL(6),
      CAL_MOTN_CTRL(7),
    end

    methods (Static)
      function retVal = getDataScope()
        retVal = 'Exported';
      end
    end
end

